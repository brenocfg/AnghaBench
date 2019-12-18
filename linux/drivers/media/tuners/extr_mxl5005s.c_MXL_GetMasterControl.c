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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */

__attribute__((used)) static u16 MXL_GetMasterControl(u8 *MasterReg, int state)
{
	if (state == 1) /* Load_Start */
		*MasterReg = 0xF3;
	if (state == 2) /* Power_Down */
		*MasterReg = 0x41;
	if (state == 3) /* Synth_Reset */
		*MasterReg = 0xB1;
	if (state == 4) /* Seq_Off */
		*MasterReg = 0xF1;

	return 0;
}