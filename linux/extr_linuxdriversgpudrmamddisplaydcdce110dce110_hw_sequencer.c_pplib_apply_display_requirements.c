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
struct dm_pp_display_configuration {int nb_pstate_switch_disable; int cpu_cc6_disable; int cpu_pstate_disable; int min_memory_clock_khz; int display_count; int line_time_in_us; TYPE_7__* disp_configs; int /*<<< orphan*/  crtc_index; int /*<<< orphan*/  disp_clk_khz; scalar_t__ avail_mclk_switch_time_in_disp_active_us; int /*<<< orphan*/  avail_mclk_switch_time_us; int /*<<< orphan*/  min_engine_clock_deep_sleep_khz; int /*<<< orphan*/  min_engine_clock_khz; int /*<<< orphan*/  min_dcfclock_khz; int /*<<< orphan*/  cpu_pstate_separation_time; int /*<<< orphan*/  all_displays_in_sync; } ;
struct TYPE_8__ {int nbp_state_change_enable; int cpuc_state_change_enable; int cpup_state_change_enable; int yclk_khz; int /*<<< orphan*/  sclk_deep_sleep_khz; int /*<<< orphan*/  sclk_khz; int /*<<< orphan*/  blackout_recovery_time_us; int /*<<< orphan*/  all_displays_in_sync; } ;
struct TYPE_9__ {TYPE_1__ dce; } ;
struct dc_state {TYPE_6__** streams; TYPE_2__ bw; struct dm_pp_display_configuration pp_display_cfg; } ;
struct dc_crtc_timing {int h_total; int pix_clk_khz; } ;
struct dc {struct dm_pp_display_configuration prev_display_config; int /*<<< orphan*/  ctx; TYPE_5__* res_pool; } ;
struct TYPE_14__ {int /*<<< orphan*/  pipe_idx; } ;
struct TYPE_13__ {struct dc_crtc_timing timing; } ;
struct TYPE_12__ {TYPE_4__* dccg; } ;
struct TYPE_10__ {int /*<<< orphan*/  dispclk_khz; } ;
struct TYPE_11__ {TYPE_3__ clks; } ;

/* Variables and functions */
 int MEMORY_TYPE_MULTIPLIER ; 
 int /*<<< orphan*/  dce110_fill_display_configs (struct dc_state*,struct dm_pp_display_configuration*) ; 
 int /*<<< orphan*/  dce110_get_min_vblank_time_us (struct dc_state*) ; 
 int /*<<< orphan*/  determine_sclk_from_bounding_box (struct dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_pp_apply_display_requirements (int /*<<< orphan*/ ,struct dm_pp_display_configuration*) ; 
 scalar_t__ memcmp (struct dm_pp_display_configuration*,struct dm_pp_display_configuration*,int) ; 

__attribute__((used)) static void pplib_apply_display_requirements(
	struct dc *dc,
	struct dc_state *context)
{
	struct dm_pp_display_configuration *pp_display_cfg = &context->pp_display_cfg;

	pp_display_cfg->all_displays_in_sync =
		context->bw.dce.all_displays_in_sync;
	pp_display_cfg->nb_pstate_switch_disable =
			context->bw.dce.nbp_state_change_enable == false;
	pp_display_cfg->cpu_cc6_disable =
			context->bw.dce.cpuc_state_change_enable == false;
	pp_display_cfg->cpu_pstate_disable =
			context->bw.dce.cpup_state_change_enable == false;
	pp_display_cfg->cpu_pstate_separation_time =
			context->bw.dce.blackout_recovery_time_us;

	pp_display_cfg->min_memory_clock_khz = context->bw.dce.yclk_khz
		/ MEMORY_TYPE_MULTIPLIER;

	pp_display_cfg->min_engine_clock_khz = determine_sclk_from_bounding_box(
			dc,
			context->bw.dce.sclk_khz);

	pp_display_cfg->min_dcfclock_khz = pp_display_cfg->min_engine_clock_khz;

	pp_display_cfg->min_engine_clock_deep_sleep_khz
			= context->bw.dce.sclk_deep_sleep_khz;

	pp_display_cfg->avail_mclk_switch_time_us =
						dce110_get_min_vblank_time_us(context);
	/* TODO: dce11.2*/
	pp_display_cfg->avail_mclk_switch_time_in_disp_active_us = 0;

	pp_display_cfg->disp_clk_khz = dc->res_pool->dccg->clks.dispclk_khz;

	dce110_fill_display_configs(context, pp_display_cfg);

	/* TODO: is this still applicable?*/
	if (pp_display_cfg->display_count == 1) {
		const struct dc_crtc_timing *timing =
			&context->streams[0]->timing;

		pp_display_cfg->crtc_index =
			pp_display_cfg->disp_configs[0].pipe_idx;
		pp_display_cfg->line_time_in_us = timing->h_total * 1000
							/ timing->pix_clk_khz;
	}

	if (memcmp(&dc->prev_display_config, pp_display_cfg, sizeof(
			struct dm_pp_display_configuration)) !=  0)
		dm_pp_apply_display_requirements(dc->ctx, pp_display_cfg);

	dc->prev_display_config = *pp_display_cfg;
}