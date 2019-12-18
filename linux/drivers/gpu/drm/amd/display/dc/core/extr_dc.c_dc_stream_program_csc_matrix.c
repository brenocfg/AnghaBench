#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_5__* opp; } ;
struct pipe_ctx {TYPE_6__ stream_res; struct dc_stream_state* stream; } ;
struct TYPE_10__ {int /*<<< orphan*/  matrix; } ;
struct dc_stream_state {TYPE_4__ csc_color_matrix; int /*<<< orphan*/  output_color_space; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* program_output_csc ) (struct dc*,struct pipe_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct dc {TYPE_3__ hwss; TYPE_2__* current_state; } ;
struct TYPE_11__ {int /*<<< orphan*/  inst; } ;
struct TYPE_7__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_8__ {TYPE_1__ res_ctx; } ;

/* Variables and functions */
 int MAX_PIPES ; 
 int /*<<< orphan*/  stub1 (struct dc*,struct pipe_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool dc_stream_program_csc_matrix(struct dc *dc, struct dc_stream_state *stream)
{
	int i = 0;
	bool ret = false;
	struct pipe_ctx *pipes;

	for (i = 0; i < MAX_PIPES; i++) {
		if (dc->current_state->res_ctx.pipe_ctx[i].stream
				== stream) {

			pipes = &dc->current_state->res_ctx.pipe_ctx[i];
			dc->hwss.program_output_csc(dc,
					pipes,
					stream->output_color_space,
					stream->csc_color_matrix.matrix,
					pipes->stream_res.opp->inst);
			ret = true;
		}
	}

	return ret;
}