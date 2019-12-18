#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dc_clocks {int fclk_khz; int phyclk_khz; int dcfclk_khz; int dcfclk_deep_sleep_khz; int socclk_khz; int dramclk_khz; int dppclk_khz; int dispclk_khz; } ;
struct TYPE_5__ {struct dc_clocks clk; } ;
struct TYPE_6__ {TYPE_1__ dcn; } ;
struct TYPE_7__ {TYPE_2__ bw; } ;
struct dc_state {TYPE_3__ bw_ctx; } ;
struct TYPE_8__ {int phyclk_khz; int dcfclk_khz; int dcfclk_deep_sleep_khz; int socclk_khz; int dramclk_khz; int dppclk_khz; int fclk_khz; int dispclk_khz; } ;
struct clk_mgr {TYPE_4__ clks; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_set_dcn_clocks (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ should_set_clock (int,int,int) ; 

void dcn2_update_clocks_fpga(struct clk_mgr *clk_mgr,
		struct dc_state *context,
		bool safe_to_lower)
{
	struct dc_clocks *new_clocks = &context->bw_ctx.bw.dcn.clk;
	/* Min fclk = 1.2GHz since all the extra scemi logic seems to run off of it */
	int fclk_adj = new_clocks->fclk_khz > 1200000 ? new_clocks->fclk_khz : 1200000;

	if (should_set_clock(safe_to_lower, new_clocks->phyclk_khz, clk_mgr->clks.phyclk_khz)) {
		clk_mgr->clks.phyclk_khz = new_clocks->phyclk_khz;
	}

	if (should_set_clock(safe_to_lower, new_clocks->dcfclk_khz, clk_mgr->clks.dcfclk_khz)) {
		clk_mgr->clks.dcfclk_khz = new_clocks->dcfclk_khz;
	}

	if (should_set_clock(safe_to_lower,
			new_clocks->dcfclk_deep_sleep_khz, clk_mgr->clks.dcfclk_deep_sleep_khz)) {
		clk_mgr->clks.dcfclk_deep_sleep_khz = new_clocks->dcfclk_deep_sleep_khz;
	}

	if (should_set_clock(safe_to_lower, new_clocks->socclk_khz, clk_mgr->clks.socclk_khz)) {
		clk_mgr->clks.socclk_khz = new_clocks->socclk_khz;
	}

	if (should_set_clock(safe_to_lower, new_clocks->dramclk_khz, clk_mgr->clks.dramclk_khz)) {
		clk_mgr->clks.dramclk_khz = new_clocks->dramclk_khz;
	}

	if (should_set_clock(safe_to_lower, new_clocks->dppclk_khz, clk_mgr->clks.dppclk_khz)) {
		clk_mgr->clks.dppclk_khz = new_clocks->dppclk_khz;
	}

	if (should_set_clock(safe_to_lower, fclk_adj, clk_mgr->clks.fclk_khz)) {
		clk_mgr->clks.fclk_khz = fclk_adj;
	}

	if (should_set_clock(safe_to_lower, new_clocks->dispclk_khz, clk_mgr->clks.dispclk_khz)) {
		clk_mgr->clks.dispclk_khz = new_clocks->dispclk_khz;
	}

	/* Both fclk and dppclk ref are run on the same scemi clock so we
	 * need to keep the same value for both
	 */
	if (clk_mgr->clks.fclk_khz > clk_mgr->clks.dppclk_khz)
		clk_mgr->clks.dppclk_khz = clk_mgr->clks.fclk_khz;
	if (clk_mgr->clks.dppclk_khz > clk_mgr->clks.fclk_khz)
		clk_mgr->clks.fclk_khz = clk_mgr->clks.dppclk_khz;

	dm_set_dcn_clocks(clk_mgr->ctx, &clk_mgr->clks);
}