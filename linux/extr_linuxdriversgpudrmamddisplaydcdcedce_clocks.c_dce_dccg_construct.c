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
struct dccg {int /*<<< orphan*/  cur_min_clks_state; int /*<<< orphan*/  max_clks_state; int /*<<< orphan*/ * funcs; struct dc_context* ctx; } ;
struct dce_dccg {int dprefclk_ss_divider; int ss_on_dprefclk; scalar_t__ dprefclk_ss_percentage; scalar_t__ dfs_bypass_disp_clk; struct dccg_mask const* clk_mask; struct dccg_shift const* clk_shift; struct dccg_registers const* regs; struct dccg base; } ;
struct dccg_shift {int dummy; } ;
struct dccg_registers {int dummy; } ;
struct dccg_mask {int dummy; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_PP_CLOCKS_STATE_INVALID ; 
 int /*<<< orphan*/  DM_PP_CLOCKS_STATE_NOMINAL ; 
 int /*<<< orphan*/  dce_clock_read_integrated_info (struct dce_dccg*) ; 
 int /*<<< orphan*/  dce_clock_read_ss_info (struct dce_dccg*) ; 
 int /*<<< orphan*/  dce_funcs ; 

__attribute__((used)) static void dce_dccg_construct(
	struct dce_dccg *clk_dce,
	struct dc_context *ctx,
	const struct dccg_registers *regs,
	const struct dccg_shift *clk_shift,
	const struct dccg_mask *clk_mask)
{
	struct dccg *base = &clk_dce->base;

	base->ctx = ctx;
	base->funcs = &dce_funcs;

	clk_dce->regs = regs;
	clk_dce->clk_shift = clk_shift;
	clk_dce->clk_mask = clk_mask;

	clk_dce->dfs_bypass_disp_clk = 0;

	clk_dce->dprefclk_ss_percentage = 0;
	clk_dce->dprefclk_ss_divider = 1000;
	clk_dce->ss_on_dprefclk = false;

	base->max_clks_state = DM_PP_CLOCKS_STATE_NOMINAL;
	base->cur_min_clks_state = DM_PP_CLOCKS_STATE_INVALID;

	dce_clock_read_integrated_info(clk_dce);
	dce_clock_read_ss_info(clk_dce);
}