#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dispclk_khz; } ;
struct TYPE_8__ {TYPE_2__ dce; } ;
struct dc_state {int /*<<< orphan*/  res_ctx; TYPE_3__ bw; } ;
struct dc_clocks {int /*<<< orphan*/  phyclk_khz; int /*<<< orphan*/  dispclk_khz; } ;
struct dc {TYPE_5__* res_pool; } ;
struct TYPE_10__ {TYPE_4__* dccg; } ;
struct TYPE_9__ {TYPE_1__* funcs; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* update_clocks ) (TYPE_4__*,struct dc_clocks*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dce110_set_displaymarks (struct dc*,struct dc_state*) ; 
 int /*<<< orphan*/  dce110_set_safe_displaymarks (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  get_max_pixel_clock_for_all_paths (struct dc*,struct dc_state*) ; 
 int /*<<< orphan*/  pplib_apply_display_requirements (struct dc*,struct dc_state*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,struct dc_clocks*,int) ; 

__attribute__((used)) static void dce110_set_bandwidth(
		struct dc *dc,
		struct dc_state *context,
		bool decrease_allowed)
{
	struct dc_clocks req_clks;

	req_clks.dispclk_khz = context->bw.dce.dispclk_khz;
	req_clks.phyclk_khz = get_max_pixel_clock_for_all_paths(dc, context);

	if (decrease_allowed)
		dce110_set_displaymarks(dc, context);
	else
		dce110_set_safe_displaymarks(&context->res_ctx, dc->res_pool);

	dc->res_pool->dccg->funcs->update_clocks(
			dc->res_pool->dccg,
			&req_clks,
			decrease_allowed);
	pplib_apply_display_requirements(dc, context);
}