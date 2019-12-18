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
struct dc_clocks {int dispclk_khz; int dppclk_khz; int max_supported_dppclk_khz; } ;
struct TYPE_3__ {int dispclk_khz; int dppclk_khz; } ;
struct TYPE_4__ {TYPE_1__ clks; } ;
struct clk_mgr_internal {TYPE_2__ base; } ;

/* Variables and functions */

__attribute__((used)) static int rv1_determine_dppclk_threshold(struct clk_mgr_internal *clk_mgr, struct dc_clocks *new_clocks)
{
	bool request_dpp_div = new_clocks->dispclk_khz > new_clocks->dppclk_khz;
	bool dispclk_increase = new_clocks->dispclk_khz > clk_mgr->base.clks.dispclk_khz;
	int disp_clk_threshold = new_clocks->max_supported_dppclk_khz;
	bool cur_dpp_div = clk_mgr->base.clks.dispclk_khz > clk_mgr->base.clks.dppclk_khz;

	/* increase clock, looking for div is 0 for current, request div is 1*/
	if (dispclk_increase) {
		/* already divided by 2, no need to reach target clk with 2 steps*/
		if (cur_dpp_div)
			return new_clocks->dispclk_khz;

		/* request disp clk is lower than maximum supported dpp clk,
		 * no need to reach target clk with two steps.
		 */
		if (new_clocks->dispclk_khz <= disp_clk_threshold)
			return new_clocks->dispclk_khz;

		/* target dpp clk not request divided by 2, still within threshold */
		if (!request_dpp_div)
			return new_clocks->dispclk_khz;

	} else {
		/* decrease clock, looking for current dppclk divided by 2,
		 * request dppclk not divided by 2.
		 */

		/* current dpp clk not divided by 2, no need to ramp*/
		if (!cur_dpp_div)
			return new_clocks->dispclk_khz;

		/* current disp clk is lower than current maximum dpp clk,
		 * no need to ramp
		 */
		if (clk_mgr->base.clks.dispclk_khz <= disp_clk_threshold)
			return new_clocks->dispclk_khz;

		/* request dpp clk need to be divided by 2 */
		if (request_dpp_div)
			return new_clocks->dispclk_khz;
	}

	return disp_clk_threshold;
}