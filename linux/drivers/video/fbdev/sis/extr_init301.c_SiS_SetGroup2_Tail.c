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
struct SiS_Private {int SiS_SetFlag; int SiS_VGAVDE; scalar_t__ SiS_ModeType; int SiS_VBType; int SiS_VBInfo; scalar_t__ SiS_LCDResInfo; int SiS_PanelXRes; int SiS_PanelYRes; int SiS_HDE; int SiS_VDE; int /*<<< orphan*/  SiS_Part2Port; } ;

/* Variables and functions */
 int LCDVESATiming ; 
 scalar_t__ ModeVGA ; 
 scalar_t__ Panel_1400x1050 ; 
 int SetCRT2ToLCD ; 
 int SetSimuScanMode ; 
 int /*<<< orphan*/  SiS_Part2Port ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 
 int VB_SIS30xB ; 
 int VB_SIS30xBLV ; 

__attribute__((used)) static void
SiS_SetGroup2_Tail(struct SiS_Private *SiS_Pr, unsigned short ModeNo)
{
  unsigned short temp;

  if(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) {
     if(SiS_Pr->SiS_VGAVDE == 525) {
	temp = 0xc3;
	if(SiS_Pr->SiS_ModeType <= ModeVGA) {
	   temp++;
	   if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) temp += 2;
	}
	SiS_SetReg(SiS_Pr->SiS_Part2Port,0x2f,temp);
	SiS_SetReg(SiS_Pr->SiS_Part2Port,0x30,0xb3);
     } else if(SiS_Pr->SiS_VGAVDE == 420) {
	temp = 0x4d;
	if(SiS_Pr->SiS_ModeType <= ModeVGA) {
	   temp++;
	   if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) temp++;
	}
	SiS_SetReg(SiS_Pr->SiS_Part2Port,0x2f,temp);
     }
  }

  if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {
     if(SiS_Pr->SiS_LCDResInfo == Panel_1400x1050) {
	if(SiS_Pr->SiS_VBType & VB_SIS30xB) {
	   SiS_SetRegOR(SiS_Pr->SiS_Part2Port,0x1a,0x03);
	   /* Not always for LV, see SetGrp2 */
	}
	temp = 1;
	if(ModeNo <= 0x13) temp = 3;
	SiS_SetReg(SiS_Pr->SiS_Part2Port,0x0b,temp);
     }
#if 0
     /* 651+301C, for 1280x768 - do I really need that? */
     if((SiS_Pr->SiS_PanelXRes == 1280) && (SiS_Pr->SiS_PanelYRes == 768)) {
        if(SiS_Pr->SiS_VBInfo & SetSimuScanMode) {
	   if(((SiS_Pr->SiS_HDE == 640) && (SiS_Pr->SiS_VDE == 480)) ||
	      ((SiS_Pr->SiS_HDE == 320) && (SiS_Pr->SiS_VDE == 240))) {
	      SiS_SetReg(SiS_Part2Port,0x01,0x2b);
	      SiS_SetReg(SiS_Part2Port,0x02,0x13);
	      SiS_SetReg(SiS_Part2Port,0x04,0xe5);
	      SiS_SetReg(SiS_Part2Port,0x05,0x08);
	      SiS_SetReg(SiS_Part2Port,0x06,0xe2);
	      SiS_SetReg(SiS_Part2Port,0x1c,0x21);
	      SiS_SetReg(SiS_Part2Port,0x1d,0x45);
	      SiS_SetReg(SiS_Part2Port,0x1f,0x0b);
	      SiS_SetReg(SiS_Part2Port,0x20,0x00);
	      SiS_SetReg(SiS_Part2Port,0x21,0xa9);
	      SiS_SetReg(SiS_Part2Port,0x23,0x0b);
	      SiS_SetReg(SiS_Part2Port,0x25,0x04);
	   }
	}
     }
#endif
  }
}