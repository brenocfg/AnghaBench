#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pipe_ctx {int dummy; } ;
struct dc_stream_state {int dummy; } ;
struct dc_state {int /*<<< orphan*/  res_ctx; } ;
struct dc {int dummy; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;

/* Variables and functions */
 int DC_ERROR_UNEXPECTED ; 
 int DC_OK ; 
 int /*<<< orphan*/  build_pipe_hw_param (struct pipe_ctx*) ; 
 struct pipe_ctx* resource_get_head_pipe_for_stream (int /*<<< orphan*/ *,struct dc_stream_state*) ; 

__attribute__((used)) static enum dc_status build_mapped_resource(
		const struct dc *dc,
		struct dc_state *context,
		struct dc_stream_state *stream)
{
	struct pipe_ctx *pipe_ctx = resource_get_head_pipe_for_stream(&context->res_ctx, stream);

	/*TODO Seems unneeded anymore */
	/*	if (old_context && resource_is_stream_unchanged(old_context, stream)) {
			if (stream != NULL && old_context->streams[i] != NULL) {
				 todo: shouldn't have to copy missing parameter here
				resource_build_bit_depth_reduction_params(stream,
						&stream->bit_depth_params);
				stream->clamping.pixel_encoding =
						stream->timing.pixel_encoding;

				resource_build_bit_depth_reduction_params(stream,
								&stream->bit_depth_params);
				build_clamping_params(stream);

				continue;
			}
		}
	*/

	if (!pipe_ctx)
		return DC_ERROR_UNEXPECTED;

	build_pipe_hw_param(pipe_ctx);
	return DC_OK;
}