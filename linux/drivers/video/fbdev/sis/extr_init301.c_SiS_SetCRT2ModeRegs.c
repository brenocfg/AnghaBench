#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct SiS_Private {unsigned char* VirtualRomBase; int SiS_VBInfo; scalar_t__ ChipType; short SiS_ModeType; int SiS_VBType; int SiS_IF_DEF_LVDS; int PanelXRes; int PanelYRes; int SiS_TVMode; int SiS_TVBlue; scalar_t__ SiS_IF_DEF_CH70xx; int /*<<< orphan*/  SiS_Part1Port; int /*<<< orphan*/  SiS_Part4Port; scalar_t__ SiS_ROMNew; int /*<<< orphan*/  SiS_P3c4; } ;

/* Variables and functions */
 unsigned short CRT2Mode ; 
 int DisableCRT2Display ; 
 int DriverMode ; 
 int /*<<< orphan*/  IS_SIS65x ; 
 scalar_t__ IS_SIS740 ; 
 short ModeVGA ; 
 scalar_t__ SIS_315H ; 
 scalar_t__ SIS_550 ; 
 scalar_t__ SIS_661 ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToLCDA ; 
 int SetCRT2ToRAMDAC ; 
 int SetCRT2ToTV ; 
 int SetInSlaveMode ; 
 unsigned short SiS_GetModeFlag (struct SiS_Private*,unsigned short,unsigned short) ; 
 unsigned short SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SiS_IsDualEdge (struct SiS_Private*) ; 
 scalar_t__ SiS_IsDualLink (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 
 int TVRPLLDIV2XO ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 int VB_NoLCD ; 
 int VB_SIS301 ; 
 int VB_SIS30xBLV ; 
 int VB_SIS30xCLV ; 
 int VB_SISLVDS ; 
 int VB_SISVB ; 

__attribute__((used)) static void
SiS_SetCRT2ModeRegs(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex)
{
  unsigned short i, j, modeflag, tempah=0;
  short tempcl;
#if defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
  unsigned short tempbl;
#endif
#ifdef CONFIG_FB_SIS_315
  unsigned char  *ROMAddr = SiS_Pr->VirtualRomBase;
  unsigned short tempah2, tempbl2;
#endif

  modeflag = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);

  if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) {

     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x00,0xAF,0x40);
     SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2E,0xF7);

  } else {

     for(i=0,j=4; i<3; i++,j++) SiS_SetReg(SiS_Pr->SiS_Part1Port,j,0);
     if(SiS_Pr->ChipType >= SIS_315H) {
        SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x02,0x7F);
     }

     tempcl = SiS_Pr->SiS_ModeType;

     if(SiS_Pr->ChipType < SIS_315H) {

#ifdef CONFIG_FB_SIS_300    /* ---- 300 series ---- */

	/* For 301BDH: (with LCD via LVDS) */
	if(SiS_Pr->SiS_VBType & VB_NoLCD) {
	   tempbl = SiS_GetReg(SiS_Pr->SiS_P3c4,0x32);
	   tempbl &= 0xef;
	   tempbl |= 0x02;
	   if((SiS_Pr->SiS_VBInfo & SetCRT2ToTV) || (SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC)) {
	      tempbl |= 0x10;
	      tempbl &= 0xfd;
	   }
	   SiS_SetReg(SiS_Pr->SiS_P3c4,0x32,tempbl);
	}

	if(ModeNo > 0x13) {
	   tempcl -= ModeVGA;
	   if(tempcl >= 0) {
	      tempah = ((0x10 >> tempcl) | 0x80);
	   }
	} else tempah = 0x80;

	if(SiS_Pr->SiS_VBInfo & SetInSlaveMode)  tempah ^= 0xA0;

#endif  /* CONFIG_FB_SIS_300 */

     } else {

#ifdef CONFIG_FB_SIS_315    /* ------- 315/330 series ------ */

	if(ModeNo > 0x13) {
	   tempcl -= ModeVGA;
	   if(tempcl >= 0) {
	      tempah = (0x08 >> tempcl);
	      if (tempah == 0) tempah = 1;
	      tempah |= 0x40;
	   }
	} else tempah = 0x40;

	if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) tempah ^= 0x50;

#endif  /* CONFIG_FB_SIS_315 */

     }

     if(SiS_Pr->SiS_VBInfo & DisableCRT2Display) tempah = 0;

     if(SiS_Pr->ChipType < SIS_315H) {
	SiS_SetReg(SiS_Pr->SiS_Part1Port,0x00,tempah);
     } else {
#ifdef CONFIG_FB_SIS_315
	if(SiS_Pr->SiS_IF_DEF_LVDS == 1) {
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x00,0xa0,tempah);
	} else if(SiS_Pr->SiS_VBType & VB_SISVB) {
	   if(IS_SIS740) {
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x00,tempah);
	   } else {
	      SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x00,0xa0,tempah);
	   }
	}
#endif
     }

     if(SiS_Pr->SiS_VBType & VB_SISVB) {

	tempah = 0x01;
	if(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) {
	   tempah |= 0x02;
	}
	if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC)) {
	   tempah ^= 0x05;
	   if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD)) {
	      tempah ^= 0x01;
	   }
	}

	if(SiS_Pr->ChipType < SIS_315H) {

	   if(SiS_Pr->SiS_VBInfo & DisableCRT2Display)  tempah = 0;

	   tempah = (tempah << 5) & 0xFF;
	   SiS_SetReg(SiS_Pr->SiS_Part1Port,0x01,tempah);
	   tempah = (tempah >> 5) & 0xFF;

	} else {

	   if(SiS_Pr->SiS_VBInfo & DisableCRT2Display)  tempah = 0x08;
	   else if(!(SiS_IsDualEdge(SiS_Pr)))           tempah |= 0x08;
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2E,0xF0,tempah);
	   tempah &= ~0x08;

	}

	if((SiS_Pr->SiS_ModeType == ModeVGA) && (!(SiS_Pr->SiS_VBInfo & SetInSlaveMode))) {
	   tempah |= 0x10;
	}

	tempah |= 0x80;
	if(SiS_Pr->SiS_VBType & VB_SIS301) {
	   if(SiS_Pr->PanelXRes < 1280 && SiS_Pr->PanelYRes < 960) tempah &= ~0x80;
	}

	if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) {
	   if(!(SiS_Pr->SiS_TVMode & (TVSetYPbPr750p | TVSetYPbPr525p))) {
	      if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) {
		 tempah |= 0x20;
	      }
	   }
	}

	SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x0D,0x40,tempah);

	tempah = 0x80;
	if(SiS_Pr->SiS_VBType & VB_SIS301) {
	   if(SiS_Pr->PanelXRes < 1280 && SiS_Pr->PanelYRes < 960) tempah = 0;
	}

	if(SiS_IsDualLink(SiS_Pr)) tempah |= 0x40;

	if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) {
	   if(SiS_Pr->SiS_TVMode & TVRPLLDIV2XO) {
	      tempah |= 0x40;
	   }
	}

	SiS_SetReg(SiS_Pr->SiS_Part4Port,0x0C,tempah);

     } else {  /* LVDS */

	if(SiS_Pr->ChipType >= SIS_315H) {

#ifdef CONFIG_FB_SIS_315
	   /* LVDS can only be slave in 8bpp modes */
	   tempah = 0x80;
	   if((modeflag & CRT2Mode) && (SiS_Pr->SiS_ModeType > ModeVGA)) {
	      if(SiS_Pr->SiS_VBInfo & DriverMode) {
	         tempah |= 0x02;
	      }
	   }

	   if(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode))  tempah |= 0x02;

	   if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)        tempah ^= 0x01;

	   if(SiS_Pr->SiS_VBInfo & DisableCRT2Display) tempah = 1;

	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2e,0xF0,tempah);
#endif

	} else {

#ifdef CONFIG_FB_SIS_300
	   tempah = 0;
	   if( (!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) && (SiS_Pr->SiS_ModeType > ModeVGA) ) {
	      tempah |= 0x02;
	   }
	   tempah <<= 5;

	   if(SiS_Pr->SiS_VBInfo & DisableCRT2Display) tempah = 0;

	   SiS_SetReg(SiS_Pr->SiS_Part1Port,0x01,tempah);
#endif

	}

     }

  }  /* LCDA */

  if(SiS_Pr->SiS_VBType & VB_SISVB) {

     if(SiS_Pr->ChipType >= SIS_315H) {

#ifdef CONFIG_FB_SIS_315
	/* unsigned char bridgerev = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x01); */

	/* The following is nearly unpreditable and varies from machine
	 * to machine. Especially the 301DH seems to be a real trouble
	 * maker. Some BIOSes simply set the registers (like in the
	 * NoLCD-if-statements here), some set them according to the
	 * LCDA stuff. It is very likely that some machines are not
	 * treated correctly in the following, very case-orientated
	 * code. What do I do then...?
	 */

	/* 740 variants match for 30xB, 301B-DH, 30xLV */

	if(!(IS_SIS740)) {
	   tempah = 0x04;						   /* For all bridges */
	   tempbl = 0xfb;
	   if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) {
	      tempah = 0x00;
	      if(SiS_IsDualEdge(SiS_Pr)) {
	         tempbl = 0xff;
	      }
	   }
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,tempbl,tempah);
	}

	/* The following two are responsible for eventually wrong colors
	 * in TV output. The DH (VB_NoLCD) conditions are unknown; the
	 * b0 was found in some 651 machine (Pim; P4_23=0xe5); the b1 version
	 * in a 650 box (Jake). What is the criteria?
	 * Addendum: Another combination 651+301B-DH(b1) (Rapo) needs same
	 * treatment like the 651+301B-DH(b0) case. Seems more to be the
	 * chipset than the bridge revision.
	 */

	if((IS_SIS740) || (SiS_Pr->ChipType >= SIS_661) || (SiS_Pr->SiS_ROMNew)) {
	   tempah = 0x30;
	   tempbl = 0xc0;
	   if((SiS_Pr->SiS_VBInfo & DisableCRT2Display) ||
	      ((SiS_Pr->SiS_ROMNew) && (!(ROMAddr[0x5b] & 0x04)))) {
	      tempah = 0x00;
	      tempbl = 0x00;
	   }
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2c,0xcf,tempah);
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x21,0x3f,tempbl);
	} else if(SiS_Pr->SiS_VBType & VB_SIS301) {
	   /* Fixes "TV-blue-bug" on 315+301 */
	   SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2c,0xcf);	/* For 301   */
	   SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x21,0x3f);
	} else if(SiS_Pr->SiS_VBType & VB_SISLVDS) {
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2c,0x30);	/* For 30xLV */
	   SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x21,0xc0);
	} else if(SiS_Pr->SiS_VBType & VB_NoLCD) {		/* For 301B-DH */
	   tempah = 0x30; tempah2 = 0xc0;
	   tempbl = 0xcf; tempbl2 = 0x3f;
	   if(SiS_Pr->SiS_TVBlue == 0) {
	         tempah = tempah2 = 0x00;
	   } else if(SiS_Pr->SiS_TVBlue == -1) {
	      /* Set on 651/M650, clear on 315/650 */
	      if(!(IS_SIS65x)) /* (bridgerev != 0xb0) */ {
	         tempah = tempah2 = 0x00;
	      }
	   }
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2c,tempbl,tempah);
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x21,tempbl2,tempah2);
	} else {
	   tempah = 0x30; tempah2 = 0xc0;		       /* For 30xB, 301C */
	   tempbl = 0xcf; tempbl2 = 0x3f;
	   if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) {
	      tempah = tempah2 = 0x00;
	      if(SiS_IsDualEdge(SiS_Pr)) {
		 tempbl = tempbl2 = 0xff;
	      }
	   }
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2c,tempbl,tempah);
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x21,tempbl2,tempah2);
	}

	if(IS_SIS740) {
	   tempah = 0x80;
	   if(SiS_Pr->SiS_VBInfo & DisableCRT2Display) tempah = 0x00;
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x23,0x7f,tempah);
	} else {
	   tempah = 0x00;
	   tempbl = 0x7f;
	   if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) {
	      tempbl = 0xff;
	      if(!(SiS_IsDualEdge(SiS_Pr))) tempah = 0x80;
	   }
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x23,tempbl,tempah);
	}

#endif /* CONFIG_FB_SIS_315 */

     } else if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) {

#ifdef CONFIG_FB_SIS_300
	SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x21,0x3f);

	if((SiS_Pr->SiS_VBInfo & DisableCRT2Display) ||
	   ((SiS_Pr->SiS_VBType & VB_NoLCD) &&
	    (SiS_Pr->SiS_VBInfo & SetCRT2ToLCD))) {
	   SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x23,0x7F);
	} else {
	   SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x23,0x80);
	}
#endif

     }

     if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) {
	SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x0D,0x80);
	if(SiS_Pr->SiS_VBType & VB_SIS30xCLV) {
	   SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x3A,0xC0);
        }
     }

  } else {  /* LVDS */

#ifdef CONFIG_FB_SIS_315
     if(SiS_Pr->ChipType >= SIS_315H) {

	if(SiS_Pr->SiS_IF_DEF_CH70xx != 0) {

	   tempah = 0x04;
	   tempbl = 0xfb;
	   if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) {
	      tempah = 0x00;
	      if(SiS_IsDualEdge(SiS_Pr)) tempbl = 0xff;
	   }
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,tempbl,tempah);

	   if(SiS_Pr->SiS_VBInfo & DisableCRT2Display) {
	      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x13,0xfb);
	   }

	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2c,0x30);

	} else if(SiS_Pr->ChipType == SIS_550) {

	   SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x13,0xfb);
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2c,0x30);

	}

     }
#endif

  }

}