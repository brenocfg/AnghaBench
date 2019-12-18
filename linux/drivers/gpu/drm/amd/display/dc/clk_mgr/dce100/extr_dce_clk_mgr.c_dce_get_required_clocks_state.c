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
struct TYPE_6__ {scalar_t__ dispclk_khz; } ;
struct TYPE_7__ {TYPE_2__ dce; } ;
struct TYPE_8__ {TYPE_3__ bw; } ;
struct dc_state {TYPE_4__ bw_ctx; } ;
struct clk_mgr_internal {int max_clks_state; TYPE_1__* max_clks_by_state; } ;
struct clk_mgr {int dummy; } ;
typedef  enum dm_pp_clocks_state { ____Placeholder_dm_pp_clocks_state } dm_pp_clocks_state ;
struct TYPE_5__ {scalar_t__ display_clk_khz; int pixel_clk_khz; } ;

/* Variables and functions */
 int DM_PP_CLOCKS_STATE_INVALID ; 
 int DM_PP_CLOCKS_STATE_ULTRA_LOW ; 
 struct clk_mgr_internal* TO_CLK_MGR_INTERNAL (struct clk_mgr*) ; 
 int dce_get_max_pixel_clock_for_all_paths (struct dc_state*) ; 

enum dm_pp_clocks_state dce_get_required_clocks_state(
	struct clk_mgr *clk_mgr_base,
	struct dc_state *context)
{
	struct clk_mgr_internal *clk_mgr_dce = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	int i;
	enum dm_pp_clocks_state low_req_clk;
	int max_pix_clk = dce_get_max_pixel_clock_for_all_paths(context);

	/* Iterate from highest supported to lowest valid state, and update
	 * lowest RequiredState with the lowest state that satisfies
	 * all required clocks
	 */
	for (i = clk_mgr_dce->max_clks_state; i >= DM_PP_CLOCKS_STATE_ULTRA_LOW; i--)
		if (context->bw_ctx.bw.dce.dispclk_khz >
				clk_mgr_dce->max_clks_by_state[i].display_clk_khz
			|| max_pix_clk >
				clk_mgr_dce->max_clks_by_state[i].pixel_clk_khz)
			break;

	low_req_clk = i + 1;
	if (low_req_clk > clk_mgr_dce->max_clks_state) {
		/* set max clock state for high phyclock, invalid on exceeding display clock */
		if (clk_mgr_dce->max_clks_by_state[clk_mgr_dce->max_clks_state].display_clk_khz
				< context->bw_ctx.bw.dce.dispclk_khz)
			low_req_clk = DM_PP_CLOCKS_STATE_INVALID;
		else
			low_req_clk = clk_mgr_dce->max_clks_state;
	}

	return low_req_clk;
}