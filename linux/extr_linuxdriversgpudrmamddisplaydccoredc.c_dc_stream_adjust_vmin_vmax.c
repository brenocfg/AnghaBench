#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ stream_enc; } ;
struct pipe_ctx {TYPE_3__ stream_res; struct dc_stream_state* stream; } ;
struct dc_stream_state {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* update_info_frame ) (struct pipe_ctx*) ;int /*<<< orphan*/  (* set_drr ) (struct pipe_ctx**,int,int,int) ;} ;
struct dc {TYPE_4__ hwss; TYPE_2__* current_state; } ;
struct TYPE_5__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_6__ {TYPE_1__ res_ctx; } ;

/* Variables and functions */
 int MAX_PIPES ; 
 int /*<<< orphan*/  resource_build_info_frame (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub1 (struct pipe_ctx**,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct pipe_ctx*) ; 

bool dc_stream_adjust_vmin_vmax(struct dc *dc,
		struct dc_stream_state **streams, int num_streams,
		int vmin, int vmax)
{
	/* TODO: Support multiple streams */
	struct dc_stream_state *stream = streams[0];
	int i = 0;
	bool ret = false;

	for (i = 0; i < MAX_PIPES; i++) {
		struct pipe_ctx *pipe = &dc->current_state->res_ctx.pipe_ctx[i];

		if (pipe->stream == stream && pipe->stream_res.stream_enc) {
			dc->hwss.set_drr(&pipe, 1, vmin, vmax);

			/* build and update the info frame */
			resource_build_info_frame(pipe);
			dc->hwss.update_info_frame(pipe);

			ret = true;
		}
	}
	return ret;
}