#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {unsigned short CModeFlag; int SiS_IF_DEF_LVDS; int SiS_VBType; scalar_t__ ChipType; int SiS_VBInfo; int SiS_LCDResInfo; unsigned short SiS_LCDHDES; unsigned short SiS_HDE; int SiS_LCDInfo; unsigned short PanelXRes; unsigned short SiS_HT; int PanelHRS; int PanelHRE; unsigned short SiS_VGAVDE; unsigned short PanelYRes; unsigned short SiS_LCDVDES; unsigned short SiS_VT; unsigned short SiS_VGAVT; int PanelVRS; int PanelVRE; unsigned int SiS_VDE; int SiS_SetFlag; int ChipRevision; int SiS_IF_DEF_CH70xx; unsigned int SiS_VGAHDE; int SiS_VGAHT; unsigned char* VirtualRomBase; int SiS_LCDTypeInfo; int /*<<< orphan*/  SiS_Part1Port; scalar_t__ SiS_IF_DEF_FSTN; scalar_t__ SiS_IF_DEF_DSTN; scalar_t__ SiS_UseROM; scalar_t__ SiS_IF_DEF_TRUMPION; int /*<<< orphan*/  SiS_Part4Port; int /*<<< orphan*/  SiS_P3c4; TYPE_3__* SiS_RefIndex; TYPE_2__* SiS_EModeIDTable; scalar_t__ UseCustomMode; TYPE_1__* SiS_SModeIDTable; } ;
struct TYPE_6__ {unsigned short Ext_CRT2CRTC; } ;
struct TYPE_5__ {unsigned short Ext_ModeFlag; unsigned short Ext_RESINFO; } ;
struct TYPE_4__ {unsigned short St_ModeFlag; unsigned short St_ResInfo; unsigned short St_CRT2CRTC; } ;

/* Variables and functions */
 int DontExpandLCD ; 
 int EnableLVDSDDA ; 
 unsigned short HalfDCLK ; 
 scalar_t__ IS_SIS330 ; 
 scalar_t__ IS_SIS740 ; 
 int LCDPass11 ; 
 int LCDRGB18Bit ; 
#define  Panel_1024x600 131 
#define  Panel_1024x768 130 
 int Panel_1280x1024 ; 
 int Panel_320x240_1 ; 
 int Panel_320x240_2 ; 
 int Panel_320x240_3 ; 
#define  Panel_640x480 129 
#define  Panel_800x600 128 
 scalar_t__ SIS_315H ; 
 scalar_t__ SIS_740 ; 
 unsigned short SIS_RI_1024x600 ; 
 unsigned short SIS_RI_1024x768 ; 
 unsigned short SIS_RI_800x600 ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToLCDA ; 
 int SetCRT2ToTV ; 
 int SetInSlaveMode ; 
 unsigned char** SiS300_TrumpionData ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetTrumpionBlock (struct SiS_Private*,unsigned char*) ; 
 int VB_NoLCD ; 
 int VB_SIS30xC ; 
 int VB_SISLVDS ; 
 int VB_SISPART4SCALER ; 
 int VB_SISVB ; 

__attribute__((used)) static void
SiS_SetGroup1_LVDS(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex,
		unsigned short RefreshRateTableIndex)
{
  unsigned short modeflag, resinfo = 0;
  unsigned short push2, tempax, tempbx, tempcx, temp;
  unsigned int   tempeax = 0, tempebx, tempecx, tempvcfact = 0;
  bool islvds = false, issis  = false, chkdclkfirst = false;
#ifdef CONFIG_FB_SIS_300
  unsigned short crt2crtc = 0;
#endif
#ifdef CONFIG_FB_SIS_315
  unsigned short pushcx;
#endif

  if(ModeNo <= 0x13) {
     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
     resinfo = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ResInfo;
#ifdef CONFIG_FB_SIS_300
     crt2crtc = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
#endif
  } else if(SiS_Pr->UseCustomMode) {
     modeflag = SiS_Pr->CModeFlag;
  } else {
     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
     resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
#ifdef CONFIG_FB_SIS_300
     crt2crtc = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;
#endif
  }

  /* is lvds if really LVDS, or 301B-DH with external LVDS transmitter */
  if((SiS_Pr->SiS_IF_DEF_LVDS == 1) || (SiS_Pr->SiS_VBType & VB_NoLCD)) {
     islvds = true;
  }

  /* is really sis if sis bridge, but not 301B-DH */
  if((SiS_Pr->SiS_VBType & VB_SISVB) && (!(SiS_Pr->SiS_VBType & VB_NoLCD))) {
     issis = true;
  }

  if((SiS_Pr->ChipType >= SIS_315H) && (islvds) && (!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA))) {
     if((!SiS_Pr->SiS_IF_DEF_FSTN) && (!SiS_Pr->SiS_IF_DEF_DSTN)) {
        chkdclkfirst = true;
     }
  }

#ifdef CONFIG_FB_SIS_315
  if((SiS_Pr->ChipType >= SIS_315H) && (SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) {
     if(IS_SIS330) {
        SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2D,0x10);
     } else if(IS_SIS740) {
        if(islvds) {
           SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,0xfb,0x04);
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2D,0x03);
        } else if(SiS_Pr->SiS_VBType & VB_SISVB) {
           SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2D,0x10);
        }
     } else {
        if(islvds) {
           SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,0xfb,0x04);
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2D,0x00);
        } else if(SiS_Pr->SiS_VBType & VB_SISVB) {
           SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2D,0x0f);
	   if(SiS_Pr->SiS_VBType & VB_SIS30xC) {
	      if((SiS_Pr->SiS_LCDResInfo == Panel_1024x768) ||
	         (SiS_Pr->SiS_LCDResInfo == Panel_1280x1024)) {
	         SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2D,0x20);
	      }
	   }
        }
     }
  }
#endif

  /* Horizontal */

  tempax = SiS_Pr->SiS_LCDHDES;
  if(islvds) {
     if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) {
	if(!SiS_Pr->SiS_IF_DEF_FSTN && !SiS_Pr->SiS_IF_DEF_DSTN) {
	   if((SiS_Pr->SiS_LCDResInfo == Panel_640x480) &&
	      (!(SiS_Pr->SiS_VBInfo & SetInSlaveMode))) {
	      tempax -= 8;
	   }
	}
     }
  }

  temp = (tempax & 0x0007);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1A,temp);			/* BPLHDESKEW[2:0]   */
  temp = (tempax >> 3) & 0x00FF;
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x16,temp);			/* BPLHDESKEW[10:3]  */

  tempbx = SiS_Pr->SiS_HDE;
  if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) {
     if(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) {
        tempbx = SiS_Pr->PanelXRes;
     }
     if((SiS_Pr->SiS_LCDResInfo == Panel_320x240_1) ||
        (SiS_Pr->SiS_LCDResInfo == Panel_320x240_2) ||
        (SiS_Pr->SiS_LCDResInfo == Panel_320x240_3)) {
        tempbx >>= 1;
     }
  }

  tempax += tempbx;
  if(tempax >= SiS_Pr->SiS_HT) tempax -= SiS_Pr->SiS_HT;

  temp = tempax;
  if(temp & 0x07) temp += 8;
  temp >>= 3;
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x17,temp);			/* BPLHDEE  */

  tempcx = (SiS_Pr->SiS_HT - tempbx) >> 2;

  if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) {
     if(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) {
        if(SiS_Pr->PanelHRS != 999) tempcx = SiS_Pr->PanelHRS;
     }
  }

  tempcx += tempax;
  if(tempcx >= SiS_Pr->SiS_HT) tempcx -= SiS_Pr->SiS_HT;

  temp = (tempcx >> 3) & 0x00FF;
  if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) {
     if(SiS_Pr->SiS_IF_DEF_TRUMPION) {
	if(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) {
	   switch(ModeNo) {
	   case 0x04:
	   case 0x05:
	   case 0x0d: temp = 0x56; break;
	   case 0x10: temp = 0x60; break;
	   case 0x13: temp = 0x5f; break;
	   case 0x40:
	   case 0x41:
	   case 0x4f:
	   case 0x43:
	   case 0x44:
	   case 0x62:
	   case 0x56:
	   case 0x53:
	   case 0x5d:
	   case 0x5e: temp = 0x54; break;
	   }
	}
     }
  }
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x14,temp);			/* BPLHRS */

  if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) {
     temp += 2;
     if(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) {
	temp += 8;
	if(SiS_Pr->PanelHRE != 999) {
	   temp = tempcx + SiS_Pr->PanelHRE;
	   if(temp >= SiS_Pr->SiS_HT) temp -= SiS_Pr->SiS_HT;
	   temp >>= 3;
	}
     }
  } else {
     temp += 10;
  }

  temp &= 0x1F;
  temp |= ((tempcx & 0x07) << 5);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x15,temp);			/* BPLHRE */

  /* Vertical */

  tempax = SiS_Pr->SiS_VGAVDE;
  if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) {
     if(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) {
	tempax = SiS_Pr->PanelYRes;
     }
  }

  tempbx = SiS_Pr->SiS_LCDVDES + tempax;
  if(tempbx >= SiS_Pr->SiS_VT) tempbx -= SiS_Pr->SiS_VT;

  push2 = tempbx;

  tempcx = SiS_Pr->SiS_VGAVT - SiS_Pr->SiS_VGAVDE;
  if(SiS_Pr->ChipType < SIS_315H) {
     if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) {
	if(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) {
	   tempcx = SiS_Pr->SiS_VGAVT - SiS_Pr->PanelYRes;
	}
     }
  }
  if(islvds) tempcx >>= 1;
  else       tempcx >>= 2;

  if( (SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) &&
      (!(SiS_Pr->SiS_LCDInfo & LCDPass11)) 		    &&
      (SiS_Pr->PanelVRS != 999) ) {
     tempcx = SiS_Pr->PanelVRS;
     tempbx += tempcx;
     if(issis) tempbx++;
  } else {
     tempbx += tempcx;
     if(SiS_Pr->ChipType < SIS_315H) tempbx++;
     else if(issis)                   tempbx++;
  }

  if(tempbx >= SiS_Pr->SiS_VT) tempbx -= SiS_Pr->SiS_VT;

  temp = tempbx & 0x00FF;
  if(SiS_Pr->SiS_IF_DEF_TRUMPION) {
     if(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) {
	if(ModeNo == 0x10) temp = 0xa9;
     }
  }
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x18,temp);			/* BPLVRS */

  tempcx >>= 3;
  tempcx++;

  if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) {
     if(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) {
        if(SiS_Pr->PanelVRE != 999) tempcx = SiS_Pr->PanelVRE;
     }
  }

  tempcx += tempbx;
  temp = tempcx & 0x000F;
  SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0xF0,temp);	/* BPLVRE  */

  temp = ((tempbx >> 8) & 0x07) << 3;
  if(SiS_Pr->SiS_IF_DEF_FSTN || SiS_Pr->SiS_IF_DEF_DSTN) {
     if(SiS_Pr->SiS_HDE != 640) {
        if(SiS_Pr->SiS_VGAVDE != SiS_Pr->SiS_VDE)  temp |= 0x40;
     }
  } else if(SiS_Pr->SiS_VGAVDE != SiS_Pr->SiS_VDE) temp |= 0x40;
  if(SiS_Pr->SiS_SetFlag & EnableLVDSDDA)          temp |= 0x40;
  tempbx = 0x87;
  if((SiS_Pr->ChipType >= SIS_315H) ||
     (SiS_Pr->ChipRevision >= 0x30)) {
     tempbx = 0x07;
     if((SiS_Pr->SiS_IF_DEF_CH70xx == 1) && (SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) {
	if(SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00) & 0x03)    temp |= 0x80;
     }
     /* Chrontel 701x operates in 24bit mode (8-8-8, 2x12bit multiplexed) via VGA2 */
     if(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit) {
	if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) {
	   if(SiS_GetReg(SiS_Pr->SiS_P3c4,0x06) & 0x10)      temp |= 0x80;
	} else {
	   if(SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00) & 0x01) temp |= 0x80;
	}
     }
  }
  SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x1A,tempbx,temp);

  tempbx = push2;						/* BPLVDEE */

  tempcx = SiS_Pr->SiS_LCDVDES;					/* BPLVDES */

  if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) {
     switch(SiS_Pr->SiS_LCDResInfo) {
     case Panel_640x480:
	tempbx = SiS_Pr->SiS_VGAVDE - 1;
	tempcx = SiS_Pr->SiS_VGAVDE;
	break;
     case Panel_800x600:
	if(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) {
	   if(resinfo == SIS_RI_800x600) tempcx++;
	}
	break;
     case Panel_1024x600:
	if(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) {
	   if(resinfo == SIS_RI_1024x600) tempcx++;
	   if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
	      if(resinfo == SIS_RI_800x600) tempcx++;
	   }
	}
	break;
     case Panel_1024x768:
	if(SiS_Pr->ChipType < SIS_315H) {
	   if(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) {
	      if(resinfo == SIS_RI_1024x768) tempcx++;
	   }
	}
	break;
     }
  }

  temp = ((tempbx >> 8) & 0x07) << 3;
  temp |= ((tempcx >> 8) & 0x07);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1D,temp);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1C,tempbx);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1B,tempcx);

  /* Vertical scaling */

  if(SiS_Pr->ChipType < SIS_315H) {

#ifdef CONFIG_FB_SIS_300      /* 300 series */
     tempeax = SiS_Pr->SiS_VGAVDE << 6;
     temp = (tempeax % (unsigned int)SiS_Pr->SiS_VDE);
     tempeax = tempeax / (unsigned int)SiS_Pr->SiS_VDE;
     if(temp) tempeax++;

     if(SiS_Pr->SiS_SetFlag & EnableLVDSDDA) tempeax = 0x3F;

     temp = (unsigned short)(tempeax & 0x00FF);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1E,temp);      	/* BPLVCFACT */
     tempvcfact = temp;
#endif /* CONFIG_FB_SIS_300 */

  } else {

#ifdef CONFIG_FB_SIS_315  /* 315 series */
     tempeax = SiS_Pr->SiS_VGAVDE << 18;
     tempebx = SiS_Pr->SiS_VDE;
     temp = (tempeax % tempebx);
     tempeax = tempeax / tempebx;
     if(temp) tempeax++;
     tempvcfact = tempeax;

     temp = (unsigned short)(tempeax & 0x00FF);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x37,temp);
     temp = (unsigned short)((tempeax & 0x00FF00) >> 8);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x36,temp);
     temp = (unsigned short)((tempeax & 0x00030000) >> 16);
     if(SiS_Pr->SiS_VDE == SiS_Pr->SiS_VGAVDE) temp |= 0x04;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x35,temp);

     if(SiS_Pr->SiS_VBType & VB_SISPART4SCALER) {
        temp = (unsigned short)(tempeax & 0x00FF);
        SiS_SetReg(SiS_Pr->SiS_Part4Port,0x3c,temp);
        temp = (unsigned short)((tempeax & 0x00FF00) >> 8);
        SiS_SetReg(SiS_Pr->SiS_Part4Port,0x3b,temp);
        temp = (unsigned short)(((tempeax & 0x00030000) >> 16) << 6);
        SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x3a,0x3f,temp);
        temp = 0;
        if(SiS_Pr->SiS_VDE != SiS_Pr->SiS_VGAVDE) temp |= 0x08;
        SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x30,0xf3,temp);
     }
#endif

  }

  /* Horizontal scaling */

  tempeax = SiS_Pr->SiS_VGAHDE;		/* 1f = ( (VGAHDE * 65536) / ( (VGAHDE * 65536) / HDE ) ) - 1*/
  if(chkdclkfirst) {
     if(modeflag & HalfDCLK) tempeax >>= 1;
  }
  tempebx = tempeax << 16;
  if(SiS_Pr->SiS_HDE == tempeax) {
     tempecx = 0xFFFF;
  } else {
     tempecx = tempebx / SiS_Pr->SiS_HDE;
     if(SiS_Pr->ChipType >= SIS_315H) {
        if(tempebx % SiS_Pr->SiS_HDE) tempecx++;
     }
  }

  if(SiS_Pr->ChipType >= SIS_315H) {
     tempeax = (tempebx / tempecx) - 1;
  } else {
     tempeax = ((SiS_Pr->SiS_VGAHT << 16) / tempecx) - 1;
  }
  tempecx = (tempecx << 16) | (tempeax & 0xFFFF);
  temp = (unsigned short)(tempecx & 0x00FF);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1F,temp);

  if(SiS_Pr->ChipType >= SIS_315H) {
     tempeax = (SiS_Pr->SiS_VGAVDE << 18) / tempvcfact;
     tempbx = (unsigned short)(tempeax & 0xFFFF);
  } else {
     tempeax = SiS_Pr->SiS_VGAVDE << 6;
     tempbx = tempvcfact & 0x3f;
     if(tempbx == 0) tempbx = 64;
     tempeax /= tempbx;
     tempbx = (unsigned short)(tempeax & 0xFFFF);
  }
  if(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) tempbx--;
  if(SiS_Pr->SiS_SetFlag & EnableLVDSDDA) {
     if((!SiS_Pr->SiS_IF_DEF_FSTN) && (!SiS_Pr->SiS_IF_DEF_DSTN)) tempbx = 1;
     else if(SiS_Pr->SiS_LCDResInfo != Panel_640x480)             tempbx = 1;
  }

  temp = ((tempbx >> 8) & 0x07) << 3;
  temp = temp | ((tempecx >> 8) & 0x07);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x20,temp);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x21,tempbx);

  tempecx >>= 16;						/* BPLHCFACT  */
  if(!chkdclkfirst) {
     if(modeflag & HalfDCLK) tempecx >>= 1;
  }
  temp = (unsigned short)((tempecx & 0xFF00) >> 8);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x22,temp);
  temp = (unsigned short)(tempecx & 0x00FF);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x23,temp);

#ifdef CONFIG_FB_SIS_315
  if(SiS_Pr->ChipType >= SIS_315H) {
     if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) {
        if((islvds) || (SiS_Pr->SiS_VBInfo & VB_SISLVDS)) {
           SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1e,0x20);
	}
     } else {
        if(islvds) {
           if(SiS_Pr->ChipType == SIS_740) {
              SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1e,0x03);
           } else {
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1e,0x23);
           }
        }
     }
  }
#endif

#ifdef CONFIG_FB_SIS_300
  if(SiS_Pr->SiS_IF_DEF_TRUMPION) {
     unsigned char *ROMAddr = SiS_Pr->VirtualRomBase;
     unsigned char *trumpdata;
     int   i, j = crt2crtc;
     unsigned char TrumpMode13[4]   = { 0x01, 0x10, 0x2c, 0x00 };
     unsigned char TrumpMode10_1[4] = { 0x01, 0x10, 0x27, 0x00 };
     unsigned char TrumpMode10_2[4] = { 0x01, 0x16, 0x10, 0x00 };

     if(SiS_Pr->SiS_UseROM) {
	trumpdata = &ROMAddr[0x8001 + (j * 80)];
     } else {
	if(SiS_Pr->SiS_LCDTypeInfo == 0x0e) j += 7;
	trumpdata = &SiS300_TrumpionData[j][0];
     }

     SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x02,0xbf);
     for(i=0; i<5; i++) {
	SiS_SetTrumpionBlock(SiS_Pr, trumpdata);
     }
     if(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) {
	if(ModeNo == 0x13) {
	   for(i=0; i<4; i++) {
	      SiS_SetTrumpionBlock(SiS_Pr, &TrumpMode13[0]);
	   }
	} else if(ModeNo == 0x10) {
	   for(i=0; i<4; i++) {
	      SiS_SetTrumpionBlock(SiS_Pr, &TrumpMode10_1[0]);
	      SiS_SetTrumpionBlock(SiS_Pr, &TrumpMode10_2[0]);
	   }
	}
     }
     SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x02,0x40);
  }
#endif

#ifdef CONFIG_FB_SIS_315
  if(SiS_Pr->SiS_IF_DEF_FSTN || SiS_Pr->SiS_IF_DEF_DSTN) {
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x25,0x00);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x26,0x00);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x27,0x00);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x28,0x87);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x29,0x5A);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2A,0x4B);
     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x44,~0x07,0x03);
     tempax = SiS_Pr->SiS_HDE;					/* Blps = lcdhdee(lcdhdes+HDE) + 64 */
     if(SiS_Pr->SiS_LCDResInfo == Panel_320x240_1 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_2 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_3) tempax >>= 1;
     tempax += 64;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x38,tempax & 0xff);
     temp = (tempax >> 8) << 3;
     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x35,~0x078,temp);
     tempax += 32;						/* Blpe = lBlps+32 */
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x39,tempax & 0xff);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3A,0x00);		/* Bflml = 0 */
     SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x3C,~0x007);

     tempax = SiS_Pr->SiS_VDE;
     if(SiS_Pr->SiS_LCDResInfo == Panel_320x240_1 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_2 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_3) tempax >>= 1;
     tempax >>= 1;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3B,tempax & 0xff);
     temp = (tempax >> 8) << 3;
     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x3C,~0x038,temp);

     tempeax = SiS_Pr->SiS_HDE;
     if(SiS_Pr->SiS_LCDResInfo == Panel_320x240_1 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_2 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_3) tempeax >>= 1;
     tempeax <<= 2;			 			/* BDxFIFOSTOP = (HDE*4)/128 */
     temp = tempeax & 0x7f;
     tempeax >>= 7;
     if(temp) tempeax++;
     temp = tempeax & 0x3f;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x45,temp);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3F,0x00);		/* BDxWadrst0 */
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3E,0x00);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3D,0x10);
     SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x3C,~0x040);

     tempax = SiS_Pr->SiS_HDE;
     if(SiS_Pr->SiS_LCDResInfo == Panel_320x240_1 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_2 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_3) tempax >>= 1;
     tempax >>= 4;						/* BDxWadroff = HDE*4/8/8 */
     pushcx = tempax;
     temp = tempax & 0x00FF;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x43,temp);
     temp = ((tempax & 0xFF00) >> 8) << 3;
     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port, 0x44, 0x07, temp);

     tempax = SiS_Pr->SiS_VDE;				 	/* BDxWadrst1 = BDxWadrst0 + BDxWadroff * VDE */
     if(SiS_Pr->SiS_LCDResInfo == Panel_320x240_1 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_2 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_3) tempax >>= 1;
     tempeax = tempax * pushcx;
     temp = tempeax & 0xFF;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x42,temp);
     temp = (tempeax & 0xFF00) >> 8;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x41,temp);
     temp = ((tempeax & 0xFF0000) >> 16) | 0x10;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x40,temp);
     temp = ((tempeax & 0x01000000) >> 24) << 7;
     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port, 0x3C, 0x7F, temp);

     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2F,0x03);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x03,0x50);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x04,0x00);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2F,0x01);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x19,0x38);

     if(SiS_Pr->SiS_IF_DEF_FSTN) {
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2b,0x02);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2c,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2d,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x35,0x0c);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x36,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x37,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x38,0x80);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x39,0xA0);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3a,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3b,0xf0);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3c,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3d,0x10);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3e,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3f,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x40,0x10);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x41,0x25);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x42,0x80);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x43,0x14);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x44,0x03);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x45,0x0a);
     }
  }
#endif  /* CONFIG_FB_SIS_315 */
}