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
struct dm_pp_power_level_change_request {scalar_t__ power_level; } ;
struct TYPE_6__ {int dispclk_khz; } ;
struct TYPE_7__ {TYPE_1__ dce; } ;
struct TYPE_8__ {TYPE_2__ bw; } ;
struct dc_state {TYPE_3__ bw_ctx; } ;
struct clk_mgr_internal {scalar_t__ cur_min_clks_state; int /*<<< orphan*/  dfs_bypass_active; } ;
struct TYPE_9__ {int dispclk_khz; } ;
struct clk_mgr {TYPE_5__* ctx; TYPE_4__ clks; } ;
struct TYPE_10__ {int /*<<< orphan*/  dc; } ;

/* Variables and functions */
 struct clk_mgr_internal* TO_CLK_MGR_INTERNAL (struct clk_mgr*) ; 
 scalar_t__ dce_get_required_clocks_state (struct clk_mgr*,struct dc_state*) ; 
 int /*<<< orphan*/  dce_pplib_apply_display_requirements (int /*<<< orphan*/ ,struct dc_state*) ; 
 int dce_set_clock (struct clk_mgr*,int) ; 
 scalar_t__ dm_pp_apply_power_level_change_request (TYPE_5__*,struct dm_pp_power_level_change_request*) ; 
 scalar_t__ should_set_clock (int,int,int) ; 

__attribute__((used)) static void dce_update_clocks(struct clk_mgr *clk_mgr_base,
			struct dc_state *context,
			bool safe_to_lower)
{
	struct clk_mgr_internal *clk_mgr_dce = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	struct dm_pp_power_level_change_request level_change_req;
	int patched_disp_clk = context->bw_ctx.bw.dce.dispclk_khz;

	/*TODO: W/A for dal3 linux, investigate why this works */
	if (!clk_mgr_dce->dfs_bypass_active)
		patched_disp_clk = patched_disp_clk * 115 / 100;

	level_change_req.power_level = dce_get_required_clocks_state(clk_mgr_base, context);
	/* get max clock state from PPLIB */
	if ((level_change_req.power_level < clk_mgr_dce->cur_min_clks_state && safe_to_lower)
			|| level_change_req.power_level > clk_mgr_dce->cur_min_clks_state) {
		if (dm_pp_apply_power_level_change_request(clk_mgr_base->ctx, &level_change_req))
			clk_mgr_dce->cur_min_clks_state = level_change_req.power_level;
	}

	if (should_set_clock(safe_to_lower, patched_disp_clk, clk_mgr_base->clks.dispclk_khz)) {
		patched_disp_clk = dce_set_clock(clk_mgr_base, patched_disp_clk);
		clk_mgr_base->clks.dispclk_khz = patched_disp_clk;
	}
	dce_pplib_apply_display_requirements(clk_mgr_base->ctx->dc, context);
}