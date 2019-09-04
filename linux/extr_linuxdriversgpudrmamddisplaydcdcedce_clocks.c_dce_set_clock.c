#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dce_dccg {int dentist_vco_freq_khz; int dfs_bypass_disp_clk; scalar_t__ dfs_bypass_enabled; } ;
struct dccg {int /*<<< orphan*/  cur_min_clks_state; TYPE_1__* ctx; } ;
struct dc_bios {TYPE_2__* funcs; } ;
struct bp_pixel_clock_parameters {int target_pixel_clock; int dfs_bypass_display_clock; int /*<<< orphan*/  pll_id; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* program_display_engine_pll ) (struct dc_bios*,struct bp_pixel_clock_parameters*) ;} ;
struct TYPE_3__ {struct dc_bios* dc_bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_SOURCE_ID_DFS ; 
 int /*<<< orphan*/  DM_PP_CLOCKS_STATE_NOMINAL ; 
 struct dce_dccg* TO_DCE_CLOCKS (struct dccg*) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  stub1 (struct dc_bios*,struct bp_pixel_clock_parameters*) ; 

__attribute__((used)) static int dce_set_clock(
	struct dccg *clk,
	int requested_clk_khz)
{
	struct dce_dccg *clk_dce = TO_DCE_CLOCKS(clk);
	struct bp_pixel_clock_parameters pxl_clk_params = { 0 };
	struct dc_bios *bp = clk->ctx->dc_bios;
	int actual_clock = requested_clk_khz;

	/* Make sure requested clock isn't lower than minimum threshold*/
	if (requested_clk_khz > 0)
		requested_clk_khz = max(requested_clk_khz,
				clk_dce->dentist_vco_freq_khz / 64);

	/* Prepare to program display clock*/
	pxl_clk_params.target_pixel_clock = requested_clk_khz;
	pxl_clk_params.pll_id = CLOCK_SOURCE_ID_DFS;

	bp->funcs->program_display_engine_pll(bp, &pxl_clk_params);

	if (clk_dce->dfs_bypass_enabled) {

		/* Cache the fixed display clock*/
		clk_dce->dfs_bypass_disp_clk =
			pxl_clk_params.dfs_bypass_display_clock;
		actual_clock = pxl_clk_params.dfs_bypass_display_clock;
	}

	/* from power down, we need mark the clock state as ClocksStateNominal
	 * from HWReset, so when resume we will call pplib voltage regulator.*/
	if (requested_clk_khz == 0)
		clk->cur_min_clks_state = DM_PP_CLOCKS_STATE_NOMINAL;
	return actual_clock;
}