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
		const struct resource_pool *pool)
{
	int i;
	struct pipe_ctx *secondary_pipe = NULL;

	/*
	 * search backwards for the second pipe to keep pipe
	 * assignment more consistent
	 */

	for (i = pool->pipe_count - 1; i >= 0; i--) {
		if (res_ctx->pipe_ctx[i].stream == NULL) {
			secondary_pipe = &res_ctx->pipe_ctx[i];
			secondary_pipe->pipe_idx = i;
			break;
		}
	}


	return secondary_pipe;
}