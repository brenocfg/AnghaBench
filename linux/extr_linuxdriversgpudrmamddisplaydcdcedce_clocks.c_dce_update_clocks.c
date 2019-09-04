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
struct dm_pp_power_level_change_request {scalar_t__ power_level; } ;
struct TYPE_4__ {int /*<<< orphan*/  dispclk_khz; } ;
struct dccg {scalar_t__ cur_min_clks_state; TYPE_2__ clks; TYPE_1__* funcs; int /*<<< orphan*/  ctx; } ;
struct dc_clocks {int /*<<< orphan*/  dispclk_khz; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_dispclk ) (struct dccg*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ dce_get_required_clocks_state (struct dccg*,struct dc_clocks*) ; 
 scalar_t__ dm_pp_apply_power_level_change_request (int /*<<< orphan*/ ,struct dm_pp_power_level_change_request*) ; 
 scalar_t__ should_set_clock (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dccg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce_update_clocks(struct dccg *dccg,
			struct dc_clocks *new_clocks,
			bool safe_to_lower)
{
	struct dm_pp_power_level_change_request level_change_req;

	level_change_req.power_level = dce_get_required_clocks_state(dccg, new_clocks);
	/* get max clock state from PPLIB */
	if ((level_change_req.power_level < dccg->cur_min_clks_state && safe_to_lower)
			|| level_change_req.power_level > dccg->cur_min_clks_state) {
		if (dm_pp_apply_power_level_change_request(dccg->ctx, &level_change_req))
			dccg->cur_min_clks_state = level_change_req.power_level;
	}

	if (should_set_clock(safe_to_lower, new_clocks->dispclk_khz, dccg->clks.dispclk_khz)) {
		new_clocks->dispclk_khz = dccg->funcs->set_dispclk(dccg, new_clocks->dispclk_khz);
		dccg->clks.dispclk_khz = new_clocks->dispclk_khz;
	}
}