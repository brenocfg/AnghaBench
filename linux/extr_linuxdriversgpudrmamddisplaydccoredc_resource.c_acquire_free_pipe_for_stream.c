#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource_pool {int pipe_count; TYPE_1__* funcs; } ;
struct resource_context {struct pipe_ctx* pipe_ctx; } ;
struct pipe_ctx {int /*<<< orphan*/  plane_state; struct dc_stream_state* stream; } ;
struct dc_stream_state {int dummy; } ;
struct dc_state {struct resource_context res_ctx; } ;
struct TYPE_2__ {struct pipe_ctx* (* acquire_idle_pipe_for_layer ) (struct dc_state*,struct resource_pool const*,struct dc_stream_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 struct pipe_ctx* resource_get_head_pipe_for_stream (struct resource_context*,struct dc_stream_state*) ; 
 struct pipe_ctx* stub1 (struct dc_state*,struct resource_pool const*,struct dc_stream_state*) ; 

__attribute__((used)) static struct pipe_ctx *acquire_free_pipe_for_stream(
		struct dc_state *context,
		const struct resource_pool *pool,
		struct dc_stream_state *stream)
{
	int i;
	struct resource_context *res_ctx = &context->res_ctx;

	struct pipe_ctx *head_pipe = NULL;

	/* Find head pipe, which has the back end set up*/

	head_pipe = resource_get_head_pipe_for_stream(res_ctx, stream);

	if (!head_pipe) {
		ASSERT(0);
		return NULL;
	}

	if (!head_pipe->plane_state)
		return head_pipe;

	/* Re-use pipe already acquired for this stream if available*/
	for (i = pool->pipe_count - 1; i >= 0; i--) {
		if (res_ctx->pipe_ctx[i].stream == stream &&
				!res_ctx->pipe_ctx[i].plane_state) {
			return &res_ctx->pipe_ctx[i];
		}
	}

	/*
	 * At this point we have no re-useable pipe for this stream and we need
	 * to acquire an idle one to satisfy the request
	 */

	if (!pool->funcs->acquire_idle_pipe_for_layer)
		return NULL;

	return pool->funcs->acquire_idle_pipe_for_layer(context, pool, stream);

}