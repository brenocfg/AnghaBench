#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dm_pp_display_configuration {int /*<<< orphan*/  disp_clk_khz; int /*<<< orphan*/  min_dcfclock_khz; int /*<<< orphan*/  min_dcfc_deep_sleep_clock_khz; int /*<<< orphan*/  min_engine_clock_deep_sleep_khz; int /*<<< orphan*/  min_memory_clock_khz; int /*<<< orphan*/  min_engine_clock_khz; } ;
struct dc_state {struct dm_pp_display_configuration pp_display_cfg; } ;
struct dc {struct dm_pp_display_configuration prev_display_config; int /*<<< orphan*/  ctx; TYPE_3__* res_pool; } ;
struct TYPE_6__ {TYPE_2__* dccg; } ;
struct TYPE_4__ {int /*<<< orphan*/  dispclk_khz; int /*<<< orphan*/  dcfclk_khz; int /*<<< orphan*/  dcfclk_deep_sleep_khz; int /*<<< orphan*/  fclk_khz; } ;
struct TYPE_5__ {TYPE_1__ clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce110_fill_display_configs (struct dc_state*,struct dm_pp_display_configuration*) ; 
 int /*<<< orphan*/  dm_pp_apply_display_requirements (int /*<<< orphan*/ ,struct dm_pp_display_configuration*) ; 
 scalar_t__ memcmp (struct dm_pp_display_configuration*,struct dm_pp_display_configuration*,int) ; 

__attribute__((used)) static void dcn10_pplib_apply_display_requirements(
	struct dc *dc,
	struct dc_state *context)
{
	struct dm_pp_display_configuration *pp_display_cfg = &context->pp_display_cfg;

	pp_display_cfg->min_engine_clock_khz = dc->res_pool->dccg->clks.dcfclk_khz;
	pp_display_cfg->min_memory_clock_khz = dc->res_pool->dccg->clks.fclk_khz;
	pp_display_cfg->min_engine_clock_deep_sleep_khz = dc->res_pool->dccg->clks.dcfclk_deep_sleep_khz;
	pp_display_cfg->min_dcfc_deep_sleep_clock_khz = dc->res_pool->dccg->clks.dcfclk_deep_sleep_khz;
	pp_display_cfg->min_dcfclock_khz = dc->res_pool->dccg->clks.dcfclk_khz;
	pp_display_cfg->disp_clk_khz = dc->res_pool->dccg->clks.dispclk_khz;
	dce110_fill_display_configs(context, pp_display_cfg);

	if (memcmp(&dc->prev_display_config, pp_display_cfg, sizeof(
			struct dm_pp_display_configuration)) !=  0)
		dm_pp_apply_display_requirements(dc->ctx, pp_display_cfg);

	dc->prev_display_config = *pp_display_cfg;
}