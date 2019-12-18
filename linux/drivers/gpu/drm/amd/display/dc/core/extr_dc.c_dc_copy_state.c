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
struct pipe_ctx {size_t pipe_idx; struct pipe_ctx* next_odm_pipe; struct pipe_ctx* prev_odm_pipe; struct pipe_ctx* bottom_pipe; struct pipe_ctx* top_pipe; } ;
struct TYPE_3__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {int stream_count; int /*<<< orphan*/  refcount; TYPE_2__* stream_status; int /*<<< orphan*/ * streams; TYPE_1__ res_ctx; } ;
struct TYPE_4__ {int plane_count; int /*<<< orphan*/ * plane_states; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_PIPES ; 
 int /*<<< orphan*/  dc_plane_state_retain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_stream_retain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct dc_state* kvmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct dc_state*,struct dc_state*,int) ; 

struct dc_state *dc_copy_state(struct dc_state *src_ctx)
{
	int i, j;
	struct dc_state *new_ctx = kvmalloc(sizeof(struct dc_state), GFP_KERNEL);

	if (!new_ctx)
		return NULL;
	memcpy(new_ctx, src_ctx, sizeof(struct dc_state));

	for (i = 0; i < MAX_PIPES; i++) {
			struct pipe_ctx *cur_pipe = &new_ctx->res_ctx.pipe_ctx[i];

			if (cur_pipe->top_pipe)
				cur_pipe->top_pipe =  &new_ctx->res_ctx.pipe_ctx[cur_pipe->top_pipe->pipe_idx];

			if (cur_pipe->bottom_pipe)
				cur_pipe->bottom_pipe = &new_ctx->res_ctx.pipe_ctx[cur_pipe->bottom_pipe->pipe_idx];

			if (cur_pipe->prev_odm_pipe)
				cur_pipe->prev_odm_pipe =  &new_ctx->res_ctx.pipe_ctx[cur_pipe->prev_odm_pipe->pipe_idx];

			if (cur_pipe->next_odm_pipe)
				cur_pipe->next_odm_pipe = &new_ctx->res_ctx.pipe_ctx[cur_pipe->next_odm_pipe->pipe_idx];

	}

	for (i = 0; i < new_ctx->stream_count; i++) {
			dc_stream_retain(new_ctx->streams[i]);
			for (j = 0; j < new_ctx->stream_status[i].plane_count; j++)
				dc_plane_state_retain(
					new_ctx->stream_status[i].plane_states[j]);
	}

	kref_init(&new_ctx->refcount);

	return new_ctx;
}