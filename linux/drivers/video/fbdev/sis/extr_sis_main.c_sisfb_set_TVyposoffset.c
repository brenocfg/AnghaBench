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
struct sis_video_info {int tvypos; int currentvbflags; int vbflags2; int tvy; int chronteltype; char p2_01; char p2_02; int /*<<< orphan*/  SiS_Pr; int /*<<< orphan*/  modechanged; scalar_t__ sisfblocked; } ;

/* Variables and functions */
 int CRT2_TV ; 
 int /*<<< orphan*/  SISPART2 ; 
 int /*<<< orphan*/  SISSR ; 
 int /*<<< orphan*/  SiS_SetCH700x (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  SiS_SetCH70xxANDOR (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,char) ; 
 int TV_HIVISION ; 
 int TV_YPBPR ; 
 int VB2_CHRONTEL ; 
 int VB2_SISBRIDGE ; 

__attribute__((used)) static void
sisfb_set_TVyposoffset(struct sis_video_info *ivideo, int val)
{
	if(val > 32) val = 32;
	if(val < -32) val = -32;
	ivideo->tvypos = val;

	if(ivideo->sisfblocked) return;
	if(!ivideo->modechanged) return;

	if(ivideo->currentvbflags & CRT2_TV) {

		if(ivideo->vbflags2 & VB2_CHRONTEL) {

			int y = ivideo->tvy;

			switch(ivideo->chronteltype) {
			case 1:
				y -= val;
				if(y < 0) y = 0;
				SiS_SetReg(SISSR, 0x05, 0x86);
				SiS_SetCH700x(&ivideo->SiS_Pr, 0x0b, (y & 0xff));
				SiS_SetCH70xxANDOR(&ivideo->SiS_Pr, 0x08, ((y & 0x0100) >> 8), 0xFE);
				break;
			case 2:
				/* Not supported by hardware */
				break;
			}

		} else if(ivideo->vbflags2 & VB2_SISBRIDGE) {

			char p2_01, p2_02;
			val /= 2;
			p2_01 = ivideo->p2_01;
			p2_02 = ivideo->p2_02;

			p2_01 += val;
			p2_02 += val;
			if(!(ivideo->currentvbflags & (TV_HIVISION | TV_YPBPR))) {
				while((p2_01 <= 0) || (p2_02 <= 0)) {
					p2_01 += 2;
					p2_02 += 2;
				}
			}
			SiS_SetReg(SISPART2, 0x01, p2_01);
			SiS_SetReg(SISPART2, 0x02, p2_02);
		}
	}
}