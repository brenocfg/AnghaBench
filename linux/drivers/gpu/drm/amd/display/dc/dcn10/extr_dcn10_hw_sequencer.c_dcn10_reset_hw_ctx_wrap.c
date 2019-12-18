#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pipe_ctx {struct clock_source* clock_source; int /*<<< orphan*/  stream; scalar_t__ top_pipe; } ;
struct TYPE_9__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_3__ res_ctx; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* enable_stream_gating ) (struct dc*,struct pipe_ctx*) ;} ;
struct dc {TYPE_4__ hwss; TYPE_6__* current_state; TYPE_1__* res_pool; } ;
struct clock_source {TYPE_5__* funcs; } ;
struct TYPE_8__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_12__ {TYPE_2__ res_ctx; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* cs_power_down ) (struct clock_source*) ;} ;
struct TYPE_7__ {int pipe_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcn10_reset_back_end_for_pipe (struct dc*,struct pipe_ctx*,TYPE_6__*) ; 
 scalar_t__ pipe_need_reprogram (struct pipe_ctx*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub1 (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub2 (struct clock_source*) ; 

__attribute__((used)) static void dcn10_reset_hw_ctx_wrap(
		struct dc *dc,
		struct dc_state *context)
{
	int i;

	/* Reset Back End*/
	for (i = dc->res_pool->pipe_count - 1; i >= 0 ; i--) {
		struct pipe_ctx *pipe_ctx_old =
			&dc->current_state->res_ctx.pipe_ctx[i];
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		if (!pipe_ctx_old->stream)
			continue;

		if (pipe_ctx_old->top_pipe)
			continue;

		if (!pipe_ctx->stream ||
				pipe_need_reprogram(pipe_ctx_old, pipe_ctx)) {
			struct clock_source *old_clk = pipe_ctx_old->clock_source;

			dcn10_reset_back_end_for_pipe(dc, pipe_ctx_old, dc->current_state);
			if (dc->hwss.enable_stream_gating)
				dc->hwss.enable_stream_gating(dc, pipe_ctx);
			if (old_clk)
				old_clk->funcs->cs_power_down(old_clk);
		}
	}
}