#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct dc_clocks {scalar_t__ dppclk_khz; scalar_t__ dispclk_khz; } ;
struct TYPE_7__ {struct dc_clocks clk; } ;
struct TYPE_8__ {TYPE_1__ dcn; } ;
struct TYPE_9__ {TYPE_2__ bw; } ;
struct dc_state {TYPE_3__ bw_ctx; } ;
struct dc_clock_config {scalar_t__ max_clock_khz; scalar_t__ min_clock_khz; scalar_t__ bw_requirequired_clock_khz; int /*<<< orphan*/  member_0; } ;
struct dc {TYPE_5__* clk_mgr; struct dc_state* current_state; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
typedef  enum dc_clock_type { ____Placeholder_dc_clock_type } dc_clock_type ;
struct TYPE_11__ {TYPE_4__* funcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* update_clocks ) (TYPE_5__*,struct dc_state*,int) ;int /*<<< orphan*/  (* get_clock ) (TYPE_5__*,struct dc_state*,int,struct dc_clock_config*) ;} ;

/* Variables and functions */
 int DC_CLOCK_TYPE_DISPCLK ; 
 int DC_CLOCK_TYPE_DPPCLK ; 
 int DC_ERROR_UNEXPECTED ; 
 int DC_FAIL_CLK_BELOW_CFG_REQUIRED ; 
 int DC_FAIL_CLK_BELOW_MIN ; 
 int DC_FAIL_CLK_EXCEED_MAX ; 
 int DC_FAIL_UNSUPPORTED_1 ; 
 int DC_OK ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,struct dc_state*,int,struct dc_clock_config*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,struct dc_state*,int) ; 

__attribute__((used)) static enum dc_status dcn10_set_clock(struct dc *dc,
			enum dc_clock_type clock_type,
			uint32_t clk_khz,
			uint32_t stepping)
{
	struct dc_state *context = dc->current_state;
	struct dc_clock_config clock_cfg = {0};
	struct dc_clocks *current_clocks = &context->bw_ctx.bw.dcn.clk;

	if (dc->clk_mgr && dc->clk_mgr->funcs->get_clock)
				dc->clk_mgr->funcs->get_clock(dc->clk_mgr,
						context, clock_type, &clock_cfg);

	if (!dc->clk_mgr->funcs->get_clock)
		return DC_FAIL_UNSUPPORTED_1;

	if (clk_khz > clock_cfg.max_clock_khz)
		return DC_FAIL_CLK_EXCEED_MAX;

	if (clk_khz < clock_cfg.min_clock_khz)
		return DC_FAIL_CLK_BELOW_MIN;

	if (clk_khz < clock_cfg.bw_requirequired_clock_khz)
		return DC_FAIL_CLK_BELOW_CFG_REQUIRED;

	/*update internal request clock for update clock use*/
	if (clock_type == DC_CLOCK_TYPE_DISPCLK)
		current_clocks->dispclk_khz = clk_khz;
	else if (clock_type == DC_CLOCK_TYPE_DPPCLK)
		current_clocks->dppclk_khz = clk_khz;
	else
		return DC_ERROR_UNEXPECTED;

	if (dc->clk_mgr && dc->clk_mgr->funcs->update_clocks)
				dc->clk_mgr->funcs->update_clocks(dc->clk_mgr,
				context, true);
	return DC_OK;

}