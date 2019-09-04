#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ audio; int /*<<< orphan*/  stream_enc; } ;
struct pipe_ctx {int /*<<< orphan*/  clock_source; TYPE_1__ stream_res; int /*<<< orphan*/  top_pipe; struct dc_stream_state* stream; } ;
struct dc_stream_state {int dummy; } ;
struct TYPE_11__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {int stream_count; struct pipe_ctx* stream_status; struct dc_stream_state** streams; TYPE_3__ res_ctx; } ;
struct dc_context {int dummy; } ;
struct dc {TYPE_4__* res_pool; struct dc_context* ctx; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_12__ {TYPE_2__* funcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* remove_stream_from_ctx ) (struct dc*,struct dc_state*,struct dc_stream_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_ERROR (char*,struct dc_stream_state*) ; 
 int DC_ERROR_UNEXPECTED ; 
 int DC_OK ; 
 int MAX_PIPES ; 
 int /*<<< orphan*/  dc_stream_release (struct dc_stream_state*) ; 
 int /*<<< orphan*/  memset (struct pipe_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_unreference_clock_source (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dc*,struct dc_state*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  update_audio_usage (TYPE_3__*,TYPE_4__*,scalar_t__,int) ; 
 int /*<<< orphan*/  update_stream_engine_usage (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int) ; 

enum dc_status dc_remove_stream_from_ctx(
			struct dc *dc,
			struct dc_state *new_ctx,
			struct dc_stream_state *stream)
{
	int i;
	struct dc_context *dc_ctx = dc->ctx;
	struct pipe_ctx *del_pipe = NULL;

	/* Release primary pipe */
	for (i = 0; i < MAX_PIPES; i++) {
		if (new_ctx->res_ctx.pipe_ctx[i].stream == stream &&
				!new_ctx->res_ctx.pipe_ctx[i].top_pipe) {
			del_pipe = &new_ctx->res_ctx.pipe_ctx[i];

			ASSERT(del_pipe->stream_res.stream_enc);
			update_stream_engine_usage(
					&new_ctx->res_ctx,
						dc->res_pool,
					del_pipe->stream_res.stream_enc,
					false);

			if (del_pipe->stream_res.audio)
				update_audio_usage(
					&new_ctx->res_ctx,
					dc->res_pool,
					del_pipe->stream_res.audio,
					false);

			resource_unreference_clock_source(&new_ctx->res_ctx,
							  dc->res_pool,
							  del_pipe->clock_source);

			if (dc->res_pool->funcs->remove_stream_from_ctx)
				dc->res_pool->funcs->remove_stream_from_ctx(dc, new_ctx, stream);

			memset(del_pipe, 0, sizeof(*del_pipe));

			break;
		}
	}

	if (!del_pipe) {
		DC_ERROR("Pipe not found for stream %p !\n", stream);
		return DC_ERROR_UNEXPECTED;
	}

	for (i = 0; i < new_ctx->stream_count; i++)
		if (new_ctx->streams[i] == stream)
			break;

	if (new_ctx->streams[i] != stream) {
		DC_ERROR("Context doesn't have stream %p !\n", stream);
		return DC_ERROR_UNEXPECTED;
	}

	dc_stream_release(new_ctx->streams[i]);
	new_ctx->stream_count--;

	/* Trim back arrays */
	for (; i < new_ctx->stream_count; i++) {
		new_ctx->streams[i] = new_ctx->streams[i + 1];
		new_ctx->stream_status[i] = new_ctx->stream_status[i + 1];
	}

	new_ctx->streams[new_ctx->stream_count] = NULL;
	memset(
			&new_ctx->stream_status[new_ctx->stream_count],
			0,
			sizeof(new_ctx->stream_status[0]));

	return DC_OK;
}