#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pipe_ctx {int dummy; } ;
struct dc_stream_state {int dummy; } ;
struct dc_state {int /*<<< orphan*/  res_ctx; } ;
struct dc {TYPE_1__* res_pool; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_2__ {int /*<<< orphan*/  underlay_pipe_index; } ;

/* Variables and functions */
 int DC_ERROR_UNEXPECTED ; 
 int DC_OK ; 
 int DC_SURFACE_PIXEL_FORMAT_UNSUPPORTED ; 
 int /*<<< orphan*/  dce110_resource_build_pipe_hw_param (struct pipe_ctx*) ; 
 int /*<<< orphan*/  is_surface_pixel_format_supported (struct pipe_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_build_info_frame (struct pipe_ctx*) ; 
 struct pipe_ctx* resource_get_head_pipe_for_stream (int /*<<< orphan*/ *,struct dc_stream_state*) ; 

__attribute__((used)) static enum dc_status build_mapped_resource(
		const struct dc *dc,
		struct dc_state *context,
		struct dc_stream_state *stream)
{
	struct pipe_ctx *pipe_ctx = resource_get_head_pipe_for_stream(&context->res_ctx, stream);

	if (!pipe_ctx)
		return DC_ERROR_UNEXPECTED;

	if (!is_surface_pixel_format_supported(pipe_ctx,
			dc->res_pool->underlay_pipe_index))
		return DC_SURFACE_PIXEL_FORMAT_UNSUPPORTED;

	dce110_resource_build_pipe_hw_param(pipe_ctx);

	/* TODO: validate audio ASIC caps, encoder */

	resource_build_info_frame(pipe_ctx);

	return DC_OK;
}