#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct vega12_single_dpm_table {scalar_t__ count; } ;
struct TYPE_2__ {struct vega12_single_dpm_table soc_table; struct vega12_single_dpm_table mem_table; struct vega12_single_dpm_table gfx_table; } ;
struct vega12_hwmgr {TYPE_1__ dpm_table; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;

/* Variables and functions */
 int AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_PEAK ; 
 scalar_t__ VEGA12_UMD_PSTATE_GFXCLK_LEVEL ; 
 scalar_t__ VEGA12_UMD_PSTATE_MCLK_LEVEL ; 
 scalar_t__ VEGA12_UMD_PSTATE_SOCCLK_LEVEL ; 

__attribute__((used)) static int vega12_get_profiling_clk_mask(struct pp_hwmgr *hwmgr, enum amd_dpm_forced_level level,
				uint32_t *sclk_mask, uint32_t *mclk_mask, uint32_t *soc_mask)
{
	struct vega12_hwmgr *data = (struct vega12_hwmgr *)(hwmgr->backend);
	struct vega12_single_dpm_table *gfx_dpm_table = &(data->dpm_table.gfx_table);
	struct vega12_single_dpm_table *mem_dpm_table = &(data->dpm_table.mem_table);
	struct vega12_single_dpm_table *soc_dpm_table = &(data->dpm_table.soc_table);

	*sclk_mask = 0;
	*mclk_mask = 0;
	*soc_mask  = 0;

	if (gfx_dpm_table->count > VEGA12_UMD_PSTATE_GFXCLK_LEVEL &&
	    mem_dpm_table->count > VEGA12_UMD_PSTATE_MCLK_LEVEL &&
	    soc_dpm_table->count > VEGA12_UMD_PSTATE_SOCCLK_LEVEL) {
		*sclk_mask = VEGA12_UMD_PSTATE_GFXCLK_LEVEL;
		*mclk_mask = VEGA12_UMD_PSTATE_MCLK_LEVEL;
		*soc_mask  = VEGA12_UMD_PSTATE_SOCCLK_LEVEL;
	}

	if (level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK) {
		*sclk_mask = 0;
	} else if (level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK) {
		*mclk_mask = 0;
	} else if (level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
		*sclk_mask = gfx_dpm_table->count - 1;
		*mclk_mask = mem_dpm_table->count - 1;
		*soc_mask  = soc_dpm_table->count - 1;
	}

	return 0;
}