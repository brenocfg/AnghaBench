#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int /*<<< orphan*/  SiS_UseOEM; } ;
struct sis_video_info {int currentvbflags; int rate_idx; scalar_t__ sisvga_engine; scalar_t__ chip; int curFSTN; int curDSTN; int vbflags; int vbflags2; int sisfb_dstn; int sisfb_fstn; size_t sisfb_mode_idx; int /*<<< orphan*/  sisfb_useoem; TYPE_2__ SiS_Pr; int /*<<< orphan*/  sisfb_nocrt2rate; } ;
struct TYPE_4__ {int rate_idx; } ;

/* Variables and functions */
#define  CRT2_LCD 130 
#define  CRT2_TV 129 
#define  CRT2_VGA 128 
 int /*<<< orphan*/  SISCR ; 
 int /*<<< orphan*/  SISSR ; 
 scalar_t__ SIS_300 ; 
 scalar_t__ SIS_300_VGA ; 
 scalar_t__ SIS_315_VGA ; 
 scalar_t__ SIS_661 ; 
 int SIS_DRIVER_MODE ; 
 int SIS_SIMULTANEOUS_VIEW_ENABLE ; 
 int SIS_VB_OUTPUT_COMPOSITE ; 
 int SIS_VB_OUTPUT_CRT2 ; 
 int SIS_VB_OUTPUT_DISABLE ; 
 int SIS_VB_OUTPUT_LCD ; 
 int SIS_VB_OUTPUT_SCART ; 
 int SIS_VB_OUTPUT_SVIDEO ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetEnableDstn (TYPE_2__*,int) ; 
 int /*<<< orphan*/  SiS_SetEnableFstn (TYPE_2__*,int) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,int) ; 
 int TV_AVIDEO ; 
 int TV_HIVISION ; 
 int TV_NTSC ; 
 int TV_NTSCJ ; 
 int TV_PAL ; 
 int TV_PALM ; 
 int TV_PALN ; 
 int TV_SCART ; 
 int TV_SVIDEO ; 
 int TV_YPBPR ; 
 int TV_YPBPR1080I ; 
 int TV_YPBPR525P ; 
 int TV_YPBPR750P ; 
 int TV_YPBPRALL ; 
 int VB2_SISHIVISIONBRIDGE ; 
 int VB2_SISYPBPRBRIDGE ; 
 int VB_DISPTYPE_DISP2 ; 
 int VB_VIDEOBRIDGE ; 
 TYPE_1__* sisbios_mode ; 
 int /*<<< orphan*/  sisfb_check_engine_and_sync (struct sis_video_info*) ; 

__attribute__((used)) static void
sisfb_pre_setmode(struct sis_video_info *ivideo)
{
	u8 cr30 = 0, cr31 = 0, cr33 = 0, cr35 = 0, cr38 = 0;
	int tvregnum = 0;

	ivideo->currentvbflags &= (VB_VIDEOBRIDGE | VB_DISPTYPE_DISP2);

	SiS_SetReg(SISSR, 0x05, 0x86);

	cr31 = SiS_GetReg(SISCR, 0x31);
	cr31 &= ~0x60;
	cr31 |= 0x04;

	cr33 = ivideo->rate_idx & 0x0F;

#ifdef CONFIG_FB_SIS_315
	if(ivideo->sisvga_engine == SIS_315_VGA) {
	   if(ivideo->chip >= SIS_661) {
	      cr38 = SiS_GetReg(SISCR, 0x38);
	      cr38 &= ~0x07;  /* Clear LCDA/DualEdge and YPbPr bits */
	   } else {
	      tvregnum = 0x38;
	      cr38 = SiS_GetReg(SISCR, tvregnum);
	      cr38 &= ~0x3b;  /* Clear LCDA/DualEdge and YPbPr bits */
	   }
	}
#endif
#ifdef CONFIG_FB_SIS_300
	if(ivideo->sisvga_engine == SIS_300_VGA) {
	   tvregnum = 0x35;
	   cr38 = SiS_GetReg(SISCR, tvregnum);
	}
#endif

	SiS_SetEnableDstn(&ivideo->SiS_Pr, false);
	SiS_SetEnableFstn(&ivideo->SiS_Pr, false);
	ivideo->curFSTN = ivideo->curDSTN = 0;

	switch(ivideo->currentvbflags & VB_DISPTYPE_DISP2) {

	   case CRT2_TV:
	      cr38 &= ~0xc0;   /* Clear PAL-M / PAL-N bits */
	      if((ivideo->vbflags & TV_YPBPR) && (ivideo->vbflags2 & VB2_SISYPBPRBRIDGE)) {
#ifdef CONFIG_FB_SIS_315
		 if(ivideo->chip >= SIS_661) {
		    cr38 |= 0x04;
		    if(ivideo->vbflags & TV_YPBPR525P)       cr35 |= 0x20;
		    else if(ivideo->vbflags & TV_YPBPR750P)  cr35 |= 0x40;
		    else if(ivideo->vbflags & TV_YPBPR1080I) cr35 |= 0x60;
		    cr30 |= SIS_SIMULTANEOUS_VIEW_ENABLE;
		    cr35 &= ~0x01;
		    ivideo->currentvbflags |= (TV_YPBPR | (ivideo->vbflags & TV_YPBPRALL));
		 } else if(ivideo->sisvga_engine == SIS_315_VGA) {
		    cr30 |= (0x80 | SIS_SIMULTANEOUS_VIEW_ENABLE);
		    cr38 |= 0x08;
		    if(ivideo->vbflags & TV_YPBPR525P)       cr38 |= 0x10;
		    else if(ivideo->vbflags & TV_YPBPR750P)  cr38 |= 0x20;
		    else if(ivideo->vbflags & TV_YPBPR1080I) cr38 |= 0x30;
		    cr31 &= ~0x01;
		    ivideo->currentvbflags |= (TV_YPBPR | (ivideo->vbflags & TV_YPBPRALL));
		 }
#endif
	      } else if((ivideo->vbflags & TV_HIVISION) &&
				(ivideo->vbflags2 & VB2_SISHIVISIONBRIDGE)) {
		 if(ivideo->chip >= SIS_661) {
		    cr38 |= 0x04;
		    cr35 |= 0x60;
		 } else {
		    cr30 |= 0x80;
		 }
		 cr30 |= SIS_SIMULTANEOUS_VIEW_ENABLE;
		 cr31 |= 0x01;
		 cr35 |= 0x01;
		 ivideo->currentvbflags |= TV_HIVISION;
	      } else if(ivideo->vbflags & TV_SCART) {
		 cr30 = (SIS_VB_OUTPUT_SCART | SIS_SIMULTANEOUS_VIEW_ENABLE);
		 cr31 |= 0x01;
		 cr35 |= 0x01;
		 ivideo->currentvbflags |= TV_SCART;
	      } else {
		 if(ivideo->vbflags & TV_SVIDEO) {
		    cr30 = (SIS_VB_OUTPUT_SVIDEO | SIS_SIMULTANEOUS_VIEW_ENABLE);
		    ivideo->currentvbflags |= TV_SVIDEO;
		 }
		 if(ivideo->vbflags & TV_AVIDEO) {
		    cr30 = (SIS_VB_OUTPUT_COMPOSITE | SIS_SIMULTANEOUS_VIEW_ENABLE);
		    ivideo->currentvbflags |= TV_AVIDEO;
		 }
	      }
	      cr31 |= SIS_DRIVER_MODE;

	      if(ivideo->vbflags & (TV_AVIDEO | TV_SVIDEO)) {
		 if(ivideo->vbflags & TV_PAL) {
		    cr31 |= 0x01; cr35 |= 0x01;
		    ivideo->currentvbflags |= TV_PAL;
		    if(ivideo->vbflags & TV_PALM) {
		       cr38 |= 0x40; cr35 |= 0x04;
		       ivideo->currentvbflags |= TV_PALM;
		    } else if(ivideo->vbflags & TV_PALN) {
		       cr38 |= 0x80; cr35 |= 0x08;
		       ivideo->currentvbflags |= TV_PALN;
		    }
		 } else {
		    cr31 &= ~0x01; cr35 &= ~0x01;
		    ivideo->currentvbflags |= TV_NTSC;
		    if(ivideo->vbflags & TV_NTSCJ) {
		       cr38 |= 0x40; cr35 |= 0x02;
		       ivideo->currentvbflags |= TV_NTSCJ;
		    }
		 }
	      }
	      break;

	   case CRT2_LCD:
	      cr30  = (SIS_VB_OUTPUT_LCD | SIS_SIMULTANEOUS_VIEW_ENABLE);
	      cr31 |= SIS_DRIVER_MODE;
	      SiS_SetEnableDstn(&ivideo->SiS_Pr, ivideo->sisfb_dstn);
	      SiS_SetEnableFstn(&ivideo->SiS_Pr, ivideo->sisfb_fstn);
	      ivideo->curFSTN = ivideo->sisfb_fstn;
	      ivideo->curDSTN = ivideo->sisfb_dstn;
	      break;

	   case CRT2_VGA:
	      cr30 = (SIS_VB_OUTPUT_CRT2 | SIS_SIMULTANEOUS_VIEW_ENABLE);
	      cr31 |= SIS_DRIVER_MODE;
	      if(ivideo->sisfb_nocrt2rate) {
		 cr33 |= (sisbios_mode[ivideo->sisfb_mode_idx].rate_idx << 4);
	      } else {
		 cr33 |= ((ivideo->rate_idx & 0x0F) << 4);
	      }
	      break;

	   default:	/* disable CRT2 */
	      cr30 = 0x00;
	      cr31 |= (SIS_DRIVER_MODE | SIS_VB_OUTPUT_DISABLE);
	}

	SiS_SetReg(SISCR, 0x30, cr30);
	SiS_SetReg(SISCR, 0x33, cr33);

	if(ivideo->chip >= SIS_661) {
#ifdef CONFIG_FB_SIS_315
	   cr31 &= ~0x01;                          /* Clear PAL flag (now in CR35) */
	   SiS_SetRegANDOR(SISCR, 0x35, ~0x10, cr35); /* Leave overscan bit alone */
	   cr38 &= 0x07;                           /* Use only LCDA and HiVision/YPbPr bits */
	   SiS_SetRegANDOR(SISCR, 0x38, 0xf8, cr38);
#endif
	} else if(ivideo->chip != SIS_300) {
	   SiS_SetReg(SISCR, tvregnum, cr38);
	}
	SiS_SetReg(SISCR, 0x31, cr31);

	ivideo->SiS_Pr.SiS_UseOEM = ivideo->sisfb_useoem;

	sisfb_check_engine_and_sync(ivideo);
}