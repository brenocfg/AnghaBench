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
struct dm_pp_clock_for_voltage_req {int clocks_in_khz; int /*<<< orphan*/  clk_type; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int dispclk_khz; int phyclk_khz; } ;
struct dccg {int /*<<< orphan*/  ctx; TYPE_2__ clks; TYPE_1__* funcs; } ;
struct dc_clocks {int dispclk_khz; int phyclk_khz; } ;
struct TYPE_3__ {int (* set_dispclk ) (struct dccg*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DM_PP_CLOCK_TYPE_DISPLAYPHYCLK ; 
 int /*<<< orphan*/  DM_PP_CLOCK_TYPE_DISPLAY_CLK ; 
 int /*<<< orphan*/  dm_pp_apply_clock_for_voltage_request (int /*<<< orphan*/ ,struct dm_pp_clock_for_voltage_req*) ; 
 scalar_t__ should_set_clock (int,int,int) ; 
 int stub1 (struct dccg*,int) ; 

__attribute__((used)) static void dce12_update_clocks(struct dccg *dccg,
			struct dc_clocks *new_clocks,
			bool safe_to_lower)
{
	struct dm_pp_clock_for_voltage_req clock_voltage_req = {0};

	/* TODO: Investigate why this is needed to fix display corruption. */
	new_clocks->dispclk_khz = new_clocks->dispclk_khz * 115 / 100;

	if (should_set_clock(safe_to_lower, new_clocks->dispclk_khz, dccg->clks.dispclk_khz)) {
		clock_voltage_req.clk_type = DM_PP_CLOCK_TYPE_DISPLAY_CLK;
		clock_voltage_req.clocks_in_khz = new_clocks->dispclk_khz;
		new_clocks->dispclk_khz = dccg->funcs->set_dispclk(dccg, new_clocks->dispclk_khz);
		dccg->clks.dispclk_khz = new_clocks->dispclk_khz;

		dm_pp_apply_clock_for_voltage_request(dccg->ctx, &clock_voltage_req);
	}

	if (should_set_clock(safe_to_lower, new_clocks->phyclk_khz, dccg->clks.phyclk_khz)) {
		clock_voltage_req.clk_type = DM_PP_CLOCK_TYPE_DISPLAYPHYCLK;
		clock_voltage_req.clocks_in_khz = new_clocks->phyclk_khz;
		dccg->clks.phyclk_khz = new_clocks->phyclk_khz;

		dm_pp_apply_clock_for_voltage_request(dccg->ctx, &clock_voltage_req);
	}
}