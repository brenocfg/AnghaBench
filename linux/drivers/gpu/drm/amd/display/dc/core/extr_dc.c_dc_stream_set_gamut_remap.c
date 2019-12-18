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
struct pipe_ctx {struct dc_stream_state const* stream; } ;
struct dc_stream_state {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* program_gamut_remap ) (struct pipe_ctx*) ;} ;
struct dc {TYPE_1__ hwss; TYPE_3__* current_state; } ;
struct TYPE_5__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_6__ {TYPE_2__ res_ctx; } ;

/* Variables and functions */
 int MAX_PIPES ; 
 int /*<<< orphan*/  stub1 (struct pipe_ctx*) ; 

bool dc_stream_set_gamut_remap(struct dc *dc, const struct dc_stream_state *stream)
{
	int i = 0;
	bool ret = false;
	struct pipe_ctx *pipes;

	for (i = 0; i < MAX_PIPES; i++) {
		if (dc->current_state->res_ctx.pipe_ctx[i].stream == stream) {
			pipes = &dc->current_state->res_ctx.pipe_ctx[i];
			dc->hwss.program_gamut_remap(pipes);
			ret = true;
		}
	}

	return ret;
}