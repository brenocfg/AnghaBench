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
struct TYPE_7__ {scalar_t__ tg; } ;
struct pipe_ctx {struct dc_stream_state* stream; TYPE_3__ stream_res; } ;
struct dc_crtc_timing_adjust {int /*<<< orphan*/  v_total_mid_frame_num; int /*<<< orphan*/  v_total_mid; int /*<<< orphan*/  v_total_max; int /*<<< orphan*/  v_total_min; } ;
struct dc_stream_state {struct dc_crtc_timing_adjust adjust; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_drr ) (struct pipe_ctx**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct dc {TYPE_4__ hwss; TYPE_2__* current_state; } ;
struct TYPE_5__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_6__ {TYPE_1__ res_ctx; } ;

/* Variables and functions */
 int MAX_PIPES ; 
 int /*<<< orphan*/  stub1 (struct pipe_ctx**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool dc_stream_adjust_vmin_vmax(struct dc *dc,
		struct dc_stream_state *stream,
		struct dc_crtc_timing_adjust *adjust)
{
	int i = 0;
	bool ret = false;

	for (i = 0; i < MAX_PIPES; i++) {
		struct pipe_ctx *pipe = &dc->current_state->res_ctx.pipe_ctx[i];

		if (pipe->stream == stream && pipe->stream_res.tg) {
			pipe->stream->adjust = *adjust;
			dc->hwss.set_drr(&pipe,
					1,
					adjust->v_total_min,
					adjust->v_total_max,
					adjust->v_total_mid,
					adjust->v_total_mid_frame_num);

			ret = true;
		}
	}
	return ret;
}