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
struct SiS_Private {int SiS_VBType; scalar_t__ ChipType; scalar_t__ SiS_CustomT; unsigned char* VirtualRomBase; int EMI_30; unsigned char EMI_31; unsigned short SiS_EMIOffset; unsigned char EMI_32; unsigned char EMI_33; int HaveEMI; int HaveEMILCD; int OverruleEMI; int SiS_IF_DEF_CH70xx; int /*<<< orphan*/  SiS_Part1Port; int /*<<< orphan*/  SiS_P3c4; int /*<<< orphan*/  SiS_Part2Port; int /*<<< orphan*/  SiS_P3d4; int /*<<< orphan*/  SiS_P3c6; int /*<<< orphan*/  SiS_Part4Port; scalar_t__ SiS_ROMNew; } ;

/* Variables and functions */
 scalar_t__ CUT_ASUSA2H_2 ; 
 scalar_t__ CUT_CLEVO1024 ; 
 scalar_t__ CUT_CLEVO1400 ; 
 scalar_t__ CUT_COMPAL1400_2 ; 
 scalar_t__ CUT_COMPAQ1280 ; 
 unsigned short GetLCDStructPtr661_2 (struct SiS_Private*) ; 
 scalar_t__ IS_SIS740 ; 
 scalar_t__ SIS_315H ; 
 scalar_t__ SIS_550 ; 
 scalar_t__ SIS_730 ; 
 scalar_t__ SIS_740 ; 
 unsigned short SetCRT2ToRAMDAC ; 
 scalar_t__ SiS_BridgeInSlavemode (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_CR36BIOSWord23b (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_CR36BIOSWord23d (struct SiS_Private*) ; 
 scalar_t__ SiS_CRT2IsLCD (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_Chrontel701xBLOff (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_Chrontel701xBLOn (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_Chrontel701xOn (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_ChrontelDoSomething1 (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_ChrontelInitTVVSync (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_DisplayOff (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_DisplayOn (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_GenericDelay (struct SiS_Private*,int) ; 
 unsigned short SiS_GetCH701x (struct SiS_Private*,int) ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int SiS_HandlePWD (struct SiS_Private*) ; 
 scalar_t__ SiS_IsDualEdge (struct SiS_Private*) ; 
 scalar_t__ SiS_IsLCDOrLCDA (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_IsNotM650orLater (struct SiS_Private*) ; 
 scalar_t__ SiS_IsTVOrYPbPrOrScart (struct SiS_Private*) ; 
 scalar_t__ SiS_IsVAMode (struct SiS_Private*) ; 
 scalar_t__ SiS_IsVAorLCD (struct SiS_Private*) ; 
 scalar_t__ SiS_LCDAEnabled (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_PanelDelay (struct SiS_Private*,int) ; 
 int /*<<< orphan*/  SiS_PanelDelayLoop (struct SiS_Private*,int,int) ; 
 int /*<<< orphan*/  SiS_SetCH700x (struct SiS_Private*,int,int) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegByte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegSR11ANDOR (struct SiS_Private*,int,int) ; 
 scalar_t__ SiS_TVEnabled (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_UnLockCRT2 (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_VBLongWait (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_WaitVBRetrace (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_WeHaveBacklightCtrl (struct SiS_Private*) ; 
 int VB_NoLCD ; 
 int VB_SIS30xBLV ; 
 int VB_SISEMI ; 
 int VB_SISLVDS ; 
 int VB_SISPOWER ; 
 int VB_SISVB ; 

__attribute__((used)) static
void
SiS_EnableBridge(struct SiS_Private *SiS_Pr)
{
  unsigned short temp=0, tempah;
#ifdef CONFIG_FB_SIS_315
  unsigned short temp1, pushax=0;
  bool delaylong = false;
#endif

  if(SiS_Pr->SiS_VBType & VB_SISVB) {

    if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) {		/* ====== For 301B et al  ====== */

      if(SiS_Pr->ChipType < SIS_315H) {

#ifdef CONFIG_FB_SIS_300     /* 300 series */

	 if(SiS_CRT2IsLCD(SiS_Pr)) {
	    if(SiS_Pr->SiS_VBType & VB_SISLVDS) {
	       SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x26,0x02);
	    } else if(SiS_Pr->SiS_VBType & VB_NoLCD) {
	       SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x00);
	    }
	    if(SiS_Pr->SiS_VBType & (VB_SISLVDS | VB_NoLCD)) {
	       if(!(SiS_CR36BIOSWord23d(SiS_Pr))) {
		  SiS_PanelDelay(SiS_Pr, 0);
	       }
	    }
	 }

	 if((SiS_Pr->SiS_VBType & VB_NoLCD) &&
	    (SiS_CRT2IsLCD(SiS_Pr))) {

	    SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);   		/* Enable CRT2 */
	    SiS_DisplayOn(SiS_Pr);
	    SiS_UnLockCRT2(SiS_Pr);
	    SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x02,0xBF);
	    if(SiS_BridgeInSlavemode(SiS_Pr)) {
	       SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x01,0x1F);
	    } else {
	       SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x01,0x1F,0x40);
	    }
	    if(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x13) & 0x40)) {
	       if(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x16) & 0x10)) {
		  if(!(SiS_CR36BIOSWord23b(SiS_Pr))) {
		     SiS_PanelDelay(SiS_Pr, 1);
		  }
		  SiS_WaitVBRetrace(SiS_Pr);
		  SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x00);
	       }
	    }

	 } else {

	    temp = SiS_GetReg(SiS_Pr->SiS_P3c4,0x32) & 0xDF;             /* lock mode */
	    if(SiS_BridgeInSlavemode(SiS_Pr)) {
	       tempah = SiS_GetReg(SiS_Pr->SiS_P3d4,0x30);
	       if(!(tempah & SetCRT2ToRAMDAC)) temp |= 0x20;
	    }
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x32,temp);
	    SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);
	    SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x00,0x1F,0x20);        /* enable VB processor */
	    SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x1F,0xC0);
	    SiS_DisplayOn(SiS_Pr);
	    if(SiS_Pr->SiS_VBType & VB_SISLVDS) {
	       if(SiS_CRT2IsLCD(SiS_Pr)) {
		  if(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x16) & 0x10)) {
		     if(!(SiS_CR36BIOSWord23b(SiS_Pr))) {
		        SiS_PanelDelay(SiS_Pr, 1);
		     }
		     SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x26,0x01);
		  }
	       }
	    }

	 }


#endif /* CONFIG_FB_SIS_300 */

      } else {

#ifdef CONFIG_FB_SIS_315    /* 315 series */

#ifdef SET_EMI
	 unsigned char   r30=0, r31=0, r32=0, r33=0, cr36=0;
	 int didpwd = 0;
	 /* unsigned short  emidelay=0; */
#endif

	 if(SiS_Pr->SiS_VBType & VB_SISLVDS) {
	    SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x1f,0xef);
#ifdef SET_EMI
	    if(SiS_Pr->SiS_VBType & VB_SISEMI) {
	       SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x30,0x0c);
	    }
#endif
	 }

	 if(!(SiS_IsNotM650orLater(SiS_Pr))) {
	    /*if(SiS_Pr->ChipType < SIS_340) { */
	       tempah = 0x10;
	       if(SiS_LCDAEnabled(SiS_Pr)) {
		  if(SiS_TVEnabled(SiS_Pr)) tempah = 0x18;
		  else			    tempah = 0x08;
	       }
	       SiS_SetReg(SiS_Pr->SiS_Part1Port,0x4c,tempah);
	    /*}*/
	 }

	 if(SiS_Pr->SiS_VBType & VB_SISLVDS) {

	    SiS_SetRegByte(SiS_Pr->SiS_P3c6,0x00);
	    SiS_DisplayOff(SiS_Pr);
	    pushax = SiS_GetReg(SiS_Pr->SiS_P3c4,0x06);
	    if(IS_SIS740) {
	       SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x06,0xE3);
	    }

	    didpwd = SiS_HandlePWD(SiS_Pr);

	    if(SiS_IsVAorLCD(SiS_Pr)) {
	       if(!didpwd) {
		  if(!(SiS_GetReg(SiS_Pr->SiS_Part4Port,0x26) & 0x02)) {
		     SiS_PanelDelayLoop(SiS_Pr, 3, 2);
		     SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x26,0x02);
		     SiS_PanelDelayLoop(SiS_Pr, 3, 2);
		     if(SiS_Pr->SiS_VBType & VB_SISEMI) {
		        SiS_GenericDelay(SiS_Pr, 17664);
		     }
		  }
	       } else {
		  SiS_PanelDelayLoop(SiS_Pr, 3, 2);
		  if(SiS_Pr->SiS_VBType & VB_SISEMI) {
		     SiS_GenericDelay(SiS_Pr, 17664);
		  }
	       }
	    }

	    if(!(SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) & 0x40)) {
	       SiS_PanelDelayLoop(SiS_Pr, 3, 10);
	       delaylong = true;
	    }

	 }

	 if(!(SiS_IsVAMode(SiS_Pr))) {

	    temp = SiS_GetReg(SiS_Pr->SiS_P3c4,0x32) & 0xDF;
	    if(SiS_BridgeInSlavemode(SiS_Pr)) {
	       tempah = SiS_GetReg(SiS_Pr->SiS_P3d4,0x30);
	       if(!(tempah & SetCRT2ToRAMDAC)) {
		  if(!(SiS_LCDAEnabled(SiS_Pr))) temp |= 0x20;
	       }
	    }
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x32,temp);

	    SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);                   /* enable CRT2 */

	    SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2e,0x7f);
	    SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2e,0x80);

	    if(SiS_Pr->SiS_VBType & VB_SISLVDS) {
	       SiS_PanelDelay(SiS_Pr, 2);
	    }

	 } else {

	    SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1e,0x20);

	 }

	 SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x00,0x1f,0x20);
	 SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2e,0x80);

	 if(SiS_Pr->SiS_VBType & VB_SISPOWER) {
	    if( (SiS_LCDAEnabled(SiS_Pr)) ||
	        (SiS_CRT2IsLCD(SiS_Pr)) ) {
	       /* Enable "LVDS PLL power on" (even on 301C) */
	       SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x2a,0x7f);
	       /* Enable "LVDS Driver Power on" (even on 301C) */
	       SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x30,0x7f);
	    }
	 }

	 tempah = 0xc0;
	 if(SiS_IsDualEdge(SiS_Pr)) {
	    tempah = 0x80;
	    if(!(SiS_IsVAMode(SiS_Pr))) tempah = 0x40;
	 }
	 SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x1F,tempah);

	 if(SiS_Pr->SiS_VBType & VB_SISLVDS) {

	    SiS_PanelDelay(SiS_Pr, 2);

	    SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x1f,0x10);
	    SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2e,0x80);

	    if(SiS_Pr->SiS_CustomT != CUT_CLEVO1400) {
#ifdef SET_EMI
	       if(SiS_Pr->SiS_VBType & VB_SISEMI) {
		  SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x30,0x0c);
		  SiS_GenericDelay(SiS_Pr, 2048);
	       }
#endif
	       SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x27,0x0c);

	       if(SiS_Pr->SiS_VBType & VB_SISEMI) {
#ifdef SET_EMI
		  cr36 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x36);

		  if(SiS_Pr->SiS_ROMNew) {
		     unsigned char  *ROMAddr = SiS_Pr->VirtualRomBase;
		     unsigned short romptr = GetLCDStructPtr661_2(SiS_Pr);
		     if(romptr) {
			SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x30,0x20); /* Reset */
			SiS_Pr->EMI_30 = 0;
			SiS_Pr->EMI_31 = ROMAddr[romptr + SiS_Pr->SiS_EMIOffset + 0];
			SiS_Pr->EMI_32 = ROMAddr[romptr + SiS_Pr->SiS_EMIOffset + 1];
			SiS_Pr->EMI_33 = ROMAddr[romptr + SiS_Pr->SiS_EMIOffset + 2];
			if(ROMAddr[romptr + 1] & 0x10) SiS_Pr->EMI_30 = 0x40;
			/* emidelay = SISGETROMW((romptr + 0x22)); */
			SiS_Pr->HaveEMI = SiS_Pr->HaveEMILCD = SiS_Pr->OverruleEMI = true;
		     }
		  }

		  /*                                              (P4_30|0x40)  */
		  /* Compal 1400x1050: 0x05, 0x60, 0x00                YES  (1.10.7w;  CR36=69)      */
		  /* Compal 1400x1050: 0x0d, 0x70, 0x40                YES  (1.10.7x;  CR36=69)      */
		  /* Acer   1280x1024: 0x12, 0xd0, 0x6b                NO   (1.10.9k;  CR36=73)      */
		  /* Compaq 1280x1024: 0x0d, 0x70, 0x6b                YES  (1.12.04b; CR36=03)      */
		  /* Clevo   1024x768: 0x05, 0x60, 0x33                NO   (1.10.8e;  CR36=12, DL!) */
		  /* Clevo   1024x768: 0x0d, 0x70, 0x40 (if type == 3) YES  (1.10.8y;  CR36=?2)      */
		  /* Clevo   1024x768: 0x05, 0x60, 0x33 (if type != 3) YES  (1.10.8y;  CR36=?2)      */
		  /* Asus    1024x768: ?                                ?   (1.10.8o;  CR36=?2)      */
		  /* Asus    1024x768: 0x08, 0x10, 0x3c (problematic)  YES  (1.10.8q;  CR36=22)      */

		  if(SiS_Pr->HaveEMI) {
		     r30 = SiS_Pr->EMI_30; r31 = SiS_Pr->EMI_31;
		     r32 = SiS_Pr->EMI_32; r33 = SiS_Pr->EMI_33;
		  } else {
		     r30 = 0;
		  }

		  /* EMI_30 is read at driver start; however, the BIOS sets this
		   * (if it is used) only if the LCD is in use. In case we caught
		   * the machine while on TV output, this bit is not set and we
		   * don't know if it should be set - hence our detection is wrong.
		   * Work-around this here:
		   */

		  if((!SiS_Pr->HaveEMI) || (!SiS_Pr->HaveEMILCD)) {
		     switch((cr36 & 0x0f)) {
		     case 2:
			r30 |= 0x40;
			if(SiS_Pr->SiS_CustomT == CUT_CLEVO1024) r30 &= ~0x40;
			if(!SiS_Pr->HaveEMI) {
			   r31 = 0x05; r32 = 0x60; r33 = 0x33;
			   if((cr36 & 0xf0) == 0x30) {
			      r31 = 0x0d; r32 = 0x70; r33 = 0x40;
			   }
			}
			break;
		     case 3:  /* 1280x1024 */
			if(SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) r30 |= 0x40;
			if(!SiS_Pr->HaveEMI) {
			   r31 = 0x12; r32 = 0xd0; r33 = 0x6b;
			   if(SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) {
			      r31 = 0x0d; r32 = 0x70; r33 = 0x6b;
			   }
			}
			break;
		     case 9:  /* 1400x1050 */
			r30 |= 0x40;
			if(!SiS_Pr->HaveEMI) {
			   r31 = 0x05; r32 = 0x60; r33 = 0x00;
			   if(SiS_Pr->SiS_CustomT == CUT_COMPAL1400_2) {
			      r31 = 0x0d; r32 = 0x70; r33 = 0x40;  /* BIOS values */
			   }
			}
			break;
		     case 11: /* 1600x1200 - unknown */
			r30 |= 0x40;
			if(!SiS_Pr->HaveEMI) {
			   r31 = 0x05; r32 = 0x60; r33 = 0x00;
			}
		     }
                  }

		  /* BIOS values don't work so well sometimes */
		  if(!SiS_Pr->OverruleEMI) {
#ifdef COMPAL_HACK
		     if(SiS_Pr->SiS_CustomT == CUT_COMPAL1400_2) {
			if((cr36 & 0x0f) == 0x09) {
			   r30 = 0x60; r31 = 0x05; r32 = 0x60; r33 = 0x00;
			}
 		     }
#endif
#ifdef COMPAQ_HACK
		     if(SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) {
			if((cr36 & 0x0f) == 0x03) {
			   r30 = 0x20; r31 = 0x12; r32 = 0xd0; r33 = 0x6b;
			}
		     }
#endif
#ifdef ASUS_HACK
		     if(SiS_Pr->SiS_CustomT == CUT_ASUSA2H_2) {
			if((cr36 & 0x0f) == 0x02) {
			   /* r30 = 0x60; r31 = 0x05; r32 = 0x60; r33 = 0x33;  */   /* rev 2 */
			   /* r30 = 0x20; r31 = 0x05; r32 = 0x60; r33 = 0x33;  */   /* rev 3 */
			   /* r30 = 0x60; r31 = 0x0d; r32 = 0x70; r33 = 0x40;  */   /* rev 4 */
			   /* r30 = 0x20; r31 = 0x0d; r32 = 0x70; r33 = 0x40;  */   /* rev 5 */
			}
		     }
#endif
		  }

		  if(!(SiS_Pr->OverruleEMI && (!r30) && (!r31) && (!r32) && (!r33))) {
		     SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x30,0x20); /* Reset */
		     SiS_GenericDelay(SiS_Pr, 2048);
		  }
		  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x31,r31);
		  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x32,r32);
		  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x33,r33);
#endif	/* SET_EMI */

		  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x34,0x10);

#ifdef SET_EMI
		  if( (SiS_LCDAEnabled(SiS_Pr)) ||
		      (SiS_CRT2IsLCD(SiS_Pr)) ) {
		     if(r30 & 0x40) {
			/*SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x2a,0x80);*/
			SiS_PanelDelayLoop(SiS_Pr, 3, 5);
			if(delaylong) {
			   SiS_PanelDelayLoop(SiS_Pr, 3, 5);
			   delaylong = false;
			}
			SiS_WaitVBRetrace(SiS_Pr);
			SiS_WaitVBRetrace(SiS_Pr);
			if(SiS_Pr->SiS_CustomT == CUT_ASUSA2H_2) {
			   SiS_GenericDelay(SiS_Pr, 1280);
			}
			SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x30,0x40);   /* Enable */
			/*SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x2a,0x7f);*/
		     }
		  }
#endif
	       }
	    }

	    if(!(SiS_WeHaveBacklightCtrl(SiS_Pr))) {
	       if(SiS_IsVAorLCD(SiS_Pr)) {
		  SiS_PanelDelayLoop(SiS_Pr, 3, 10);
		  if(delaylong) {
		     SiS_PanelDelayLoop(SiS_Pr, 3, 10);
		  }
		  SiS_WaitVBRetrace(SiS_Pr);
		  if(SiS_Pr->SiS_VBType & VB_SISEMI) {
		     SiS_GenericDelay(SiS_Pr, 2048);
		     SiS_WaitVBRetrace(SiS_Pr);
		  }
		  if(!didpwd) {
		     SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x26,0x01);
		  } else {
		     SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x26,0x03);
		  }
	       }
	    }

	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x06,pushax);
	    SiS_DisplayOn(SiS_Pr);
	    SiS_SetRegByte(SiS_Pr->SiS_P3c6,0xff);

	 }

	 if(!(SiS_WeHaveBacklightCtrl(SiS_Pr))) {
	    SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x00,0x7f);
	 }

#endif /* CONFIG_FB_SIS_315 */

      }

    } else {	/* ============  For 301 ================ */

       if(SiS_Pr->ChipType < SIS_315H) {
	  if(SiS_CRT2IsLCD(SiS_Pr)) {
	     SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x00);
	     SiS_PanelDelay(SiS_Pr, 0);
	  }
       }

       temp = SiS_GetReg(SiS_Pr->SiS_P3c4,0x32) & 0xDF;          /* lock mode */
       if(SiS_BridgeInSlavemode(SiS_Pr)) {
	  tempah = SiS_GetReg(SiS_Pr->SiS_P3d4,0x30);
	  if(!(tempah & SetCRT2ToRAMDAC)) temp |= 0x20;
       }
       SiS_SetReg(SiS_Pr->SiS_P3c4,0x32,temp);

       SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);                  /* enable CRT2 */

       if(SiS_Pr->ChipType >= SIS_315H) {
	  temp = SiS_GetReg(SiS_Pr->SiS_Part1Port,0x2E);
	  if(!(temp & 0x80)) {
	     SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2E,0x80);         /* BVBDOENABLE=1 */
	  }
       }

       SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x00,0x1F,0x20);     /* enable VB processor */

       SiS_VBLongWait(SiS_Pr);
       SiS_DisplayOn(SiS_Pr);
       if(SiS_Pr->ChipType >= SIS_315H) {
	  SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x00,0x7f);
       }
       SiS_VBLongWait(SiS_Pr);

       if(SiS_Pr->ChipType < SIS_315H) {
	  if(SiS_CRT2IsLCD(SiS_Pr)) {
	     SiS_PanelDelay(SiS_Pr, 1);
	     SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x00);
	  }
       }

    }

  } else {   /* =================== For LVDS ================== */

    if(SiS_Pr->ChipType < SIS_315H) {

#ifdef CONFIG_FB_SIS_300    /* 300 series */

       if(SiS_CRT2IsLCD(SiS_Pr)) {
	  if(SiS_Pr->ChipType == SIS_730) {
	     SiS_PanelDelay(SiS_Pr, 1);
	     SiS_PanelDelay(SiS_Pr, 1);
	     SiS_PanelDelay(SiS_Pr, 1);
	  }
	  SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x00);
	  if(!(SiS_CR36BIOSWord23d(SiS_Pr))) {
	     SiS_PanelDelay(SiS_Pr, 0);
	  }
       }

       SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);
       SiS_DisplayOn(SiS_Pr);
       SiS_UnLockCRT2(SiS_Pr);
       SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x02,0xBF);
       if(SiS_BridgeInSlavemode(SiS_Pr)) {
	  SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x01,0x1F);
       } else {
	  SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x01,0x1F,0x40);
       }

       if(SiS_Pr->SiS_IF_DEF_CH70xx == 1) {
	  if(!(SiS_CRT2IsLCD(SiS_Pr))) {
	     SiS_WaitVBRetrace(SiS_Pr);
	     SiS_SetCH700x(SiS_Pr,0x0E,0x0B);
	  }
       }

       if(SiS_CRT2IsLCD(SiS_Pr)) {
	  if(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x13) & 0x40)) {
	     if(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x16) & 0x10)) {
		if(!(SiS_CR36BIOSWord23b(SiS_Pr))) {
		   SiS_PanelDelay(SiS_Pr, 1);
		   SiS_PanelDelay(SiS_Pr, 1);
		}
		SiS_WaitVBRetrace(SiS_Pr);
		SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x00);
	     }
	  }
       }

#endif  /* CONFIG_FB_SIS_300 */

    } else {

#ifdef CONFIG_FB_SIS_315    /* 315 series */

       if(!(SiS_IsNotM650orLater(SiS_Pr))) {
	  /*if(SiS_Pr->ChipType < SIS_340) {*/  /* XGI needs this */
	     SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x4c,0x18);
	  /*}*/
       }

       if(SiS_Pr->SiS_IF_DEF_CH70xx == 0) {
	  if(SiS_CRT2IsLCD(SiS_Pr)) {
	     SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x00);
	     SiS_PanelDelay(SiS_Pr, 0);
	  }
       }

       SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);
       SiS_UnLockCRT2(SiS_Pr);

       SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2e,0xf7);

       if(SiS_Pr->SiS_IF_DEF_CH70xx == 2) {
	  temp = SiS_GetCH701x(SiS_Pr,0x66);
	  temp &= 0x20;
	  SiS_Chrontel701xBLOff(SiS_Pr);
       }

       if(SiS_Pr->ChipType != SIS_550) {
	  SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2e,0x7f);
       }

       if(SiS_Pr->ChipType == SIS_740) {
	  if(SiS_Pr->SiS_IF_DEF_CH70xx == 2) {
	     if(SiS_IsLCDOrLCDA(SiS_Pr)) {
		SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1E,0x20);
	     }
	  }
       }

       temp1 = SiS_GetReg(SiS_Pr->SiS_Part1Port,0x2E);
       if(!(temp1 & 0x80)) {
	  SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2E,0x80);
       }

       if(SiS_Pr->SiS_IF_DEF_CH70xx == 2) {
	  if(temp) {
	     SiS_Chrontel701xBLOn(SiS_Pr);
	  }
       }

       if(SiS_Pr->SiS_IF_DEF_CH70xx == 0) {
	  if(SiS_CRT2IsLCD(SiS_Pr)) {
	     SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1E,0x20);
	     if(SiS_Pr->ChipType == SIS_550) {
		SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1E,0x40);
		SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1E,0x10);
	     }
	  }
       } else if(SiS_IsVAMode(SiS_Pr)) {
	  if(SiS_Pr->ChipType != SIS_740) {
	     SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1E,0x20);
	  }
       }

       if(!(SiS_WeHaveBacklightCtrl(SiS_Pr))) {
	  SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x00,0x7f);
       }

       if(SiS_Pr->SiS_IF_DEF_CH70xx == 2) {
	  if(SiS_IsTVOrYPbPrOrScart(SiS_Pr)) {
	     SiS_Chrontel701xOn(SiS_Pr);
	  }
	  if( (SiS_IsVAMode(SiS_Pr)) ||
	      (SiS_IsLCDOrLCDA(SiS_Pr)) ) {
	     SiS_ChrontelDoSomething1(SiS_Pr);
	  }
       }

       if(SiS_Pr->SiS_IF_DEF_CH70xx == 2) {
	  if(!(SiS_WeHaveBacklightCtrl(SiS_Pr))) {
	     if( (SiS_IsVAMode(SiS_Pr)) ||
		 (SiS_IsLCDOrLCDA(SiS_Pr)) ) {
		SiS_Chrontel701xBLOn(SiS_Pr);
		SiS_ChrontelInitTVVSync(SiS_Pr);
	     }
	  }
       } else if(SiS_Pr->SiS_IF_DEF_CH70xx == 0) {
	  if(!(SiS_WeHaveBacklightCtrl(SiS_Pr))) {
	     if(SiS_CRT2IsLCD(SiS_Pr)) {
		SiS_PanelDelay(SiS_Pr, 1);
		SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x00);
	     }
	  }
       }

#endif  /* CONFIG_FB_SIS_315 */

    } /* 310 series */

  }  /* LVDS */

}