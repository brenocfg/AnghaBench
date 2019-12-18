#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pp_hwmgr {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {int reg; int data; } ;
typedef  TYPE_1__ PWR_Command_Table ;

/* Variables and functions */
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void execute_pwr_table(struct pp_hwmgr *hwmgr, const PWR_Command_Table *pvirus, int size)
{
	int i;
	uint32_t reg, data;

	for (i = 0; i < size; i++) {
		reg  = pvirus->reg;
		data = pvirus->data;
		if (reg != 0xffffffff)
			cgs_write_register(hwmgr->device, reg, data);
		else
			break;
		pvirus++;
	}
}