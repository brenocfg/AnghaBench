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
struct SiS_Private {unsigned char* VirtualRomBase; int SiS_VBInfo; unsigned short CModeFlag; scalar_t__ ChipType; int SiS_IF_DEF_LVDS; int SiS_VGAHT; int SiS_VGAHDE; int SiS_VBType; unsigned short SiS_HT; unsigned short SiS_HDE; int SiS_LCDInfo; scalar_t__ SiS_LCDResInfo; unsigned short CHSyncStart; unsigned short CHSyncEnd; unsigned char* CCRT1CRTC; int SiS_TVMode; int SiS_VGAVT; scalar_t__ SiS_IF_DEF_CH70xx; int SiS_VGAVDE; unsigned short CVSyncStart; unsigned short CVSyncEnd; int PDC; int /*<<< orphan*/  SiS_Part1Port; int /*<<< orphan*/  SiS_ROMNew; scalar_t__ SiS_UseROM; scalar_t__ SiS_IF_DEF_FSTN; scalar_t__ SiS_IF_DEF_DSTN; TYPE_3__* SiS_CRT1Table; scalar_t__ UseCustomMode; TYPE_2__* SiS_EModeIDTable; int /*<<< orphan*/  SiS_UseWideCRT2; TYPE_1__* SiS_SModeIDTable; } ;
struct TYPE_6__ {unsigned char* CR; } ;
struct TYPE_5__ {unsigned short Ext_RESINFO; unsigned short Ext_ModeFlag; } ;
struct TYPE_4__ {unsigned short St_ModeFlag; } ;

/* Variables and functions */
 int DontExpandLCD ; 
 unsigned short DoubleScanMode ; 
 unsigned short HalfDCLK ; 
 scalar_t__ Panel_1024x768 ; 
 scalar_t__ Panel_1280x1024 ; 
 scalar_t__ Panel_1280x960 ; 
 scalar_t__ Panel_1600x1200 ; 
 scalar_t__ Panel_640x480 ; 
 scalar_t__ Panel_Custom ; 
 scalar_t__ SIS_300 ; 
 scalar_t__ SIS_315H ; 
 scalar_t__ SIS_650 ; 
 scalar_t__ SIS_661 ; 
 scalar_t__ SIS_740 ; 
 unsigned short SIS_RI_1280x1024 ; 
 unsigned short SIS_RI_1600x1200 ; 
 int SetCRT2ToAVIDEO ; 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToLCDA ; 
 int SetCRT2ToRAMDAC ; 
 int SetCRT2ToSVIDEO ; 
 int SetCRT2ToTV ; 
 int SetCRT2ToTVNoYPbPrHiVision ; 
 int SetInSlaveMode ; 
 unsigned short SiS_GetRefCRT1CRTC (struct SiS_Private*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiS_SetCRT2FIFO_300 (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT2FIFO_310 (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_SetCRT2Offset (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetGroup1_301 (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetGroup1_LVDS (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int TVSet525p1024 ; 
 int TVSetNTSC1024 ; 
 int VB_NoLCD ; 
 int VB_SIS301 ; 
 int VB_SISVB ; 

__attribute__((used)) static void
SiS_SetGroup1(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex,
		unsigned short RefreshRateTableIndex)
{
#if defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
  unsigned char   *ROMAddr = SiS_Pr->VirtualRomBase;
#endif
  unsigned short  temp=0, tempax=0, tempbx=0, tempcx=0, bridgeadd=0;
  unsigned short  pushbx=0, CRT1Index=0, modeflag, resinfo=0;
#ifdef CONFIG_FB_SIS_315
  unsigned short  tempbl=0;
#endif

  if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) {
     SiS_SetGroup1_LVDS(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
     return;
  }

  if(ModeNo <= 0x13) {
     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
  } else if(SiS_Pr->UseCustomMode) {
     modeflag = SiS_Pr->CModeFlag;
  } else {
     CRT1Index = SiS_GetRefCRT1CRTC(SiS_Pr, RefreshRateTableIndex, SiS_Pr->SiS_UseWideCRT2);
     resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
  }

  SiS_SetCRT2Offset(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);

  if( ! ((SiS_Pr->ChipType >= SIS_315H) &&
         (SiS_Pr->SiS_IF_DEF_LVDS == 1) &&
         (SiS_Pr->SiS_VBInfo & SetInSlaveMode)) ) {

     if(SiS_Pr->ChipType < SIS_315H ) {
#ifdef CONFIG_FB_SIS_300
	SiS_SetCRT2FIFO_300(SiS_Pr, ModeNo);
#endif
     } else {
#ifdef CONFIG_FB_SIS_315
	SiS_SetCRT2FIFO_310(SiS_Pr);
#endif
     }

     /* 1. Horizontal setup */

     if(SiS_Pr->ChipType < SIS_315H ) {

#ifdef CONFIG_FB_SIS_300   /* ------------- 300 series --------------*/

	temp = (SiS_Pr->SiS_VGAHT - 1) & 0x0FF;   		  /* BTVGA2HT 0x08,0x09 */
	SiS_SetReg(SiS_Pr->SiS_Part1Port,0x08,temp);              /* CRT2 Horizontal Total */

	temp = (((SiS_Pr->SiS_VGAHT - 1) & 0xFF00) >> 8) << 4;
	SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x09,0x0f,temp);    /* CRT2 Horizontal Total Overflow [7:4] */

	temp = (SiS_Pr->SiS_VGAHDE + 12) & 0x0FF;                 /* BTVGA2HDEE 0x0A,0x0C */
	SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0A,temp);              /* CRT2 Horizontal Display Enable End */

	pushbx = SiS_Pr->SiS_VGAHDE + 12;                         /* bx  BTVGA2HRS 0x0B,0x0C */
	tempcx = (SiS_Pr->SiS_VGAHT - SiS_Pr->SiS_VGAHDE) >> 2;
	tempbx = pushbx + tempcx;
	tempcx <<= 1;
	tempcx += tempbx;

	bridgeadd = 12;

#endif /* CONFIG_FB_SIS_300 */

     } else {

#ifdef CONFIG_FB_SIS_315  /* ------------------- 315/330 series --------------- */

	tempcx = SiS_Pr->SiS_VGAHT;				  /* BTVGA2HT 0x08,0x09 */
	if(modeflag & HalfDCLK) {
	   if(SiS_Pr->SiS_VBType & VB_SISVB) {
	      tempcx >>= 1;
	   } else {
	      tempax = SiS_Pr->SiS_VGAHDE >> 1;
	      tempcx = SiS_Pr->SiS_HT - SiS_Pr->SiS_HDE + tempax;
	      if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
	         tempcx = SiS_Pr->SiS_HT - tempax;
	      }
	   }
	}
	tempcx--;
	SiS_SetReg(SiS_Pr->SiS_Part1Port,0x08,tempcx);            /* CRT2 Horizontal Total */
	temp = (tempcx >> 4) & 0xF0;
	SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x09,0x0F,temp);    /* CRT2 Horizontal Total Overflow [7:4] */

	tempcx = SiS_Pr->SiS_VGAHT;				  /* BTVGA2HDEE 0x0A,0x0C */
	tempbx = SiS_Pr->SiS_VGAHDE;
	tempcx -= tempbx;
	tempcx >>= 2;
	if(modeflag & HalfDCLK) {
	   tempbx >>= 1;
	   tempcx >>= 1;
	}
	tempbx += 16;

	SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0A,tempbx);            /* CRT2 Horizontal Display Enable End */

	pushbx = tempbx;
	tempcx >>= 1;
	tempbx += tempcx;
	tempcx += tempbx;

	bridgeadd = 16;

	if(SiS_Pr->SiS_VBType & VB_SISVB) {
	   if(SiS_Pr->ChipType >= SIS_661) {
	      if((SiS_Pr->SiS_LCDResInfo == Panel_1600x1200) ||
		 (SiS_Pr->SiS_LCDResInfo == Panel_1280x1024)) {
		 if(resinfo == SIS_RI_1280x1024) {
		    tempcx = (tempcx & 0xff00) | 0x30;
		 } else if(resinfo == SIS_RI_1600x1200) {
		    tempcx = (tempcx & 0xff00) | 0xff;
		 }
	      }
	   }
        }

#endif  /* CONFIG_FB_SIS_315 */

     }  /* 315/330 series */

     if(SiS_Pr->SiS_VBType & VB_SISVB) {

	if(SiS_Pr->UseCustomMode) {
	   tempbx = SiS_Pr->CHSyncStart + bridgeadd;
	   tempcx = SiS_Pr->CHSyncEnd + bridgeadd;
	   tempax = SiS_Pr->SiS_VGAHT;
	   if(modeflag & HalfDCLK) tempax >>= 1;
	   tempax--;
	   if(tempcx > tempax) tempcx = tempax;
	}

	if(SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC) {
	   unsigned char cr4, cr14, cr5, cr15;
	   if(SiS_Pr->UseCustomMode) {
	      cr4  = SiS_Pr->CCRT1CRTC[4];
	      cr14 = SiS_Pr->CCRT1CRTC[14];
	      cr5  = SiS_Pr->CCRT1CRTC[5];
	      cr15 = SiS_Pr->CCRT1CRTC[15];
	   } else {
	      cr4  = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[4];
	      cr14 = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[14];
	      cr5  = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[5];
	      cr15 = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[15];
	   }
	   tempbx = ((cr4 | ((cr14 & 0xC0) << 2)) - 3) << 3; 		    /* (VGAHRS-3)*8 */
	   tempcx = (((cr5 & 0x1f) | ((cr15 & 0x04) << (5-2))) - 3) << 3;   /* (VGAHRE-3)*8 */
	   tempcx &= 0x00FF;
	   tempcx |= (tempbx & 0xFF00);
	   tempbx += bridgeadd;
	   tempcx += bridgeadd;
	   tempax = SiS_Pr->SiS_VGAHT;
	   if(modeflag & HalfDCLK) tempax >>= 1;
	   tempax--;
	   if(tempcx > tempax) tempcx = tempax;
	}

	if(SiS_Pr->SiS_TVMode & (TVSetNTSC1024 | TVSet525p1024)) {
	   tempbx = 1040;
	   tempcx = 1044;   /* HWCursor bug! */
	}

     }

     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0B,tempbx);            	  /* CRT2 Horizontal Retrace Start */

     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0D,tempcx);               /* CRT2 Horizontal Retrace End */

     temp = ((tempbx >> 8) & 0x0F) | ((pushbx >> 4) & 0xF0);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0C,temp);		  /* Overflow */

     /* 2. Vertical setup */

     tempcx = SiS_Pr->SiS_VGAVT - 1;
     temp = tempcx & 0x00FF;

     if(SiS_Pr->ChipType < SIS_661) {
        if(SiS_Pr->SiS_IF_DEF_LVDS == 1) {
	   if(SiS_Pr->ChipType < SIS_315H) {
	      if(SiS_Pr->SiS_IF_DEF_CH70xx != 0) {
	         if(SiS_Pr->SiS_VBInfo & (SetCRT2ToSVIDEO | SetCRT2ToAVIDEO)) {
	            temp--;
	         }
	      }
	   } else {
	      temp--;
	   }
	} else if(SiS_Pr->ChipType >= SIS_315H) {
	   temp--;
	}
     }
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0E,temp);                 /* CRT2 Vertical Total */

     tempbx = SiS_Pr->SiS_VGAVDE - 1;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0F,tempbx);               /* CRT2 Vertical Display Enable End */

     temp = ((tempbx >> 5) & 0x38) | ((tempcx >> 8) & 0x07);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x12,temp);                 /* Overflow */

     if((SiS_Pr->ChipType >= SIS_315H) && (SiS_Pr->ChipType < SIS_661)) {
	tempbx++;
	tempax = tempbx;
	tempcx++;
	tempcx -= tempax;
	tempcx >>= 2;
	tempbx += tempcx;
	if(tempcx < 4) tempcx = 4;
	tempcx >>= 2;
	tempcx += tempbx;
	tempcx++;
     } else {
	tempbx = (SiS_Pr->SiS_VGAVT + SiS_Pr->SiS_VGAVDE) >> 1;                 /*  BTVGA2VRS     0x10,0x11   */
	tempcx = ((SiS_Pr->SiS_VGAVT - SiS_Pr->SiS_VGAVDE) >> 4) + tempbx + 1;  /*  BTVGA2VRE     0x11        */
     }

     if(SiS_Pr->SiS_VBType & VB_SISVB) {
	if(SiS_Pr->UseCustomMode) {
	   tempbx = SiS_Pr->CVSyncStart;
	   tempcx = SiS_Pr->CVSyncEnd;
	}
	if(SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC) {
	   unsigned char cr8, cr7, cr13;
	   if(SiS_Pr->UseCustomMode) {
	      cr8    = SiS_Pr->CCRT1CRTC[8];
	      cr7    = SiS_Pr->CCRT1CRTC[7];
	      cr13   = SiS_Pr->CCRT1CRTC[13];
	      tempcx = SiS_Pr->CCRT1CRTC[9];
	   } else {
	      cr8    = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[8];
	      cr7    = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[7];
	      cr13   = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[13];
	      tempcx = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[9];
	   }
	   tempbx = cr8;
	   if(cr7  & 0x04) tempbx |= 0x0100;
	   if(cr7  & 0x80) tempbx |= 0x0200;
	   if(cr13 & 0x08) tempbx |= 0x0400;
	}
     }
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x10,tempbx);               /* CRT2 Vertical Retrace Start */

     temp = ((tempbx >> 4) & 0x70) | (tempcx & 0x0F);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x11,temp);                 /* CRT2 Vert. Retrace End; Overflow */

     /* 3. Panel delay compensation */

     if(SiS_Pr->ChipType < SIS_315H) {

#ifdef CONFIG_FB_SIS_300  /* ---------- 300 series -------------- */

	if(SiS_Pr->SiS_VBType & VB_SISVB) {
	   temp = 0x20;
	   if(SiS_Pr->ChipType == SIS_300) {
	      temp = 0x10;
	      if(SiS_Pr->SiS_LCDResInfo == Panel_1024x768)  temp = 0x2c;
	      if(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) temp = 0x20;
	   }
	   if(SiS_Pr->SiS_VBType & VB_SIS301) {
	      if(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) temp = 0x20;
	   }
	   if(SiS_Pr->SiS_LCDResInfo == Panel_1280x960)     temp = 0x24;
	   if(SiS_Pr->SiS_LCDResInfo == Panel_Custom)       temp = 0x2c;
	   if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) 	    temp = 0x08;
	   if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) {
	      if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) 	    temp = 0x2c;
	      else 					    temp = 0x20;
	   }
	   if(SiS_Pr->SiS_UseROM) {
	      if(ROMAddr[0x220] & 0x80) {
		 if(SiS_Pr->SiS_VBInfo & SetCRT2ToTVNoYPbPrHiVision)
		    temp = ROMAddr[0x221];
		 else if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision)
		    temp = ROMAddr[0x222];
		 else if(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024)
		    temp = ROMAddr[0x223];
		 else
		    temp = ROMAddr[0x224];
	      }
	   }
	   if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {
	      if(SiS_Pr->PDC != -1)  temp = SiS_Pr->PDC;
	   }

	} else {
	   temp = 0x20;
	   if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) {
	      if(SiS_Pr->SiS_LCDResInfo == Panel_640x480) temp = 0x04;
	   }
	   if(SiS_Pr->SiS_UseROM) {
	      if(ROMAddr[0x220] & 0x80) {
	         temp = ROMAddr[0x220];
	      }
	   }
	   if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {
	      if(SiS_Pr->PDC != -1) temp = SiS_Pr->PDC;
	   }
	}

	temp &= 0x3c;

	SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,~0x3C,temp);   /* Panel Link Delay Compensation; (Software Command Reset; Power Saving) */

#endif  /* CONFIG_FB_SIS_300 */

     } else {

#ifdef CONFIG_FB_SIS_315   /* --------------- 315/330 series ---------------*/

	if(SiS_Pr->ChipType < SIS_661) {

	   if(SiS_Pr->SiS_IF_DEF_LVDS == 1) {

	      if(SiS_Pr->ChipType == SIS_740) temp = 0x03;
	      else 		              temp = 0x00;

	      if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) temp = 0x0a;
	      tempbl = 0xF0;
	      if(SiS_Pr->ChipType == SIS_650) {
		 if(SiS_Pr->SiS_IF_DEF_CH70xx != 0) {
		    if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) tempbl = 0x0F;
		 }
	      }

	      if(SiS_Pr->SiS_IF_DEF_DSTN || SiS_Pr->SiS_IF_DEF_FSTN) {
		 temp = 0x08;
		 tempbl = 0;
		 if((SiS_Pr->SiS_UseROM) && (!(SiS_Pr->SiS_ROMNew))) {
		    if(ROMAddr[0x13c] & 0x80) tempbl = 0xf0;
		 }
	      }

	      SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2D,tempbl,temp);	    /* Panel Link Delay Compensation */
	   }

	} /* < 661 */

	tempax = 0;
	if(modeflag & DoubleScanMode) tempax |= 0x80;
	if(modeflag & HalfDCLK)       tempax |= 0x40;
	SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2C,0x3f,tempax);

#endif  /* CONFIG_FB_SIS_315 */

     }

  }  /* Slavemode */

  if(SiS_Pr->SiS_VBType & VB_SISVB) {
     if((SiS_Pr->SiS_VBType & VB_NoLCD) && (SiS_Pr->SiS_VBInfo & SetCRT2ToLCD)) {
	/* For 301BDH with LCD, we set up the Panel Link */
	SiS_SetGroup1_LVDS(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
     } else if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) {
	SiS_SetGroup1_301(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
     }
  } else {
     if(SiS_Pr->ChipType < SIS_315H) {
	SiS_SetGroup1_LVDS(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
     } else {
	if(SiS_Pr->SiS_IF_DEF_CH70xx != 0) {
	   if((!(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) || (SiS_Pr->SiS_VBInfo & SetInSlaveMode)) {
	      SiS_SetGroup1_LVDS(SiS_Pr, ModeNo,ModeIdIndex,RefreshRateTableIndex);
	   }
	} else {
	   SiS_SetGroup1_LVDS(SiS_Pr, ModeNo,ModeIdIndex,RefreshRateTableIndex);
	}
     }
  }
}