#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dm_pp_static_clock_info {int /*<<< orphan*/  max_clocks_state; int /*<<< orphan*/  member_0; } ;
struct clk_mgr {int /*<<< orphan*/ * funcs; struct dc_context* ctx; } ;
struct dce_clk_mgr {int dprefclk_ss_divider; int ss_on_dprefclk; int /*<<< orphan*/  cur_min_clks_state; int /*<<< orphan*/  max_clks_state; scalar_t__ dprefclk_ss_percentage; scalar_t__ dfs_bypass_disp_clk; struct clk_mgr_mask const* clk_mgr_mask; struct clk_mgr_shift const* clk_mgr_shift; struct clk_mgr_registers const* regs; struct clk_mgr base; } ;
struct dc_context {int dummy; } ;
struct clk_mgr_shift {int dummy; } ;
struct clk_mgr_registers {int dummy; } ;
struct clk_mgr_mask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_PP_CLOCKS_STATE_INVALID ; 
 int /*<<< orphan*/  DM_PP_CLOCKS_STATE_NOMINAL ; 
 int /*<<< orphan*/  dce_clock_read_integrated_info (struct dce_clk_mgr*) ; 
 int /*<<< orphan*/  dce_clock_read_ss_info (struct dce_clk_mgr*) ; 
 int /*<<< orphan*/  dce_funcs ; 
 scalar_t__ dm_pp_get_static_clocks (struct dc_context*,struct dm_pp_static_clock_info*) ; 

__attribute__((used)) static void dce_clk_mgr_construct(
	struct dce_clk_mgr *clk_mgr_dce,
	struct dc_context *ctx,
	const struct clk_mgr_registers *regs,
	const struct clk_mgr_shift *clk_shift,
	const struct clk_mgr_mask *clk_mask)
{
	struct clk_mgr *base = &clk_mgr_dce->base;
	struct dm_pp_static_clock_info static_clk_info = {0};

	base->ctx = ctx;
	base->funcs = &dce_funcs;

	clk_mgr_dce->regs = regs;
	clk_mgr_dce->clk_mgr_shift = clk_shift;
	clk_mgr_dce->clk_mgr_mask = clk_mask;

	clk_mgr_dce->dfs_bypass_disp_clk = 0;

	clk_mgr_dce->dprefclk_ss_percentage = 0;
	clk_mgr_dce->dprefclk_ss_divider = 1000;
	clk_mgr_dce->ss_on_dprefclk = false;


	if (dm_pp_get_static_clocks(ctx, &static_clk_info))
		clk_mgr_dce->max_clks_state = static_clk_info.max_clocks_state;
	else
		clk_mgr_dce->max_clks_state = DM_PP_CLOCKS_STATE_NOMINAL;
	clk_mgr_dce->cur_min_clks_state = DM_PP_CLOCKS_STATE_INVALID;

	dce_clock_read_integrated_info(clk_mgr_dce);
	dce_clock_read_ss_info(clk_mgr_dce);
}