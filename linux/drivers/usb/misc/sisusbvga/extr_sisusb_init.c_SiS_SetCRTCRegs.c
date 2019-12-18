#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {int /*<<< orphan*/  SiS_P3d4; TYPE_1__* SiS_StandTable; } ;
struct TYPE_2__ {unsigned char* CRTC; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_SetReg (struct SiS_Private*,int /*<<< orphan*/ ,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  SiS_SetRegAND (struct SiS_Private*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
SiS_SetCRTCRegs(struct SiS_Private *SiS_Pr, unsigned short StandTableIndex)
{
	unsigned char CRTCdata;
	unsigned short i;

	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3d4, 0x11, 0x7f);

	for (i = 0; i <= 0x18; i++) {
		CRTCdata = SiS_Pr->SiS_StandTable[StandTableIndex].CRTC[i];
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, i, CRTCdata);
	}
}