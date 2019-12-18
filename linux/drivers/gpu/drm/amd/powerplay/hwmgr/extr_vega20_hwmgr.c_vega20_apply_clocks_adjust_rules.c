#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_11__ {int soft_min_level; int soft_max_level; int hard_min_level; void* hard_max_level; } ;
struct vega20_single_dpm_table {size_t count; TYPE_6__* dpm_levels; TYPE_5__ dpm_state; } ;
struct TYPE_10__ {struct vega20_single_dpm_table eclk_table; struct vega20_single_dpm_table soc_table; struct vega20_single_dpm_table dclk_table; struct vega20_single_dpm_table vclk_table; struct vega20_single_dpm_table fclk_table; struct vega20_single_dpm_table mem_table; struct vega20_single_dpm_table gfx_table; } ;
struct TYPE_8__ {int count; TYPE_1__* entries; } ;
struct vega20_hwmgr {TYPE_4__ dpm_table; TYPE_2__ mclk_latency_table; } ;
struct pp_hwmgr {scalar_t__ dpm_level; TYPE_3__* display_config; scalar_t__ backend; } ;
struct TYPE_12__ {int value; } ;
struct TYPE_9__ {int num_display; int dce_tolerable_mclk_in_active_latency; int min_mem_set_clock; scalar_t__ nb_pstate_switch_disable; int /*<<< orphan*/  multi_monitor_in_sync; } ;
struct TYPE_7__ {int latency; } ;

/* Variables and functions */
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK ; 
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK ; 
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_PEAK ; 
 int /*<<< orphan*/  PHM_PlatformCaps_UMDPState ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 size_t VEGA20_UMD_PSTATE_GFXCLK_LEVEL ; 
 size_t VEGA20_UMD_PSTATE_MCLK_LEVEL ; 
 size_t VEGA20_UMD_PSTATE_SOCCLK_LEVEL ; 
 size_t VEGA20_UMD_PSTATE_UVDCLK_LEVEL ; 
 size_t VEGA20_UMD_PSTATE_VCEMCLK_LEVEL ; 
 void* VG20_CLOCK_MAX_DEFAULT ; 

__attribute__((used)) static int vega20_apply_clocks_adjust_rules(struct pp_hwmgr *hwmgr)
{
	struct vega20_hwmgr *data = (struct vega20_hwmgr *)(hwmgr->backend);
	struct vega20_single_dpm_table *dpm_table;
	bool vblank_too_short = false;
	bool disable_mclk_switching;
	bool disable_fclk_switching;
	uint32_t i, latency;

	disable_mclk_switching = ((1 < hwmgr->display_config->num_display) &&
                           !hwmgr->display_config->multi_monitor_in_sync) ||
                            vblank_too_short;
	latency = hwmgr->display_config->dce_tolerable_mclk_in_active_latency;

	/* gfxclk */
	dpm_table = &(data->dpm_table.gfx_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = VG20_CLOCK_MAX_DEFAULT;

	if (PP_CAP(PHM_PlatformCaps_UMDPState)) {
		if (VEGA20_UMD_PSTATE_GFXCLK_LEVEL < dpm_table->count) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_GFXCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_GFXCLK_LEVEL].value;
		}

		if (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[0].value;
		}

		if (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		}
	}

	/* memclk */
	dpm_table = &(data->dpm_table.mem_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = VG20_CLOCK_MAX_DEFAULT;

	if (PP_CAP(PHM_PlatformCaps_UMDPState)) {
		if (VEGA20_UMD_PSTATE_MCLK_LEVEL < dpm_table->count) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_MCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_MCLK_LEVEL].value;
		}

		if (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[0].value;
		}

		if (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		}
	}

	/* honour DAL's UCLK Hardmin */
	if (dpm_table->dpm_state.hard_min_level < (hwmgr->display_config->min_mem_set_clock / 100))
		dpm_table->dpm_state.hard_min_level = hwmgr->display_config->min_mem_set_clock / 100;

	/* Hardmin is dependent on displayconfig */
	if (disable_mclk_switching) {
		dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		for (i = 0; i < data->mclk_latency_table.count - 1; i++) {
			if (data->mclk_latency_table.entries[i].latency <= latency) {
				if (dpm_table->dpm_levels[i].value >= (hwmgr->display_config->min_mem_set_clock / 100)) {
					dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[i].value;
					break;
				}
			}
		}
	}

	if (hwmgr->display_config->nb_pstate_switch_disable)
		dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

	if ((disable_mclk_switching &&
	    (dpm_table->dpm_state.hard_min_level == dpm_table->dpm_levels[dpm_table->count - 1].value)) ||
	     hwmgr->display_config->min_mem_set_clock / 100 >= dpm_table->dpm_levels[dpm_table->count - 1].value)
		disable_fclk_switching = true;
	else
		disable_fclk_switching = false;

	/* fclk */
	dpm_table = &(data->dpm_table.fclk_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = VG20_CLOCK_MAX_DEFAULT;
	if (hwmgr->display_config->nb_pstate_switch_disable || disable_fclk_switching)
		dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

	/* vclk */
	dpm_table = &(data->dpm_table.vclk_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = VG20_CLOCK_MAX_DEFAULT;

	if (PP_CAP(PHM_PlatformCaps_UMDPState)) {
		if (VEGA20_UMD_PSTATE_UVDCLK_LEVEL < dpm_table->count) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_UVDCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_UVDCLK_LEVEL].value;
		}

		if (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		}
	}

	/* dclk */
	dpm_table = &(data->dpm_table.dclk_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = VG20_CLOCK_MAX_DEFAULT;

	if (PP_CAP(PHM_PlatformCaps_UMDPState)) {
		if (VEGA20_UMD_PSTATE_UVDCLK_LEVEL < dpm_table->count) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_UVDCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_UVDCLK_LEVEL].value;
		}

		if (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		}
	}

	/* socclk */
	dpm_table = &(data->dpm_table.soc_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = VG20_CLOCK_MAX_DEFAULT;

	if (PP_CAP(PHM_PlatformCaps_UMDPState)) {
		if (VEGA20_UMD_PSTATE_SOCCLK_LEVEL < dpm_table->count) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_SOCCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_SOCCLK_LEVEL].value;
		}

		if (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		}
	}

	/* eclk */
	dpm_table = &(data->dpm_table.eclk_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = VG20_CLOCK_MAX_DEFAULT;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = VG20_CLOCK_MAX_DEFAULT;

	if (PP_CAP(PHM_PlatformCaps_UMDPState)) {
		if (VEGA20_UMD_PSTATE_VCEMCLK_LEVEL < dpm_table->count) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_VCEMCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_VCEMCLK_LEVEL].value;
		}

		if (hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		}
	}

	return 0;
}