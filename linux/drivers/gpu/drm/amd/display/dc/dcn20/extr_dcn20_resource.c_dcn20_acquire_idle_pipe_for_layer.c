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
struct resource_pool {TYPE_3__** dpps; int /*<<< orphan*/ * ipps; int /*<<< orphan*/ * hubps; } ;
struct resource_context {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mpcc_inst; TYPE_3__* dpp; int /*<<< orphan*/  ipp; int /*<<< orphan*/  hubp; } ;
struct TYPE_4__ {int /*<<< orphan*/  opp; int /*<<< orphan*/  tg; } ;
struct pipe_ctx {size_t pipe_idx; TYPE_2__ plane_res; TYPE_1__ stream_res; int /*<<< orphan*/  stream; } ;
struct dc_stream_state {int dummy; } ;
struct dc_state {struct resource_context res_ctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 struct pipe_ctx* find_idle_secondary_pipe (struct resource_context*,struct resource_pool const*,struct pipe_ctx*) ; 
 struct pipe_ctx* resource_get_head_pipe_for_stream (struct resource_context*,struct dc_stream_state*) ; 

struct pipe_ctx *dcn20_acquire_idle_pipe_for_layer(
		struct dc_state *state,
		const struct resource_pool *pool,
		struct dc_stream_state *stream)
{
	struct resource_context *res_ctx = &state->res_ctx;
	struct pipe_ctx *head_pipe = resource_get_head_pipe_for_stream(res_ctx, stream);
	struct pipe_ctx *idle_pipe = find_idle_secondary_pipe(res_ctx, pool, head_pipe);

	if (!head_pipe)
		ASSERT(0);

	if (!idle_pipe)
		return NULL;

	idle_pipe->stream = head_pipe->stream;
	idle_pipe->stream_res.tg = head_pipe->stream_res.tg;
	idle_pipe->stream_res.opp = head_pipe->stream_res.opp;

	idle_pipe->plane_res.hubp = pool->hubps[idle_pipe->pipe_idx];
	idle_pipe->plane_res.ipp = pool->ipps[idle_pipe->pipe_idx];
	idle_pipe->plane_res.dpp = pool->dpps[idle_pipe->pipe_idx];
	idle_pipe->plane_res.mpcc_inst = pool->dpps[idle_pipe->pipe_idx]->inst;

	return idle_pipe;
}