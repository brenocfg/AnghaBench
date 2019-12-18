#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pipe_ctx {size_t pipe_idx; struct pipe_ctx* prev_odm_pipe; struct pipe_ctx* next_odm_pipe; struct pipe_ctx* bottom_pipe; struct pipe_ctx* top_pipe; } ;
struct kref {int dummy; } ;
struct TYPE_3__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {int stream_count; struct kref refcount; TYPE_2__* stream_status; int /*<<< orphan*/ * streams; TYPE_1__ res_ctx; } ;
struct TYPE_4__ {int plane_count; int /*<<< orphan*/ * plane_states; } ;

/* Variables and functions */
 int MAX_PIPES ; 
 int /*<<< orphan*/  dc_plane_state_retain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_stream_retain (int /*<<< orphan*/ ) ; 

void dc_resource_state_copy_construct(
		const struct dc_state *src_ctx,
		struct dc_state *dst_ctx)
{
	int i, j;
	struct kref refcount = dst_ctx->refcount;

	*dst_ctx = *src_ctx;

	for (i = 0; i < MAX_PIPES; i++) {
		struct pipe_ctx *cur_pipe = &dst_ctx->res_ctx.pipe_ctx[i];

		if (cur_pipe->top_pipe)
			cur_pipe->top_pipe =  &dst_ctx->res_ctx.pipe_ctx[cur_pipe->top_pipe->pipe_idx];

		if (cur_pipe->bottom_pipe)
			cur_pipe->bottom_pipe = &dst_ctx->res_ctx.pipe_ctx[cur_pipe->bottom_pipe->pipe_idx];

		if (cur_pipe->next_odm_pipe)
			cur_pipe->next_odm_pipe =  &dst_ctx->res_ctx.pipe_ctx[cur_pipe->next_odm_pipe->pipe_idx];

		if (cur_pipe->prev_odm_pipe)
			cur_pipe->prev_odm_pipe = &dst_ctx->res_ctx.pipe_ctx[cur_pipe->prev_odm_pipe->pipe_idx];
	}

	for (i = 0; i < dst_ctx->stream_count; i++) {
		dc_stream_retain(dst_ctx->streams[i]);
		for (j = 0; j < dst_ctx->stream_status[i].plane_count; j++)
			dc_plane_state_retain(
				dst_ctx->stream_status[i].plane_states[j]);
	}

	/* context refcount should not be overridden */
	dst_ctx->refcount = refcount;

}