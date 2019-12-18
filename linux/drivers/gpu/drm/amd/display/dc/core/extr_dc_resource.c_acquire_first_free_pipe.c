#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource_pool {int pipe_count; TYPE_3__** dpps; int /*<<< orphan*/ * opps; int /*<<< orphan*/ * transforms; int /*<<< orphan*/ * ipps; int /*<<< orphan*/ * hubps; int /*<<< orphan*/ * mis; int /*<<< orphan*/ * timing_generators; } ;
struct resource_context {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  mpcc_inst; TYPE_3__* dpp; int /*<<< orphan*/  xfm; int /*<<< orphan*/  ipp; int /*<<< orphan*/  hubp; int /*<<< orphan*/  mi; } ;
struct TYPE_4__ {int /*<<< orphan*/  opp; int /*<<< orphan*/  tg; } ;
struct pipe_ctx {int pipe_idx; struct dc_stream_state* stream; TYPE_2__ plane_res; TYPE_1__ stream_res; } ;
struct dc_stream_state {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  inst; } ;

/* Variables and functions */

__attribute__((used)) static int acquire_first_free_pipe(
		struct resource_context *res_ctx,
		const struct resource_pool *pool,
		struct dc_stream_state *stream)
{
	int i;

	for (i = 0; i < pool->pipe_count; i++) {
		if (!res_ctx->pipe_ctx[i].stream) {
			struct pipe_ctx *pipe_ctx = &res_ctx->pipe_ctx[i];

			pipe_ctx->stream_res.tg = pool->timing_generators[i];
			pipe_ctx->plane_res.mi = pool->mis[i];
			pipe_ctx->plane_res.hubp = pool->hubps[i];
			pipe_ctx->plane_res.ipp = pool->ipps[i];
			pipe_ctx->plane_res.xfm = pool->transforms[i];
			pipe_ctx->plane_res.dpp = pool->dpps[i];
			pipe_ctx->stream_res.opp = pool->opps[i];
			if (pool->dpps[i])
				pipe_ctx->plane_res.mpcc_inst = pool->dpps[i]->inst;
			pipe_ctx->pipe_idx = i;


			pipe_ctx->stream = stream;
			return i;
		}
	}
	return -1;
}