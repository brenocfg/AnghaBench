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
typedef  int uint8_t ;
struct pipe_ctx {struct dc_stream_state* stream; } ;
struct dc_stream_state {int dummy; } ;
struct TYPE_5__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_1__ res_ctx; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* setup_stereo ) (struct pipe_ctx*,struct dc*) ;} ;
struct dc {TYPE_4__ hwss; TYPE_3__* current_state; } ;
struct TYPE_6__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_7__ {TYPE_2__ res_ctx; } ;

/* Variables and functions */
 int MAX_PIPES ; 
 int /*<<< orphan*/  stub1 (struct pipe_ctx*,struct dc*) ; 

bool dc_enable_stereo(
	struct dc *dc,
	struct dc_state *context,
	struct dc_stream_state *streams[],
	uint8_t stream_count)
{
	bool ret = true;
	int i, j;
	struct pipe_ctx *pipe;

	for (i = 0; i < MAX_PIPES; i++) {
		if (context != NULL)
			pipe = &context->res_ctx.pipe_ctx[i];
		else
			pipe = &dc->current_state->res_ctx.pipe_ctx[i];
		for (j = 0 ; pipe && j < stream_count; j++)  {
			if (streams[j] && streams[j] == pipe->stream &&
				dc->hwss.setup_stereo)
				dc->hwss.setup_stereo(pipe, dc);
		}
	}

	return ret;
}