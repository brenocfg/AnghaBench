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
typedef  int uint32_t ;
struct TYPE_9__ {int soft_min_level; int soft_max_level; int hard_min_level; int hard_max_level; } ;
struct vega20_single_dpm_table {int count; TYPE_5__* dpm_levels; TYPE_4__ dpm_state; } ;
struct vega20_dpm_table {struct vega20_single_dpm_table eclk_table; struct vega20_single_dpm_table soc_table; struct vega20_single_dpm_table dclk_table; struct vega20_single_dpm_table vclk_table; struct vega20_single_dpm_table mem_table; struct vega20_single_dpm_table gfx_table; } ;
struct smu_dpm_context {scalar_t__ dpm_level; TYPE_2__* mclk_latency_table; scalar_t__ dpm_context; } ;
struct smu_context {TYPE_3__* display_config; struct smu_dpm_context smu_dpm; } ;
struct TYPE_10__ {int value; } ;
struct TYPE_8__ {int num_display; int dce_tolerable_mclk_in_active_latency; int min_mem_set_clock; scalar_t__ nb_pstate_switch_disable; int /*<<< orphan*/  multi_monitor_in_sync; } ;
struct TYPE_7__ {int count; TYPE_1__* entries; } ;
struct TYPE_6__ {int latency; } ;

/* Variables and functions */
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK ; 
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK ; 
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_PEAK ; 
 size_t VEGA20_UMD_PSTATE_GFXCLK_LEVEL ; 
 size_t VEGA20_UMD_PSTATE_MCLK_LEVEL ; 
 size_t VEGA20_UMD_PSTATE_SOCCLK_LEVEL ; 
 size_t VEGA20_UMD_PSTATE_UVDCLK_LEVEL ; 
 size_t VEGA20_UMD_PSTATE_VCEMCLK_LEVEL ; 

__attribute__((used)) static int vega20_apply_clocks_adjust_rules(struct smu_context *smu)
{
	struct smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);
	struct vega20_dpm_table *dpm_ctx = (struct vega20_dpm_table *)(smu_dpm_ctx->dpm_context);
	struct vega20_single_dpm_table *dpm_table;
	bool vblank_too_short = false;
	bool disable_mclk_switching;
	uint32_t i, latency;

	disable_mclk_switching = ((1 < smu->display_config->num_display) &&
				  !smu->display_config->multi_monitor_in_sync) || vblank_too_short;
	latency = smu->display_config->dce_tolerable_mclk_in_active_latency;

	/* gfxclk */
	dpm_table = &(dpm_ctx->gfx_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

		if (VEGA20_UMD_PSTATE_GFXCLK_LEVEL < dpm_table->count) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_GFXCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_GFXCLK_LEVEL].value;
		}

		if (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[0].value;
		}

		if (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		}

	/* memclk */
	dpm_table = &(dpm_ctx->mem_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

		if (VEGA20_UMD_PSTATE_MCLK_LEVEL < dpm_table->count) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_MCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_MCLK_LEVEL].value;
		}

		if (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[0].value;
		}

		if (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		}

	/* honour DAL's UCLK Hardmin */
	if (dpm_table->dpm_state.hard_min_level < (smu->display_config->min_mem_set_clock / 100))
		dpm_table->dpm_state.hard_min_level = smu->display_config->min_mem_set_clock / 100;

	/* Hardmin is dependent on displayconfig */
	if (disable_mclk_switching) {
		dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		for (i = 0; i < smu_dpm_ctx->mclk_latency_table->count - 1; i++) {
			if (smu_dpm_ctx->mclk_latency_table->entries[i].latency <= latency) {
				if (dpm_table->dpm_levels[i].value >= (smu->display_config->min_mem_set_clock / 100)) {
					dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[i].value;
					break;
				}
			}
		}
	}

	if (smu->display_config->nb_pstate_switch_disable)
		dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

	/* vclk */
	dpm_table = &(dpm_ctx->vclk_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

		if (VEGA20_UMD_PSTATE_UVDCLK_LEVEL < dpm_table->count) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_UVDCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_UVDCLK_LEVEL].value;
		}

		if (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		}

	/* dclk */
	dpm_table = &(dpm_ctx->dclk_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

		if (VEGA20_UMD_PSTATE_UVDCLK_LEVEL < dpm_table->count) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_UVDCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_UVDCLK_LEVEL].value;
		}

		if (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		}

	/* socclk */
	dpm_table = &(dpm_ctx->soc_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

		if (VEGA20_UMD_PSTATE_SOCCLK_LEVEL < dpm_table->count) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_SOCCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_SOCCLK_LEVEL].value;
		}

		if (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		}

	/* eclk */
	dpm_table = &(dpm_ctx->eclk_table);
	dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
	dpm_table->dpm_state.hard_min_level = dpm_table->dpm_levels[0].value;
	dpm_table->dpm_state.hard_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;

		if (VEGA20_UMD_PSTATE_VCEMCLK_LEVEL < dpm_table->count) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_VCEMCLK_LEVEL].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[VEGA20_UMD_PSTATE_VCEMCLK_LEVEL].value;
		}

		if (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
			dpm_table->dpm_state.soft_min_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
			dpm_table->dpm_state.soft_max_level = dpm_table->dpm_levels[dpm_table->count - 1].value;
		}
	return 0;
}