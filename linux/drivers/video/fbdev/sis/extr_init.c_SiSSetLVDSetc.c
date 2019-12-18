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
struct SiS_Private {int SiS_IF_DEF_LVDS; int SiS_IF_DEF_TRUMPION; int SiS_IF_DEF_CH70xx; int SiS_IF_DEF_CONEX; int ChipType; int /*<<< orphan*/  SiS_P3d4; int /*<<< orphan*/  SiS_Backup70xx; int /*<<< orphan*/  SiS_Part4Port; scalar_t__ SiS_ChrontelInit; } ;

/* Variables and functions */
#define  SIS_330 142 
#define  SIS_340 141 
#define  SIS_540 140 
#define  SIS_550 139 
#define  SIS_630 138 
#define  SIS_650 137 
#define  SIS_660 136 
#define  SIS_661 135 
#define  SIS_730 134 
#define  SIS_740 133 
#define  SIS_741 132 
#define  SIS_760 131 
#define  SIS_761 130 
 int /*<<< orphan*/  SiS_GetCH700x (struct SiS_Private*,int) ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
#define  XGI_20 129 
#define  XGI_40 128 

__attribute__((used)) static
void
SiSSetLVDSetc(struct SiS_Private *SiS_Pr)
{
   unsigned short temp;

   SiS_Pr->SiS_IF_DEF_LVDS = 0;
   SiS_Pr->SiS_IF_DEF_TRUMPION = 0;
   SiS_Pr->SiS_IF_DEF_CH70xx = 0;
   SiS_Pr->SiS_IF_DEF_CONEX = 0;

   SiS_Pr->SiS_ChrontelInit = 0;

   if(SiS_Pr->ChipType == XGI_20) return;

   /* Check for SiS30x first */
   temp = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x00);
   if((temp == 1) || (temp == 2)) return;

   switch(SiS_Pr->ChipType) {
#ifdef CONFIG_FB_SIS_300
   case SIS_540:
   case SIS_630:
   case SIS_730:
	temp = (SiS_GetReg(SiS_Pr->SiS_P3d4,0x37) & 0x0e) >> 1;
	if((temp >= 2) && (temp <= 5))	SiS_Pr->SiS_IF_DEF_LVDS = 1;
	if(temp == 3)			SiS_Pr->SiS_IF_DEF_TRUMPION = 1;
	if((temp == 4) || (temp == 5)) {
		/* Save power status (and error check) - UNUSED */
		SiS_Pr->SiS_Backup70xx = SiS_GetCH700x(SiS_Pr, 0x0e);
		SiS_Pr->SiS_IF_DEF_CH70xx = 1;
	}
	break;
#endif
#ifdef CONFIG_FB_SIS_315
   case SIS_550:
   case SIS_650:
   case SIS_740:
   case SIS_330:
	temp = (SiS_GetReg(SiS_Pr->SiS_P3d4,0x37) & 0x0e) >> 1;
	if((temp >= 2) && (temp <= 3))	SiS_Pr->SiS_IF_DEF_LVDS = 1;
	if(temp == 3)			SiS_Pr->SiS_IF_DEF_CH70xx = 2;
	break;
   case SIS_661:
   case SIS_741:
   case SIS_660:
   case SIS_760:
   case SIS_761:
   case SIS_340:
   case XGI_20:
   case XGI_40:
	temp = (SiS_GetReg(SiS_Pr->SiS_P3d4,0x38) & 0xe0) >> 5;
	if((temp >= 2) && (temp <= 3)) 	SiS_Pr->SiS_IF_DEF_LVDS = 1;
	if(temp == 3)			SiS_Pr->SiS_IF_DEF_CH70xx = 2;
	if(temp == 4)			SiS_Pr->SiS_IF_DEF_CONEX = 1;  /* Not yet supported */
	break;
#endif
   default:
	break;
   }
}