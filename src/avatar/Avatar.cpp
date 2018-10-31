// CSIRO has filed various patents which cover the Software. 

// CSIRO grants to you a license to any patents granted for inventions
// implemented by the Software for academic, research and non-commercial
// use only.

// CSIRO hereby reserves all rights to its inventions implemented by the
// Software and any patents subsequently granted for those inventions
// that are not expressly granted to you.  Should you wish to license the
// patents relating to the Software for commercial use please contact
// CSIRO IP & Licensing, Gautam Tendulkar (gautam.tendulkar@csiro.au) or
// Nick Marsh (nick.marsh@csiro.au)

// This software is provided under the CSIRO OPEN SOURCE LICENSE
// (GPL2) which can be found in the LICENSE file located in the top
// most directory of the source code.

// Copyright CSIRO 2013

#include <avatar/myAvatar.hpp>
using namespace AVATAR;
using namespace std;

//===========================================================================
Avatar::~Avatar()
{

}
//===========================================================================
Avatar* AVATAR::LoadAvatar(const char* fname)
{
  int type; Avatar* model=NULL;
  ifstream file(fname);
  if (!file.is_open())
	  return NULL;

  file.read(reinterpret_cast<char*>(&type), sizeof(type));
  file.close();
  switch(type){
  case IO::MYAVATAR:
    model = new myAvatar(fname);
    break;
  default:    
    file.open(fname,std::ios::binary);
    if (!file.is_open())
		return NULL;

    file.read(reinterpret_cast<char*>(&type), sizeof(type));
    file.close();
    if (type == IOBinary::MYAVATAR)
      model = new myAvatar(fname, true);
    else     
      printf("ERROR(%s,%d) : unknown avatar type %d\n", 
	     __FILE__,__LINE__,type);
  }
  return model;
}
//============================================================================
void* AVATAR::LoadAvatarParams(const char* fname)
{
  int type; void* model = NULL;
  ifstream file(fname);
  if (!file.is_open())
	  return NULL;

  file >> type;
  file.close();

  switch(type){
  case IO::MYAVATARPARAMS:
    model =  new myAvatarParams(fname);
    break;
  default:    
    file.open(fname,std::ios::binary);
    if (!file.is_open())
		return NULL;

    file.read(reinterpret_cast<char*>(&type), sizeof(type));
    file.close();
    if(type == IOBinary::MYAVATARPARAMS)
      model = new myAvatarParams(fname, true);
    else
      printf("ERROR(%s,%d) : unknown avatar parameter type %d\n", 
	     __FILE__,__LINE__,type);
  }
  return model;
}
