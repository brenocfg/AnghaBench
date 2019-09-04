#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int count; TYPE_1__* entries; } ;
struct smu7_hwmgr {scalar_t__ vdd_gfx_control; TYPE_2__ vddgfx_voltage_table; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct TYPE_7__ {unsigned int VddGfxLevelCount; int /*<<< orphan*/ * VddGfxTable; } ;
struct TYPE_5__ {int value; } ;
typedef  TYPE_3__ SMU72_Discrete_DpmTable ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERT_FROM_HOST_TO_SMC_UL (unsigned int) ; 
 int /*<<< orphan*/  PP_HOST_TO_SMC_US (int) ; 
 scalar_t__ SMU7_VOLTAGE_CONTROL_BY_SVID2 ; 
 int VOLTAGE_SCALE ; 

__attribute__((used)) static int tonga_populate_smc_vdd_gfx_table(struct pp_hwmgr *hwmgr,
			SMU72_Discrete_DpmTable *table)
{
	unsigned int count;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	if (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->vdd_gfx_control) {
		table->VddGfxLevelCount = data->vddgfx_voltage_table.count;
		for (count = 0; count < data->vddgfx_voltage_table.count; count++) {
			table->VddGfxTable[count] =
				PP_HOST_TO_SMC_US(data->vddgfx_voltage_table.entries[count].value * VOLTAGE_SCALE);
		}
		CONVERT_FROM_HOST_TO_SMC_UL(table->VddGfxLevelCount);
	}
	return 0;
}