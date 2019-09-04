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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ requested_pix_clk; } ;
struct TYPE_5__ {TYPE_1__ pix_clk_params; } ;
struct pipe_ctx {TYPE_2__ stream_res; scalar_t__ top_pipe; int /*<<< orphan*/ * stream; } ;
struct TYPE_6__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_3__ res_ctx; } ;
struct dc {int dummy; } ;

/* Variables and functions */
 int MAX_PIPES ; 

__attribute__((used)) static uint32_t get_max_pixel_clock_for_all_paths(
	struct dc *dc,
	struct dc_state *context)
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

		if (pipe_ctx->stream_res.pix_clk_params.requested_pix_clk > max_pix_clk)
			max_pix_clk =
				pipe_ctx->stream_res.pix_clk_params.requested_pix_clk;
	}

	return max_pix_clk;
}