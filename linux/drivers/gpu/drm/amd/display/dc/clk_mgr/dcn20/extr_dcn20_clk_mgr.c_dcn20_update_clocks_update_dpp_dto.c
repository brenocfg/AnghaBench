#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_8__* pipe_ctx; } ;
struct dc_state {TYPE_9__ res_ctx; } ;
struct TYPE_17__ {TYPE_3__* ctx; } ;
struct clk_mgr_internal {TYPE_11__* dccg; TYPE_4__ base; } ;
struct TYPE_19__ {int dppclk_khz; } ;
struct TYPE_20__ {TYPE_6__ bw; TYPE_5__* dpp; } ;
struct TYPE_21__ {TYPE_7__ plane_res; int /*<<< orphan*/  plane_state; } ;
struct TYPE_18__ {int inst; } ;
struct TYPE_16__ {TYPE_2__* dc; } ;
struct TYPE_15__ {TYPE_1__* res_pool; } ;
struct TYPE_14__ {int pipe_count; } ;
struct TYPE_13__ {TYPE_10__* funcs; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* update_dpp_dto ) (TYPE_11__*,int,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_11__*,int,int,int) ; 

void dcn20_update_clocks_update_dpp_dto(struct clk_mgr_internal *clk_mgr,
		struct dc_state *context)
{
	int i;

	for (i = 0; i < clk_mgr->base.ctx->dc->res_pool->pipe_count; i++) {
		int dpp_inst, dppclk_khz;

		if (!context->res_ctx.pipe_ctx[i].plane_state)
			continue;

		dpp_inst = context->res_ctx.pipe_ctx[i].plane_res.dpp->inst;
		dppclk_khz = context->res_ctx.pipe_ctx[i].plane_res.bw.dppclk_khz;
		clk_mgr->dccg->funcs->update_dpp_dto(
				clk_mgr->dccg, dpp_inst, dppclk_khz, false);
	}
}