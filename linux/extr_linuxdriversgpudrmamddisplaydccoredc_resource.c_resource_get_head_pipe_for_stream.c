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
struct resource_context {struct pipe_ctx* pipe_ctx; } ;
struct pipe_ctx {int /*<<< orphan*/  top_pipe; struct dc_stream_state* stream; } ;
struct dc_stream_state {int dummy; } ;

/* Variables and functions */
 int MAX_PIPES ; 

struct pipe_ctx *resource_get_head_pipe_for_stream(
		struct resource_context *res_ctx,
		struct dc_stream_state *stream)
{
	int i;
	for (i = 0; i < MAX_PIPES; i++) {
		if (res_ctx->pipe_ctx[i].stream == stream &&
				!res_ctx->pipe_ctx[i].top_pipe) {
			return &res_ctx->pipe_ctx[i];
			break;
		}
	}
	return NULL;
}