#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_13__ {scalar_t__ sclk_bootup_value; scalar_t__ mclk_bootup_value; } ;
struct smu7_hwmgr {TYPE_6__ vbios_boot_state; } ;
struct TYPE_12__ {TYPE_4__* vddc_dependency_on_mclk; TYPE_2__* vddc_dependency_on_sclk; } ;
struct pp_hwmgr {TYPE_5__ dyn_state; scalar_t__ smu_backend; scalar_t__ backend; } ;
struct TYPE_14__ {size_t GraphicsBootLevel; size_t MemoryBootLevel; } ;
struct ci_smumgr {TYPE_7__ smc_state_table; } ;
struct TYPE_11__ {TYPE_3__* entries; scalar_t__ count; } ;
struct TYPE_10__ {scalar_t__ clk; } ;
struct TYPE_9__ {TYPE_1__* entries; scalar_t__ count; } ;
struct TYPE_8__ {scalar_t__ clk; } ;

/* Variables and functions */

__attribute__((used)) static int ci_populate_smc_initial_state(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct ci_smumgr *smu_data = (struct ci_smumgr *)(hwmgr->smu_backend);
	uint8_t count, level;

	count = (uint8_t)(hwmgr->dyn_state.vddc_dependency_on_sclk->count);

	for (level = 0; level < count; level++) {
		if (hwmgr->dyn_state.vddc_dependency_on_sclk->entries[level].clk
			 >= data->vbios_boot_state.sclk_bootup_value) {
			smu_data->smc_state_table.GraphicsBootLevel = level;
			break;
		}
	}

	count = (uint8_t)(hwmgr->dyn_state.vddc_dependency_on_mclk->count);

	for (level = 0; level < count; level++) {
		if (hwmgr->dyn_state.vddc_dependency_on_mclk->entries[level].clk
			>= data->vbios_boot_state.mclk_bootup_value) {
			smu_data->smc_state_table.MemoryBootLevel = level;
			break;
		}
	}

	return 0;
}