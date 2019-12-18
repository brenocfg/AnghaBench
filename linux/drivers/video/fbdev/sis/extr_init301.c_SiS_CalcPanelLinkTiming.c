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
struct SiS_Private {int SiS_LCDInfo; unsigned short CHTotal; int CModeFlag; unsigned short SiS_VGAHT; unsigned short SiS_HT; int SiS_IF_DEF_LVDS; unsigned short PanelHT; unsigned short SiS_HDE; unsigned short PanelXRes; unsigned short SiS_VGAHDE; scalar_t__ SiS_VGAVDE; scalar_t__ PanelYRes; scalar_t__ PanelVT; scalar_t__ SiS_VGAVT; scalar_t__ SiS_VT; scalar_t__ SiS_VDE; TYPE_3__* SiS_NoScaleData; scalar_t__ Alternate1600x1200; TYPE_2__* SiS_RefIndex; TYPE_1__* SiS_SModeIDTable; scalar_t__ CVTotal; scalar_t__ UseCustomMode; } ;
struct TYPE_6__ {unsigned short VGAHT; unsigned short LCDHT; scalar_t__ LCDVT; scalar_t__ VGAVT; } ;
struct TYPE_5__ {unsigned short Ext_CRT2CRTC_NS; } ;
struct TYPE_4__ {unsigned short St_CRT2CRTC; } ;

/* Variables and functions */
 int DontExpandLCD ; 
 int HalfDCLK ; 
 int LCDPass11 ; 

__attribute__((used)) static void
SiS_CalcPanelLinkTiming(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		unsigned short ModeIdIndex, unsigned short RefreshRateTableIndex)
{
   unsigned short ResIndex;

   if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
      if(SiS_Pr->SiS_LCDInfo & LCDPass11) {
	 if(SiS_Pr->UseCustomMode) {
	    ResIndex = SiS_Pr->CHTotal;
	    if(SiS_Pr->CModeFlag & HalfDCLK) ResIndex <<= 1;
	    SiS_Pr->SiS_VGAHT = SiS_Pr->SiS_HT = ResIndex;
	    SiS_Pr->SiS_VGAVT = SiS_Pr->SiS_VT = SiS_Pr->CVTotal;
	 } else {
	    if(ModeNo < 0x13) {
	       ResIndex = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
	    } else {
	       ResIndex = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC_NS;
	    }
	    if(ResIndex == 0x09) {
	       if(SiS_Pr->Alternate1600x1200)        ResIndex = 0x20; /* 1600x1200 LCDA */
	       else if(SiS_Pr->SiS_IF_DEF_LVDS == 1) ResIndex = 0x21; /* 1600x1200 LVDS */
	    }
	    SiS_Pr->SiS_VGAHT = SiS_Pr->SiS_NoScaleData[ResIndex].VGAHT;
	    SiS_Pr->SiS_VGAVT = SiS_Pr->SiS_NoScaleData[ResIndex].VGAVT;
	    SiS_Pr->SiS_HT    = SiS_Pr->SiS_NoScaleData[ResIndex].LCDHT;
	    SiS_Pr->SiS_VT    = SiS_Pr->SiS_NoScaleData[ResIndex].LCDVT;
	 }
      } else {
	 SiS_Pr->SiS_VGAHT = SiS_Pr->SiS_HT = SiS_Pr->PanelHT;
	 SiS_Pr->SiS_VGAVT = SiS_Pr->SiS_VT = SiS_Pr->PanelVT;
      }
   } else {
      /* This handles custom modes and custom panels */
      SiS_Pr->SiS_HDE = SiS_Pr->PanelXRes;
      SiS_Pr->SiS_VDE = SiS_Pr->PanelYRes;
      SiS_Pr->SiS_HT  = SiS_Pr->PanelHT;
      SiS_Pr->SiS_VT  = SiS_Pr->PanelVT;
      SiS_Pr->SiS_VGAHT = SiS_Pr->PanelHT - (SiS_Pr->PanelXRes - SiS_Pr->SiS_VGAHDE);
      SiS_Pr->SiS_VGAVT = SiS_Pr->PanelVT - (SiS_Pr->PanelYRes - SiS_Pr->SiS_VGAVDE);
   }
}