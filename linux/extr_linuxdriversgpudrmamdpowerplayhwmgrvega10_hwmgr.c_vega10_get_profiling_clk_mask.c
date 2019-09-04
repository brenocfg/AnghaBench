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
struct pp_hwmgr {int /*<<< orphan*/  pstate_mclk; int /*<<< orphan*/  pstate_sclk; scalar_t__ pptable; } ;
struct phm_ppt_v2_information {TYPE_5__* vdd_dep_on_mclk; TYPE_4__* vdd_dep_on_socclk; TYPE_3__* vdd_dep_on_sclk; } ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;
struct TYPE_10__ {size_t count; TYPE_2__* entries; } ;
struct TYPE_9__ {scalar_t__ count; } ;
struct TYPE_8__ {size_t count; TYPE_1__* entries; } ;
struct TYPE_7__ {int /*<<< orphan*/  clk; } ;
struct TYPE_6__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_PEAK ; 
 size_t VEGA10_UMD_PSTATE_GFXCLK_LEVEL ; 
 size_t VEGA10_UMD_PSTATE_MCLK_LEVEL ; 
 scalar_t__ VEGA10_UMD_PSTATE_SOCCLK_LEVEL ; 

__attribute__((used)) static int vega10_get_profiling_clk_mask(struct pp_hwmgr *hwmgr, enum amd_dpm_forced_level level,
				uint32_t *sclk_mask, uint32_t *mclk_mask, uint32_t *soc_mask)
{
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)(hwmgr->pptable);

	if (table_info->vdd_dep_on_sclk->count > VEGA10_UMD_PSTATE_GFXCLK_LEVEL &&
		table_info->vdd_dep_on_socclk->count > VEGA10_UMD_PSTATE_SOCCLK_LEVEL &&
		table_info->vdd_dep_on_mclk->count > VEGA10_UMD_PSTATE_MCLK_LEVEL) {
		*sclk_mask = VEGA10_UMD_PSTATE_GFXCLK_LEVEL;
		*soc_mask = VEGA10_UMD_PSTATE_SOCCLK_LEVEL;
		*mclk_mask = VEGA10_UMD_PSTATE_MCLK_LEVEL;
		hwmgr->pstate_sclk = table_info->vdd_dep_on_sclk->entries[VEGA10_UMD_PSTATE_GFXCLK_LEVEL].clk;
		hwmgr->pstate_mclk = table_info->vdd_dep_on_mclk->entries[VEGA10_UMD_PSTATE_MCLK_LEVEL].clk;
	}

	if (level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK) {
		*sclk_mask = 0;
	} else if (level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK) {
		*mclk_mask = 0;
	} else if (level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
		*sclk_mask = table_info->vdd_dep_on_sclk->count - 1;
		*soc_mask = table_info->vdd_dep_on_socclk->count - 1;
		*mclk_mask = table_info->vdd_dep_on_mclk->count - 1;
	}
	return 0;
}