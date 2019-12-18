#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct resource_pool {int pipe_count; } ;
struct resource_context {struct pipe_ctx* pipe_ctx; } ;
struct pipe_ctx {int pipe_idx; int /*<<< orphan*/ * stream; } ;

/* Variables and functions */

struct pipe_ctx *find_idle_secondary_pipe(
		struct resource_context *res_ctx,
		const struct resource_pool *pool,
		const struct pipe_ctx *primary_pipe)
{
	int i;
	struct pipe_ctx *secondary_pipe = NULL;

	/*
	 * We add a preferred pipe mapping to avoid the chance that
	 * MPCCs already in use will need to be reassigned to other trees.
	 * For example, if we went with the strict, assign backwards logic:
	 *
	 * (State 1)
	 * Display A on, no surface, top pipe = 0
	 * Display B on, no surface, top pipe = 1
	 *
	 * (State 2)
	 * Display A on, no surface, top pipe = 0
	 * Display B on, surface enable, top pipe = 1, bottom pipe = 5
	 *
	 * (State 3)
	 * Display A on, surface enable, top pipe = 0, bottom pipe = 5
	 * Display B on, surface enable, top pipe = 1, bottom pipe = 4
	 *
	 * The state 2->3 transition requires remapping MPCC 5 from display B
	 * to display A.
	 *
	 * However, with the preferred pipe logic, state 2 would look like:
	 *
	 * (State 2)
	 * Display A on, no surface, top pipe = 0
	 * Display B on, surface enable, top pipe = 1, bottom pipe = 4
	 *
	 * This would then cause 2->3 to not require remapping any MPCCs.
	 */
	if (primary_pipe) {
		int preferred_pipe_idx = (pool->pipe_count - 1) - primary_pipe->pipe_idx;
		if (res_ctx->pipe_ctx[preferred_pipe_idx].stream == NULL) {
			secondary_pipe = &res_ctx->pipe_ctx[preferred_pipe_idx];
			secondary_pipe->pipe_idx = preferred_pipe_idx;
		}
	}

	/*
	 * search backwards for the second pipe to keep pipe
	 * assignment more consistent
	 */
	if (!secondary_pipe)
		for (i = pool->pipe_count - 1; i >= 0; i--) {
			if (res_ctx->pipe_ctx[i].stream == NULL) {
				secondary_pipe = &res_ctx->pipe_ctx[i];
				secondary_pipe->pipe_idx = i;
				break;
			}
		}

	return secondary_pipe;
}