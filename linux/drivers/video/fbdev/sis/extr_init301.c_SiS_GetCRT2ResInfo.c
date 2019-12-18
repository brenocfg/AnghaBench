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
struct SiS_Private {unsigned short CHDisplay; int CModeFlag; unsigned short SiS_VGAHDE; unsigned short SiS_HDE; unsigned short SiS_VGAVDE; unsigned short SiS_VDE; unsigned short CVDisplay; scalar_t__ ChipType; int SiS_IF_DEF_LVDS; int SiS_SetFlag; int SiS_VBType; int SiS_VBInfo; int SiS_LCDResInfo; int SiS_LCDInfo; scalar_t__ SiS_IF_DEF_FSTN; scalar_t__ SiS_IF_DEF_DSTN; int /*<<< orphan*/  SiS_P3c4; int /*<<< orphan*/  SiS_P3d4; TYPE_3__* SiS_EModeIDTable; TYPE_2__* SiS_ModeResInfo; TYPE_1__* SiS_StResInfo; scalar_t__ UseCustomMode; } ;
struct TYPE_6__ {unsigned short Ext_ModeFlag; } ;
struct TYPE_5__ {unsigned short HTotal; unsigned short VTotal; } ;
struct TYPE_4__ {unsigned short HTotal; unsigned short VTotal; } ;

/* Variables and functions */
 int DontExpandLCD ; 
 unsigned short DoubleScanMode ; 
 int HalfDCLK ; 
 int LCDVESATiming ; 
#define  Panel_1024x768 130 
#define  Panel_1280x1024 129 
#define  Panel_1600x1200 128 
 scalar_t__ SIS_315H ; 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToLCD ; 
 int SetDOSMode ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 unsigned short SiS_GetResInfo (struct SiS_Private*,unsigned short,unsigned short) ; 
 int VB_NoLCD ; 
 int VB_SISVB ; 

__attribute__((used)) static void
SiS_GetCRT2ResInfo(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex)
{
   unsigned short xres, yres, modeflag=0, resindex;

   if(SiS_Pr->UseCustomMode) {
      xres = SiS_Pr->CHDisplay;
      if(SiS_Pr->CModeFlag & HalfDCLK) xres <<= 1;
      SiS_Pr->SiS_VGAHDE = SiS_Pr->SiS_HDE = xres;
      /* DoubleScanMode-check done in CheckCalcCustomMode()! */
      SiS_Pr->SiS_VGAVDE = SiS_Pr->SiS_VDE = SiS_Pr->CVDisplay;
      return;
   }

   resindex = SiS_GetResInfo(SiS_Pr,ModeNo,ModeIdIndex);

   if(ModeNo <= 0x13) {
      xres = SiS_Pr->SiS_StResInfo[resindex].HTotal;
      yres = SiS_Pr->SiS_StResInfo[resindex].VTotal;
   } else {
      xres = SiS_Pr->SiS_ModeResInfo[resindex].HTotal;
      yres = SiS_Pr->SiS_ModeResInfo[resindex].VTotal;
      modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
   }

   if(!SiS_Pr->SiS_IF_DEF_DSTN && !SiS_Pr->SiS_IF_DEF_FSTN) {

      if((SiS_Pr->ChipType >= SIS_315H) && (SiS_Pr->SiS_IF_DEF_LVDS == 1)) {
	 if((ModeNo != 0x03) && (SiS_Pr->SiS_SetFlag & SetDOSMode)) {
	    if(yres == 350) yres = 400;
	 }
	 if(SiS_GetReg(SiS_Pr->SiS_P3d4,0x3a) & 0x01) {
	    if(ModeNo == 0x12) yres = 400;
	 }
      }

      if(modeflag & HalfDCLK)       xres <<= 1;
      if(modeflag & DoubleScanMode) yres <<= 1;

   }

   if((SiS_Pr->SiS_VBType & VB_SISVB) && (!(SiS_Pr->SiS_VBType & VB_NoLCD))) {

      if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {
	 switch(SiS_Pr->SiS_LCDResInfo) {
	   case Panel_1024x768:
	      if(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) {
		 if(!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) {
		    if(yres == 350) yres = 357;
		    if(yres == 400) yres = 420;
		    if(yres == 480) yres = 525;
		 }
	      }
	      break;
	   case Panel_1280x1024:
	      if(!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) {
		 /* BIOS bug - does this regardless of scaling */
		 if(yres == 400) yres = 405;
	      }
	      if(yres == 350) yres = 360;
	      if(SiS_Pr->SiS_SetFlag & LCDVESATiming) {
		 if(yres == 360) yres = 375;
	      }
	      break;
	   case Panel_1600x1200:
	      if(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) {
		 if(yres == 1024) yres = 1056;
	      }
	      break;
	 }
      }

   } else {

      if(SiS_Pr->SiS_VBType & VB_SISVB) {
	 if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToHiVision)) {
	    if(xres == 720) xres = 640;
	 }
      } else if(xres == 720) xres = 640;

      if(SiS_Pr->SiS_SetFlag & SetDOSMode) {
	 yres = 400;
	 if(SiS_Pr->ChipType >= SIS_315H) {
	    if(SiS_GetReg(SiS_Pr->SiS_P3c4,0x17) & 0x80) yres = 480;
	 } else {
	    if(SiS_GetReg(SiS_Pr->SiS_P3c4,0x13) & 0x80) yres = 480;
	 }
	 if(SiS_Pr->SiS_IF_DEF_DSTN || SiS_Pr->SiS_IF_DEF_FSTN) yres = 480;
      }

   }
   SiS_Pr->SiS_VGAHDE = SiS_Pr->SiS_HDE = xres;
   SiS_Pr->SiS_VGAVDE = SiS_Pr->SiS_VDE = yres;
}