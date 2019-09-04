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
struct pipe_ctx {int /*<<< orphan*/  top_pipe; struct dc_stream_state const* stream; int /*<<< orphan*/  plane_state; } ;
struct dc_stream_state {int dummy; } ;
struct TYPE_5__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_1__ res_ctx; } ;
struct dc {TYPE_3__* current_state; TYPE_4__* res_pool; } ;
struct TYPE_8__ {int pipe_count; } ;
struct TYPE_6__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_7__ {TYPE_2__ res_ctx; } ;

/* Variables and functions */

__attribute__((used)) static struct pipe_ctx *find_top_pipe_for_stream(
		struct dc *dc,
		struct dc_state *context,
		const struct dc_stream_state *stream)
{
	int i;

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];
		struct pipe_ctx *old_pipe_ctx =
				&dc->current_state->res_ctx.pipe_ctx[i];

		if (!pipe_ctx->plane_state && !old_pipe_ctx->plane_state)
			continue;

		if (pipe_ctx->stream != stream)
			continue;

		if (!pipe_ctx->top_pipe)
			return pipe_ctx;
	}
	return NULL;
}