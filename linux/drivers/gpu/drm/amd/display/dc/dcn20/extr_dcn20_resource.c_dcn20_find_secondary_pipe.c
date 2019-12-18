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
struct resource_pool {int dummy; } ;
struct resource_context {struct pipe_ctx* pipe_ctx; } ;
struct pipe_ctx {size_t pipe_idx; int /*<<< orphan*/ * stream; } ;
struct dc {TYPE_6__* res_pool; TYPE_5__* current_state; } ;
struct TYPE_12__ {int pipe_count; } ;
struct TYPE_10__ {TYPE_3__* pipe_ctx; } ;
struct TYPE_11__ {TYPE_4__ res_ctx; } ;
struct TYPE_9__ {int /*<<< orphan*/ * top_pipe; TYPE_2__* next_odm_pipe; TYPE_1__* bottom_pipe; } ;
struct TYPE_8__ {int pipe_idx; } ;
struct TYPE_7__ {int pipe_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct pipe_ctx*) ; 

__attribute__((used)) static struct pipe_ctx *dcn20_find_secondary_pipe(struct dc *dc,
		struct resource_context *res_ctx,
		const struct resource_pool *pool,
		const struct pipe_ctx *primary_pipe)
{
	struct pipe_ctx *secondary_pipe = NULL;

	if (dc && primary_pipe) {
		int j;
		int preferred_pipe_idx = 0;

		/* first check the prev dc state:
		 * if this primary pipe has a bottom pipe in prev. state
		 * and if the bottom pipe is still available (which it should be),
		 * pick that pipe as secondary
		 * Same logic applies for ODM pipes. Since mpo is not allowed with odm
		 * check in else case.
		 */
		if (dc->current_state->res_ctx.pipe_ctx[primary_pipe->pipe_idx].bottom_pipe) {
			preferred_pipe_idx = dc->current_state->res_ctx.pipe_ctx[primary_pipe->pipe_idx].bottom_pipe->pipe_idx;
			if (res_ctx->pipe_ctx[preferred_pipe_idx].stream == NULL) {
				secondary_pipe = &res_ctx->pipe_ctx[preferred_pipe_idx];
				secondary_pipe->pipe_idx = preferred_pipe_idx;
			}
		} else if (dc->current_state->res_ctx.pipe_ctx[primary_pipe->pipe_idx].next_odm_pipe) {
			preferred_pipe_idx = dc->current_state->res_ctx.pipe_ctx[primary_pipe->pipe_idx].next_odm_pipe->pipe_idx;
			if (res_ctx->pipe_ctx[preferred_pipe_idx].stream == NULL) {
				secondary_pipe = &res_ctx->pipe_ctx[preferred_pipe_idx];
				secondary_pipe->pipe_idx = preferred_pipe_idx;
			}
		}

		/*
		 * if this primary pipe does not have a bottom pipe in prev. state
		 * start backward and find a pipe that did not used to be a bottom pipe in
		 * prev. dc state. This way we make sure we keep the same assignment as
		 * last state and will not have to reprogram every pipe
		 */
		if (secondary_pipe == NULL) {
			for (j = dc->res_pool->pipe_count - 1; j >= 0; j--) {
				if (dc->current_state->res_ctx.pipe_ctx[j].top_pipe == NULL) {
					preferred_pipe_idx = j;

					if (res_ctx->pipe_ctx[preferred_pipe_idx].stream == NULL) {
						secondary_pipe = &res_ctx->pipe_ctx[preferred_pipe_idx];
						secondary_pipe->pipe_idx = preferred_pipe_idx;
						break;
					}
				}
			}
		}
		/*
		 * We should never hit this assert unless assignments are shuffled around
		 * if this happens we will prob. hit a vsync tdr
		 */
		ASSERT(secondary_pipe);
		/*
		 * search backwards for the second pipe to keep pipe
		 * assignment more consistent
		 */
		if (secondary_pipe == NULL) {
			for (j = dc->res_pool->pipe_count - 1; j >= 0; j--) {
				preferred_pipe_idx = j;

				if (res_ctx->pipe_ctx[preferred_pipe_idx].stream == NULL) {
					secondary_pipe = &res_ctx->pipe_ctx[preferred_pipe_idx];
					secondary_pipe->pipe_idx = preferred_pipe_idx;
					break;
				}
			}
		}
	}

	return secondary_pipe;
}