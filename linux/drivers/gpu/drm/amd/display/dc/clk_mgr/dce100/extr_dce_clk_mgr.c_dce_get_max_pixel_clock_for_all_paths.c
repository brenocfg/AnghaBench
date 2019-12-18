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
typedef  int uint32_t ;
struct TYPE_7__ {int requested_pix_clk_100hz; int requested_sym_clk; } ;
struct TYPE_8__ {TYPE_3__ pix_clk_params; } ;
struct pipe_ctx {TYPE_4__ stream_res; TYPE_2__* stream; scalar_t__ top_pipe; } ;
struct TYPE_5__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_1__ res_ctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  signal; } ;

/* Variables and functions */
 int MAX_PIPES ; 
 scalar_t__ dc_is_dp_signal (int /*<<< orphan*/ ) ; 

uint32_t dce_get_max_pixel_clock_for_all_paths(struct dc_state *context)
{
	uint32_t max_pix_clk = 0;
	int i;

	for (i = 0; i < MAX_PIPES; i++) {
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		if (pipe_ctx->stream == NULL)
			continue;

		/* do not check under lay */
		if (pipe_ctx->top_pipe)
			continue;

		if (pipe_ctx->stream_res.pix_clk_params.requested_pix_clk_100hz / 10 > max_pix_clk)
			max_pix_clk = pipe_ctx->stream_res.pix_clk_params.requested_pix_clk_100hz / 10;

		/* raise clock state for HBR3/2 if required. Confirmed with HW DCE/DPCS
		 * logic for HBR3 still needs Nominal (0.8V) on VDDC rail
		 */
		if (dc_is_dp_signal(pipe_ctx->stream->signal) &&
				pipe_ctx->stream_res.pix_clk_params.requested_sym_clk > max_pix_clk)
			max_pix_clk = pipe_ctx->stream_res.pix_clk_params.requested_sym_clk;
	}

	return max_pix_clk;
}