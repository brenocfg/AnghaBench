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
struct resource_pool {int pipe_count; } ;
struct pipe_ctx {struct dc_plane_state* plane_state; TYPE_3__* top_pipe; TYPE_2__* bottom_pipe; } ;
struct dc_stream_status {int plane_count; struct dc_plane_state** plane_states; } ;
struct dc_stream_state {int dummy; } ;
struct TYPE_4__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {int stream_count; TYPE_1__ res_ctx; struct dc_stream_status* stream_status; struct dc_stream_state** streams; } ;
struct dc_plane_state {int dummy; } ;
struct dc {struct resource_pool* res_pool; } ;
struct TYPE_6__ {TYPE_2__* bottom_pipe; } ;
struct TYPE_5__ {TYPE_3__* top_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_plane_state_release (struct dc_plane_state*) ; 
 int /*<<< orphan*/  dm_error (char*) ; 
 int /*<<< orphan*/  memset (struct pipe_ctx*,int /*<<< orphan*/ ,int) ; 

bool dc_remove_plane_from_context(
		const struct dc *dc,
		struct dc_stream_state *stream,
		struct dc_plane_state *plane_state,
		struct dc_state *context)
{
	int i;
	struct dc_stream_status *stream_status = NULL;
	struct resource_pool *pool = dc->res_pool;

	for (i = 0; i < context->stream_count; i++)
		if (context->streams[i] == stream) {
			stream_status = &context->stream_status[i];
			break;
		}

	if (stream_status == NULL) {
		dm_error("Existing stream not found; failed to remove plane.\n");
		return false;
	}

	/* release pipe for plane*/
	for (i = pool->pipe_count - 1; i >= 0; i--) {
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		if (pipe_ctx->plane_state == plane_state) {
			if (pipe_ctx->top_pipe)
				pipe_ctx->top_pipe->bottom_pipe = pipe_ctx->bottom_pipe;

			/* Second condition is to avoid setting NULL to top pipe
			 * of tail pipe making it look like head pipe in subsequent
			 * deletes
			 */
			if (pipe_ctx->bottom_pipe && pipe_ctx->top_pipe)
				pipe_ctx->bottom_pipe->top_pipe = pipe_ctx->top_pipe;

			/*
			 * For head pipe detach surfaces from pipe for tail
			 * pipe just zero it out
			 */
			if (!pipe_ctx->top_pipe)
				pipe_ctx->plane_state = NULL;
			else
				memset(pipe_ctx, 0, sizeof(*pipe_ctx));
		}
	}


	for (i = 0; i < stream_status->plane_count; i++) {
		if (stream_status->plane_states[i] == plane_state) {

			dc_plane_state_release(stream_status->plane_states[i]);
			break;
		}
	}

	if (i == stream_status->plane_count) {
		dm_error("Existing plane_state not found; failed to detach it!\n");
		return false;
	}

	stream_status->plane_count--;

	/* Start at the plane we've just released, and move all the planes one index forward to "trim" the array */
	for (; i < stream_status->plane_count; i++)
		stream_status->plane_states[i] = stream_status->plane_states[i + 1];

	stream_status->plane_states[stream_status->plane_count] = NULL;

	return true;
}