#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {int count; } ;
struct TYPE_13__ {TYPE_10__ pcie_speed_table; } ;
struct TYPE_22__ {int count; TYPE_3__* dpm_levels; } ;
struct TYPE_15__ {int count; TYPE_1__* dpm_levels; } ;
struct smu7_dpm_table {TYPE_9__ mclk_table; TYPE_2__ sclk_table; } ;
struct smu7_hwmgr {TYPE_11__ dpm_table; struct smu7_dpm_table golden_dpm_table; } ;
struct TYPE_19__ {TYPE_5__* vddc_dependency_on_sclk; } ;
struct pp_hwmgr {scalar_t__ pp_table_version; int pstate_sclk; int pstate_mclk; scalar_t__ pptable; TYPE_6__ dyn_state; scalar_t__ backend; } ;
struct phm_ppt_v1_information {TYPE_8__* vdd_dep_on_sclk; } ;
typedef  int int32_t ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;
struct TYPE_21__ {int count; TYPE_7__* entries; } ;
struct TYPE_20__ {int clk; } ;
struct TYPE_18__ {int count; TYPE_4__* entries; } ;
struct TYPE_17__ {int clk; } ;
struct TYPE_16__ {int value; } ;
struct TYPE_14__ {int value; } ;

/* Variables and functions */
 int AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_PEAK ; 
 int EINVAL ; 
 scalar_t__ PP_TABLE_V0 ; 
 scalar_t__ PP_TABLE_V1 ; 

__attribute__((used)) static int smu7_get_profiling_clk(struct pp_hwmgr *hwmgr, enum amd_dpm_forced_level level,
				uint32_t *sclk_mask, uint32_t *mclk_mask, uint32_t *pcie_mask)
{
	uint32_t percentage;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct smu7_dpm_table *golden_dpm_table = &data->golden_dpm_table;
	int32_t tmp_mclk;
	int32_t tmp_sclk;
	int32_t count;

	if (golden_dpm_table->mclk_table.count < 1)
		return -EINVAL;

	percentage = 100 * golden_dpm_table->sclk_table.dpm_levels[golden_dpm_table->sclk_table.count - 1].value /
			golden_dpm_table->mclk_table.dpm_levels[golden_dpm_table->mclk_table.count - 1].value;

	if (golden_dpm_table->mclk_table.count == 1) {
		percentage = 70;
		tmp_mclk = golden_dpm_table->mclk_table.dpm_levels[golden_dpm_table->mclk_table.count - 1].value;
		*mclk_mask = golden_dpm_table->mclk_table.count - 1;
	} else {
		tmp_mclk = golden_dpm_table->mclk_table.dpm_levels[golden_dpm_table->mclk_table.count - 2].value;
		*mclk_mask = golden_dpm_table->mclk_table.count - 2;
	}

	tmp_sclk = tmp_mclk * percentage / 100;

	if (hwmgr->pp_table_version == PP_TABLE_V0) {
		for (count = hwmgr->dyn_state.vddc_dependency_on_sclk->count-1;
			count >= 0; count--) {
			if (tmp_sclk >= hwmgr->dyn_state.vddc_dependency_on_sclk->entries[count].clk) {
				tmp_sclk = hwmgr->dyn_state.vddc_dependency_on_sclk->entries[count].clk;
				*sclk_mask = count;
				break;
			}
		}
		if (count < 0 || level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK) {
			*sclk_mask = 0;
			tmp_sclk = hwmgr->dyn_state.vddc_dependency_on_sclk->entries[0].clk;
		}

		if (level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK)
			*sclk_mask = hwmgr->dyn_state.vddc_dependency_on_sclk->count-1;
	} else if (hwmgr->pp_table_version == PP_TABLE_V1) {
		struct phm_ppt_v1_information *table_info =
				(struct phm_ppt_v1_information *)(hwmgr->pptable);

		for (count = table_info->vdd_dep_on_sclk->count-1; count >= 0; count--) {
			if (tmp_sclk >= table_info->vdd_dep_on_sclk->entries[count].clk) {
				tmp_sclk = table_info->vdd_dep_on_sclk->entries[count].clk;
				*sclk_mask = count;
				break;
			}
		}
		if (count < 0 || level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK) {
			*sclk_mask = 0;
			tmp_sclk =  table_info->vdd_dep_on_sclk->entries[0].clk;
		}

		if (level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK)
			*sclk_mask = table_info->vdd_dep_on_sclk->count - 1;
	}

	if (level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK)
		*mclk_mask = 0;
	else if (level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK)
		*mclk_mask = golden_dpm_table->mclk_table.count - 1;

	*pcie_mask = data->dpm_table.pcie_speed_table.count - 1;
	hwmgr->pstate_sclk = tmp_sclk;
	hwmgr->pstate_mclk = tmp_mclk;

	return 0;
}