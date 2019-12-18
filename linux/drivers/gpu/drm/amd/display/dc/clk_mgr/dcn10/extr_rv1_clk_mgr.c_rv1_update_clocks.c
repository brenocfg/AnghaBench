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
struct pp_smu_funcs_rv {int /*<<< orphan*/  pp_smu; int /*<<< orphan*/  (* set_min_deep_sleep_dcfclk ) (int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* set_hard_min_dcfclk_by_freq ) (int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* set_hard_min_fclk_by_freq ) (int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* set_display_count ) (int /*<<< orphan*/ *,int) ;} ;
struct dc_clocks {scalar_t__ dispclk_khz; scalar_t__ phyclk_khz; scalar_t__ fclk_khz; int dcfclk_khz; int dcfclk_deep_sleep_khz; } ;
struct TYPE_8__ {struct dc_clocks clk; } ;
struct TYPE_9__ {TYPE_2__ dcn; } ;
struct TYPE_10__ {TYPE_3__ bw; } ;
struct dc_state {TYPE_4__ bw_ctx; } ;
struct dc_debug_options {scalar_t__ force_fclk_khz; } ;
struct dc {struct dc_debug_options debug; } ;
struct clk_mgr_internal {TYPE_6__* pp_smu; } ;
struct TYPE_11__ {scalar_t__ dispclk_khz; scalar_t__ phyclk_khz; scalar_t__ fclk_khz; int dcfclk_khz; int dcfclk_deep_sleep_khz; } ;
struct clk_mgr {TYPE_5__ clks; TYPE_1__* ctx; } ;
struct TYPE_12__ {struct pp_smu_funcs_rv rv_funcs; } ;
struct TYPE_7__ {struct dc* dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_6__*) ; 
 struct clk_mgr_internal* TO_CLK_MGR_INTERNAL (struct clk_mgr*) ; 
 int clk_mgr_helper_get_active_display_cnt (struct dc*,struct dc_state*) ; 
 int /*<<< orphan*/  ramp_up_dispclk_with_dpp (struct clk_mgr_internal*,struct dc*,struct dc_clocks*) ; 
 scalar_t__ should_set_clock (int,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void rv1_update_clocks(struct clk_mgr *clk_mgr_base,
			struct dc_state *context,
			bool safe_to_lower)
{
	struct clk_mgr_internal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	struct dc *dc = clk_mgr_base->ctx->dc;
	struct dc_debug_options *debug = &dc->debug;
	struct dc_clocks *new_clocks = &context->bw_ctx.bw.dcn.clk;
	struct pp_smu_funcs_rv *pp_smu = NULL;
	bool send_request_to_increase = false;
	bool send_request_to_lower = false;
	int display_count;

	bool enter_display_off = false;

	ASSERT(clk_mgr->pp_smu);

	pp_smu = &clk_mgr->pp_smu->rv_funcs;

	display_count = clk_mgr_helper_get_active_display_cnt(dc, context);

	if (display_count == 0)
		enter_display_off = true;

	if (enter_display_off == safe_to_lower) {
		/*
		 * Notify SMU active displays
		 * if function pointer not set up, this message is
		 * sent as part of pplib_apply_display_requirements.
		 */
		if (pp_smu->set_display_count)
			pp_smu->set_display_count(&pp_smu->pp_smu, display_count);
	}

	if (new_clocks->dispclk_khz > clk_mgr_base->clks.dispclk_khz
			|| new_clocks->phyclk_khz > clk_mgr_base->clks.phyclk_khz
			|| new_clocks->fclk_khz > clk_mgr_base->clks.fclk_khz
			|| new_clocks->dcfclk_khz > clk_mgr_base->clks.dcfclk_khz)
		send_request_to_increase = true;

	if (should_set_clock(safe_to_lower, new_clocks->phyclk_khz, clk_mgr_base->clks.phyclk_khz)) {
		clk_mgr_base->clks.phyclk_khz = new_clocks->phyclk_khz;
		send_request_to_lower = true;
	}

	// F Clock
	if (debug->force_fclk_khz != 0)
		new_clocks->fclk_khz = debug->force_fclk_khz;

	if (should_set_clock(safe_to_lower, new_clocks->fclk_khz, clk_mgr_base->clks.fclk_khz)) {
		clk_mgr_base->clks.fclk_khz = new_clocks->fclk_khz;
		send_request_to_lower = true;
	}

	//DCF Clock
	if (should_set_clock(safe_to_lower, new_clocks->dcfclk_khz, clk_mgr_base->clks.dcfclk_khz)) {
		clk_mgr_base->clks.dcfclk_khz = new_clocks->dcfclk_khz;
		send_request_to_lower = true;
	}

	if (should_set_clock(safe_to_lower,
			new_clocks->dcfclk_deep_sleep_khz, clk_mgr_base->clks.dcfclk_deep_sleep_khz)) {
		clk_mgr_base->clks.dcfclk_deep_sleep_khz = new_clocks->dcfclk_deep_sleep_khz;
		send_request_to_lower = true;
	}

	/* make sure dcf clk is before dpp clk to
	 * make sure we have enough voltage to run dpp clk
	 */
	if (send_request_to_increase) {
		/*use dcfclk to request voltage*/
		if (pp_smu->set_hard_min_fclk_by_freq &&
				pp_smu->set_hard_min_dcfclk_by_freq &&
				pp_smu->set_min_deep_sleep_dcfclk) {
			pp_smu->set_hard_min_fclk_by_freq(&pp_smu->pp_smu, new_clocks->fclk_khz / 1000);
			pp_smu->set_hard_min_dcfclk_by_freq(&pp_smu->pp_smu, new_clocks->dcfclk_khz / 1000);
			pp_smu->set_min_deep_sleep_dcfclk(&pp_smu->pp_smu, (new_clocks->dcfclk_deep_sleep_khz + 999) / 1000);
		}
	}

	/* dcn1 dppclk is tied to dispclk */
	/* program dispclk on = as a w/a for sleep resume clock ramping issues */
	if (should_set_clock(safe_to_lower, new_clocks->dispclk_khz, clk_mgr_base->clks.dispclk_khz)
			|| new_clocks->dispclk_khz == clk_mgr_base->clks.dispclk_khz) {
		ramp_up_dispclk_with_dpp(clk_mgr, dc, new_clocks);
		clk_mgr_base->clks.dispclk_khz = new_clocks->dispclk_khz;
		send_request_to_lower = true;
	}

	if (!send_request_to_increase && send_request_to_lower) {
		/*use dcfclk to request voltage*/
		if (pp_smu->set_hard_min_fclk_by_freq &&
				pp_smu->set_hard_min_dcfclk_by_freq &&
				pp_smu->set_min_deep_sleep_dcfclk) {
			pp_smu->set_hard_min_fclk_by_freq(&pp_smu->pp_smu, new_clocks->fclk_khz / 1000);
			pp_smu->set_hard_min_dcfclk_by_freq(&pp_smu->pp_smu, new_clocks->dcfclk_khz / 1000);
			pp_smu->set_min_deep_sleep_dcfclk(&pp_smu->pp_smu, (new_clocks->dcfclk_deep_sleep_khz + 999) / 1000);
		}
	}
}