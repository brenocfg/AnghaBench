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
struct SiS_Private {int SiS_UseWide; TYPE_3__* SiS_RefIndex; TYPE_2__* SiS_CRT1Table; TYPE_1__* SiS_EModeIDTable; } ;
struct TYPE_6__ {int Ext_InfoFlag; unsigned short Ext_CRT1CRTC_WIDE; unsigned short Ext_CRT1CRTC_NORM; unsigned short Ext_CRT1CRTC; } ;
struct TYPE_5__ {unsigned char* CR; } ;
struct TYPE_4__ {unsigned short REFindex; } ;

/* Variables and functions */
 int HaveWideTiming ; 
 int InterlaceMode ; 
 int /*<<< orphan*/  SiSInitPtr (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_SearchModeID (struct SiS_Private*,unsigned short*,unsigned short*) ; 

bool
sisfb_gettotalfrommode(struct SiS_Private *SiS_Pr, unsigned char modeno, int *htotal,
			int *vtotal, unsigned char rateindex)
{
    unsigned short ModeNo = modeno;
    unsigned short ModeIdIndex = 0, CRT1Index = 0;
    unsigned short RRTI = 0;
    unsigned char  sr_data, cr_data, cr_data2;

    if(!SiSInitPtr(SiS_Pr)) return false;

    if(rateindex > 0) rateindex--;

#ifdef CONFIG_FB_SIS_315
    switch(ModeNo) {
       case 0x5a: ModeNo = 0x50; break;
       case 0x5b: ModeNo = 0x56;
    }
#endif

    if(!(SiS_SearchModeID(SiS_Pr, &ModeNo, &ModeIdIndex))) return false;

    RRTI = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].REFindex;
    if(SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag & HaveWideTiming) {
       if(SiS_Pr->SiS_UseWide == 1) {
	  /* Wide screen: Ignore rateindex */
	  CRT1Index = SiS_Pr->SiS_RefIndex[RRTI].Ext_CRT1CRTC_WIDE;
       } else {
	  RRTI += rateindex;
	  CRT1Index = SiS_Pr->SiS_RefIndex[RRTI].Ext_CRT1CRTC_NORM;
       }
    } else {
       RRTI += rateindex;
       CRT1Index = SiS_Pr->SiS_RefIndex[RRTI].Ext_CRT1CRTC;
    }

    sr_data = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[14];
    cr_data = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[0];
    *htotal = (((cr_data & 0xff) | ((unsigned short) (sr_data & 0x03) << 8)) + 5) * 8;

    sr_data = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[13];
    cr_data = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[6];
    cr_data2 = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[7];
    *vtotal = ((cr_data & 0xFF) |
	       ((unsigned short)(cr_data2 & 0x01) <<  8) |
	       ((unsigned short)(cr_data2 & 0x20) <<  4) |
	       ((unsigned short)(sr_data  & 0x01) << 10)) + 2;

    if(SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag & InterlaceMode)
       *vtotal *= 2;

    return true;
}