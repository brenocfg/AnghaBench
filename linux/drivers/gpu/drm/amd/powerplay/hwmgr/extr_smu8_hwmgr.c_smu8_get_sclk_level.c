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
typedef  int uint32_t ;
struct TYPE_3__ {struct phm_clock_voltage_dependency_table* vddc_dependency_on_sclk; } ;
struct pp_hwmgr {TYPE_1__ dyn_state; } ;
struct phm_clock_voltage_dependency_table {TYPE_2__* entries; scalar_t__ count; } ;
struct TYPE_4__ {int clk; } ;

/* Variables and functions */
#define  PPSMC_MSG_SetSclkHardMax 131 
#define  PPSMC_MSG_SetSclkHardMin 130 
#define  PPSMC_MSG_SetSclkSoftMax 129 
#define  PPSMC_MSG_SetSclkSoftMin 128 

__attribute__((used)) static uint32_t smu8_get_sclk_level(struct pp_hwmgr *hwmgr,
				uint32_t clock, uint32_t msg)
{
	int i = 0;
	struct phm_clock_voltage_dependency_table *table =
				hwmgr->dyn_state.vddc_dependency_on_sclk;

	switch (msg) {
	case PPSMC_MSG_SetSclkSoftMin:
	case PPSMC_MSG_SetSclkHardMin:
		for (i = 0; i < (int)table->count; i++) {
			if (clock <= table->entries[i].clk)
				break;
		}
		break;

	case PPSMC_MSG_SetSclkSoftMax:
	case PPSMC_MSG_SetSclkHardMax:
		for (i = table->count - 1; i >= 0; i--) {
			if (clock >= table->entries[i].clk)
				break;
		}
		break;

	default:
		break;
	}
	return i;
}