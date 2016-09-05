#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofDisableArbTex();
    
    
    frontMovie.load("movies/front.mp4");
    backMovie.load("movies/back.mp4");
    frontMovie.play();
    backMovie.play();
    
    shader.load("shaders/equirectanguler");
    
    fbo.allocate(1280, 480);
    
    sphere = ofSpherePrimitive(1000, 64).getMesh();
    for(int i=0;i<sphere.getNumTexCoords();i++){
        sphere.setTexCoord(i, ofVec2f(1.0) - sphere.getTexCoord(i));
    }
    for(int i=0;i<sphere.getNumNormals();i++){
        sphere.setNormal(i, sphere.getNormal(i) * ofVec3f(-1));
    }

    
    offset.set("uvOffset", ofVec4f(0,0.0,0,0.0), ofVec4f(-0.1), ofVec4f(0.1));
    radius.set("radius", 0.445, 0.0, 1.0);
    showSphere.set("showSphere", false);
    thetaParams.add(offset);
    thetaParams.add(radius);
    gui.setup(thetaParams);
    gui.add(showSphere);
    
    
    cam.setAutoDistance(false);
    cam.setDistance(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    frontMovie.update();
    backMovie.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(frontMovie.isFrameNew() && backMovie.isFrameNew()){
        fbo.begin();
        ofClear(0);
        shader.begin();
        shader.setUniformTexture("mainTex", frontMovie.getTexture(), 0);
        shader.setUniforms(thetaParams);
        frontMovie.draw(0, 0, 640, 480);
        backMovie.draw(640, 0, 640, 480);
        shader.end();
        fbo.end();
        
    }

    if(!showSphere){
        
        fbo.draw(0, 0, 1280, 480);
        
    }else{
        
        ofEnableDepthTest();
        cam.begin();
        fbo.getTexture().bind();
        sphere.draw();
        fbo.getTexture().unbind();
        cam.end();
        
    }
    
    ofDisableDepthTest();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    switch (key) {
//        case '0':
////            backMovie.firstFrame();
//            break;
//    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
