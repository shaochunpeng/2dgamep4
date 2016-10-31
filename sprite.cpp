#include <cmath>
#include "sprite.h"
#include "gamedata.h"
#include <cmath>
#include "frameFactory.h"

Sprite::Sprite(const std::string& name) :
  Drawable(name,
           Vector2f( ((rand()%900)-450), ((rand() % 900)-450)),
               //Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    //Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f( ((rand()%500)-250), ((rand()%400)-200))
               //Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    //Gamedata::getInstance().getXmlInt(name+"/speedY"))
           
       ),



  frame( FrameFactory::getInstance().getFrame(name) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("WORLD_WIDTH")),//WORLD_WIDTH),
  worldHeight(Gamedata::getInstance().getXmlInt("WORLD_HEIGHT"))//WORLD_HEIGHT)
{ }

Sprite::Sprite(const string& n, const Vector2f& pos, const Vector2f& vel):
  Drawable(n, pos, vel), 
  frame( FrameFactory::getInstance().getFrame(n) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("WORLD_WIDTH")),
  worldHeight(Gamedata::getInstance().getXmlInt("WORLD_HEIGHT"))
{ }

Sprite::Sprite(const string& n, const Vector2f& pos, const Vector2f& vel,
               const Frame* frm):
  Drawable(n, pos, vel), 
  frame( frm ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("WORLD_WIDTH")),
  worldHeight(Gamedata::getInstance().getXmlInt("WORLD_HEIGHT"))
{ }
/*
Sprite::Sprite(const std::string& n, const Vector2f& pos, const Vector2f& vel, double& zoom):
    Drawable(n, pos, vel, zoom),
    frame( FrameFactory::getInstance().getFrame(n) ),
    frameWidth( frame->getWidth() ),
    frameHeight( frame->getHeight() ),
    worldWidth(Gamedata::getInstance().getXmlInt("WORLD_WIDTH") ),
    worldHeight(Gamedata::getInstance().getXmlInt("WORLD_HEIGHT") )
{ }*/

Sprite::Sprite(const Sprite& s) :
  Drawable(s), 
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("WORLD_WIDTH")),
  worldHeight(Gamedata::getInstance().getXmlInt("WORLD_HEIGHT"))
{ }

Sprite& Sprite::operator=(const Sprite&)
{
  return *this;
}


void Sprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  //double i =( sqrt((velocityX())*(velocityX())+(velocityY())*(velocityY())));
 // getZoom(i);
  frame->draw(x, y,getzoom()); 
}

int Sprite::getDistance(const Sprite *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void Sprite::update(Uint32 ticks) { 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}
