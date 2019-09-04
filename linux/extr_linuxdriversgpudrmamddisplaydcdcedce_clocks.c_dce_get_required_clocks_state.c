#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dce_dccg {TYPE_1__* max_clks_by_state; } ;
struct dccg {int max_clks_state; } ;
struct dc_clocks {scalar_t__ dispclk_khz; scalar_t__ phyclk_khz; } ;
typedef  enum dm_pp_clocks_state { ____Placeholder_dm_pp_clocks_state } dm_pp_clocks_state ;
struct TYPE_2__ {scalar_t__ display_clk_khz; scalar_t__ pixel_clk_khz; } ;

/* Variables and functions */
 int DM_PP_CLOCKS_STATE_INVALID ; 
 int DM_PP_CLOCKS_STATE_ULTRA_LOW ; 
 struct dce_dccg* TO_DCE_CLOCKS (struct dccg*) ; 

__attribute__((used)) static enum dm_pp_clocks_state dce_get_required_clocks_state(
	struct dccg *clk,
	struct dc_clocks *req_clocks)
{
	struct dce_dccg *clk_dce = TO_DCE_CLOCKS(clk);
	int i;
	enum dm_pp_clocks_state low_req_clk;

	/* Iterate from highest supported to lowest valid state, and update
	 * lowest RequiredState with the lowest state that satisfies
	 * all required clocks
	 */
	for (i = clk->max_clks_state; i >= DM_PP_CLOCKS_STATE_ULTRA_LOW; i--)
		if (req_clocks->dispclk_khz >
				clk_dce->max_clks_by_state[i].display_clk_khz
			|| req_clocks->phyclk_khz >
				clk_dce->max_clks_by_state[i].pixel_clk_khz)
			break;

	low_req_clk = i + 1;
	if (low_req_clk > clk->max_clks_state) {
		/* set max clock state for high phyclock, invalid on exceeding display clock */
		if (clk_dce->max_clks_by_state[clk->max_clks_state].display_clk_khz
				< req_clocks->dispclk_khz)
			low_req_clk = DM_PP_CLOCKS_STATE_INVALID;
		else
			low_req_clk = clk->max_clks_state;
	}

	return low_req_clk;
}