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
struct dmcu {TYPE_6__* funcs; } ;
struct dc_bios {TYPE_4__* funcs; } ;
struct dc {TYPE_5__* ctx; TYPE_3__* res_pool; } ;
struct TYPE_8__ {TYPE_1__* ctx; } ;
struct clk_mgr_internal {int dentist_vco_freq_khz; int dfs_bypass_disp_clk; int /*<<< orphan*/  cur_min_clks_state; TYPE_2__ base; } ;
struct bp_set_dce_clock_parameters {int target_clock_frequency; int /*<<< orphan*/  clock_type; int /*<<< orphan*/  pll_id; } ;
typedef  int /*<<< orphan*/  dce_clk_params ;
struct TYPE_12__ {int /*<<< orphan*/  (* set_psr_wait_loop ) (struct dmcu*,int) ;scalar_t__ (* is_dmcu_initialized ) (struct dmcu*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  dce_environment; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* set_dce_clock ) (struct dc_bios*,struct bp_set_dce_clock_parameters*) ;} ;
struct TYPE_9__ {struct dmcu* dmcu; } ;
struct TYPE_7__ {struct dc* dc; struct dc_bios* dc_bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_SOURCE_ID_DFS ; 
 int /*<<< orphan*/  DCECLOCK_TYPE_DISPLAY_CLOCK ; 
 int /*<<< orphan*/  DM_PP_CLOCKS_STATE_NOMINAL ; 
 int /*<<< orphan*/  IS_FPGA_MAXIMUS_DC (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memset (struct bp_set_dce_clock_parameters*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dc_bios*,struct bp_set_dce_clock_parameters*) ; 
 scalar_t__ stub2 (struct dmcu*) ; 
 int /*<<< orphan*/  stub3 (struct dmcu*,int) ; 

int dce112_set_dispclk(struct clk_mgr_internal *clk_mgr, int requested_clk_khz)
{
	struct bp_set_dce_clock_parameters dce_clk_params;
	struct dc_bios *bp = clk_mgr->base.ctx->dc_bios;
	struct dc *core_dc = clk_mgr->base.ctx->dc;
	struct dmcu *dmcu = core_dc->res_pool->dmcu;
	int actual_clock = requested_clk_khz;
	/* Prepare to program display clock*/
	memset(&dce_clk_params, 0, sizeof(dce_clk_params));

	/* Make sure requested clock isn't lower than minimum threshold*/
	if (requested_clk_khz > 0)
		requested_clk_khz = max(requested_clk_khz,
				clk_mgr->dentist_vco_freq_khz / 62);

	dce_clk_params.target_clock_frequency = requested_clk_khz;
	dce_clk_params.pll_id = CLOCK_SOURCE_ID_DFS;
	dce_clk_params.clock_type = DCECLOCK_TYPE_DISPLAY_CLOCK;

	bp->funcs->set_dce_clock(bp, &dce_clk_params);
	actual_clock = dce_clk_params.target_clock_frequency;

	/*
	 * from power down, we need mark the clock state as ClocksStateNominal
	 * from HWReset, so when resume we will call pplib voltage regulator.
	 */
	if (requested_clk_khz == 0)
		clk_mgr->cur_min_clks_state = DM_PP_CLOCKS_STATE_NOMINAL;


	if (!IS_FPGA_MAXIMUS_DC(core_dc->ctx->dce_environment)) {
		if (dmcu && dmcu->funcs->is_dmcu_initialized(dmcu)) {
			if (clk_mgr->dfs_bypass_disp_clk != actual_clock)
				dmcu->funcs->set_psr_wait_loop(dmcu,
						actual_clock / 1000 / 7);
		}
	}

	clk_mgr->dfs_bypass_disp_clk = actual_clock;
	return actual_clock;

}