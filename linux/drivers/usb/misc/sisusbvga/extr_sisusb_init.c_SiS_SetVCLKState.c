#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {int /*<<< orphan*/  SiS_P3c4; TYPE_2__* SiS_VCLKData; TYPE_1__* SiS_RefIndex; } ;
struct TYPE_4__ {unsigned short CLOCK; } ;
struct TYPE_3__ {unsigned short Ext_CRTVCLK; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_SetRegAND (struct SiS_Private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (struct SiS_Private*,int /*<<< orphan*/ ,int,int,unsigned short) ; 

__attribute__((used)) static void
SiS_SetVCLKState(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		 unsigned short rrti)
{
	unsigned short data = 0, VCLK = 0, index = 0;

	if (ModeNo > 0x13) {
		index = SiS_Pr->SiS_RefIndex[rrti].Ext_CRTVCLK;
		VCLK = SiS_Pr->SiS_VCLKData[index].CLOCK;
	}

	if (VCLK >= 166)
		data |= 0x0c;
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x32, 0xf3, data);

	if (VCLK >= 166)
		SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x1f, 0xe7);

	/* DAC speed */
	data = 0x03;
	if (VCLK >= 260)
		data = 0x00;
	else if (VCLK >= 160)
		data = 0x01;
	else if (VCLK >= 135)
		data = 0x02;

	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x07, 0xF8, data);
}