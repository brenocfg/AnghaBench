#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct vega10_single_dpm_table {size_t count; TYPE_3__* dpm_levels; } ;
struct TYPE_7__ {struct vega10_single_dpm_table dclk_table; struct vega10_single_dpm_table vclk_table; } ;
struct TYPE_10__ {int /*<<< orphan*/ * UvdDpmVoltageIndex; int /*<<< orphan*/ * DclkDid; int /*<<< orphan*/ * VclkDid; } ;
struct TYPE_6__ {TYPE_5__ pp_table; } ;
struct vega10_hwmgr {TYPE_2__ dpm_table; TYPE_1__ smc_state_table; } ;
struct pp_hwmgr {scalar_t__ pptable; struct vega10_hwmgr* backend; } ;
struct phm_ppt_v2_information {struct phm_ppt_v1_mm_clock_voltage_dependency_table* mm_dep_table; } ;
struct phm_ppt_v1_mm_clock_voltage_dependency_table {size_t count; TYPE_4__* entries; } ;
struct TYPE_9__ {scalar_t__ vclk; scalar_t__ dclk; int /*<<< orphan*/  vddcInd; } ;
struct TYPE_8__ {scalar_t__ value; } ;
typedef  TYPE_5__ PPTable_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t NUM_UVD_DPM_LEVELS ; 
 int vega10_populate_single_dclock_level (struct pp_hwmgr*,scalar_t__,int /*<<< orphan*/ *) ; 
 int vega10_populate_single_vclock_level (struct pp_hwmgr*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vega10_populate_smc_uvd_levels(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	struct vega10_single_dpm_table *vclk_dpm_table =
			&(data->dpm_table.vclk_table);
	struct vega10_single_dpm_table *dclk_dpm_table =
			&(data->dpm_table.dclk_table);
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)(hwmgr->pptable);
	struct phm_ppt_v1_mm_clock_voltage_dependency_table *dep_table =
			table_info->mm_dep_table;
	int result = -EINVAL;
	uint32_t i, j;

	for (i = 0; i < vclk_dpm_table->count; i++) {
		result = vega10_populate_single_vclock_level(hwmgr,
				vclk_dpm_table->dpm_levels[i].value,
				&(pp_table->VclkDid[i]));
		if (result)
			return result;
	}

	j = i - 1;
	while (i < NUM_UVD_DPM_LEVELS) {
		result = vega10_populate_single_vclock_level(hwmgr,
				vclk_dpm_table->dpm_levels[j].value,
				&(pp_table->VclkDid[i]));
		if (result)
			return result;
		i++;
	}

	for (i = 0; i < dclk_dpm_table->count; i++) {
		result = vega10_populate_single_dclock_level(hwmgr,
				dclk_dpm_table->dpm_levels[i].value,
				&(pp_table->DclkDid[i]));
		if (result)
			return result;
	}

	j = i - 1;
	while (i < NUM_UVD_DPM_LEVELS) {
		result = vega10_populate_single_dclock_level(hwmgr,
				dclk_dpm_table->dpm_levels[j].value,
				&(pp_table->DclkDid[i]));
		if (result)
			return result;
		i++;
	}

	for (i = 0; i < dep_table->count; i++) {
		if (dep_table->entries[i].vclk ==
				vclk_dpm_table->dpm_levels[i].value &&
			dep_table->entries[i].dclk ==
				dclk_dpm_table->dpm_levels[i].value)
			pp_table->UvdDpmVoltageIndex[i] =
					dep_table->entries[i].vddcInd;
		else
			return -1;
	}

	j = i - 1;
	while (i < NUM_UVD_DPM_LEVELS) {
		pp_table->UvdDpmVoltageIndex[i] = dep_table->entries[j].vddcInd;
		i++;
	}

	return 0;
}