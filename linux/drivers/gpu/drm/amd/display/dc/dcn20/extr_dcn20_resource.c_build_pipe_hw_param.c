#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  pix_clk_params; } ;
struct pipe_ctx {TYPE_6__* stream; int /*<<< orphan*/  pll_settings; TYPE_3__ stream_res; TYPE_5__* clock_source; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_9__ {int /*<<< orphan*/  pixel_encoding; } ;
struct TYPE_8__ {int /*<<< orphan*/  pixel_encoding; } ;
struct TYPE_13__ {int /*<<< orphan*/  bit_depth_params; TYPE_2__ timing; TYPE_1__ clamping; } ;
struct TYPE_12__ {TYPE_4__* funcs; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* get_pix_clk_dividers ) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int DC_OK ; 
 int /*<<< orphan*/  build_clamping_params (TYPE_6__*) ; 
 int /*<<< orphan*/  get_pixel_clock_parameters (struct pipe_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_build_bit_depth_reduction_params (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum dc_status build_pipe_hw_param(struct pipe_ctx *pipe_ctx)
{

	get_pixel_clock_parameters(pipe_ctx, &pipe_ctx->stream_res.pix_clk_params);

	pipe_ctx->clock_source->funcs->get_pix_clk_dividers(
		pipe_ctx->clock_source,
		&pipe_ctx->stream_res.pix_clk_params,
		&pipe_ctx->pll_settings);

	pipe_ctx->stream->clamping.pixel_encoding = pipe_ctx->stream->timing.pixel_encoding;

	resource_build_bit_depth_reduction_params(pipe_ctx->stream,
					&pipe_ctx->stream->bit_depth_params);
	build_clamping_params(pipe_ctx->stream);

	return DC_OK;
}