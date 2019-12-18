#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_9__* dpp; } ;
struct pipe_ctx {TYPE_5__ plane_res; int /*<<< orphan*/  plane_state; } ;
struct dc_clocks {int dispclk_khz; int dppclk_khz; int /*<<< orphan*/  max_supported_dppclk_khz; } ;
struct dc {TYPE_3__* current_state; TYPE_1__* res_pool; } ;
struct TYPE_16__ {int dispclk_khz; int dppclk_khz; int /*<<< orphan*/  max_supported_dppclk_khz; } ;
struct TYPE_17__ {TYPE_7__ clks; } ;
struct clk_mgr_internal {TYPE_8__ base; TYPE_6__* funcs; } ;
struct TYPE_18__ {TYPE_4__* funcs; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* set_dprefclk ) (struct clk_mgr_internal*) ;int /*<<< orphan*/  (* set_dispclk ) (struct clk_mgr_internal*,int) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* dpp_dppclk_control ) (TYPE_9__*,int,int) ;} ;
struct TYPE_11__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_12__ {TYPE_2__ res_ctx; } ;
struct TYPE_10__ {int pipe_count; } ;

/* Variables and functions */
 int rv1_determine_dppclk_threshold (struct clk_mgr_internal*,struct dc_clocks*) ; 
 int /*<<< orphan*/  stub1 (struct clk_mgr_internal*,int) ; 
 int /*<<< orphan*/  stub2 (struct clk_mgr_internal*) ; 
 int /*<<< orphan*/  stub3 (TYPE_9__*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct clk_mgr_internal*,int) ; 
 int /*<<< orphan*/  stub5 (struct clk_mgr_internal*) ; 

__attribute__((used)) static void ramp_up_dispclk_with_dpp(struct clk_mgr_internal *clk_mgr, struct dc *dc, struct dc_clocks *new_clocks)
{
	int i;
	int dispclk_to_dpp_threshold = rv1_determine_dppclk_threshold(clk_mgr, new_clocks);
	bool request_dpp_div = new_clocks->dispclk_khz > new_clocks->dppclk_khz;

	/* set disp clk to dpp clk threshold */

	clk_mgr->funcs->set_dispclk(clk_mgr, dispclk_to_dpp_threshold);
	clk_mgr->funcs->set_dprefclk(clk_mgr);


	/* update request dpp clk division option */
	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx = &dc->current_state->res_ctx.pipe_ctx[i];

		if (!pipe_ctx->plane_state)
			continue;

		pipe_ctx->plane_res.dpp->funcs->dpp_dppclk_control(
				pipe_ctx->plane_res.dpp,
				request_dpp_div,
				true);
	}

	/* If target clk not same as dppclk threshold, set to target clock */
	if (dispclk_to_dpp_threshold != new_clocks->dispclk_khz) {
		clk_mgr->funcs->set_dispclk(clk_mgr, new_clocks->dispclk_khz);
		clk_mgr->funcs->set_dprefclk(clk_mgr);
	}


	clk_mgr->base.clks.dispclk_khz = new_clocks->dispclk_khz;
	clk_mgr->base.clks.dppclk_khz = new_clocks->dppclk_khz;
	clk_mgr->base.clks.max_supported_dppclk_khz = new_clocks->max_supported_dppclk_khz;
}