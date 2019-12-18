#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pipe_ctx {int /*<<< orphan*/  clock_source; struct dc_stream_state* stream; TYPE_4__* plane_state; } ;
struct dc_stream_state {int /*<<< orphan*/  signal; } ;
struct TYPE_13__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {int stream_count; TYPE_5__ res_ctx; struct dc_stream_state** streams; } ;
struct dc {TYPE_6__* res_pool; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_14__ {int pipe_count; TYPE_3__* funcs; int /*<<< orphan*/  dp_clock_source; } ;
struct TYPE_9__ {scalar_t__ swizzle; } ;
struct TYPE_10__ {TYPE_1__ gfx9; } ;
struct TYPE_12__ {TYPE_2__ tiling_info; } ;
struct TYPE_11__ {int (* validate_global ) (struct dc*,struct dc_state*) ;int (* get_default_swizzle_mode ) (TYPE_4__*) ;int /*<<< orphan*/  (* validate_bandwidth ) (struct dc*,struct dc_state*,int) ;} ;

/* Variables and functions */
 int DC_ERROR_UNEXPECTED ; 
 int DC_FAIL_BANDWIDTH_VALIDATE ; 
 int DC_OK ; 
 scalar_t__ DC_SW_UNKNOWN ; 
 scalar_t__ dc_is_dp_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_pll_sharable_stream (struct dc_stream_state*,struct dc_state*) ; 
 int resource_build_scaling_params_for_context (struct dc*,struct dc_state*) ; 
 int /*<<< orphan*/  resource_reference_clock_source (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_unreference_clock_source (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dc*,struct dc_state*) ; 
 int stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (struct dc*,struct dc_state*,int) ; 

enum dc_status dc_validate_global_state(
		struct dc *dc,
		struct dc_state *new_ctx,
		bool fast_validate)
{
	enum dc_status result = DC_ERROR_UNEXPECTED;
	int i, j;

	if (!new_ctx)
		return DC_ERROR_UNEXPECTED;

	if (dc->res_pool->funcs->validate_global) {
		result = dc->res_pool->funcs->validate_global(dc, new_ctx);
		if (result != DC_OK)
			return result;
	}

	for (i = 0; i < new_ctx->stream_count; i++) {
		struct dc_stream_state *stream = new_ctx->streams[i];

		for (j = 0; j < dc->res_pool->pipe_count; j++) {
			struct pipe_ctx *pipe_ctx = &new_ctx->res_ctx.pipe_ctx[j];

			if (pipe_ctx->stream != stream)
				continue;

			if (dc->res_pool->funcs->get_default_swizzle_mode &&
					pipe_ctx->plane_state &&
					pipe_ctx->plane_state->tiling_info.gfx9.swizzle == DC_SW_UNKNOWN) {
				result = dc->res_pool->funcs->get_default_swizzle_mode(pipe_ctx->plane_state);
				if (result != DC_OK)
					return result;
			}

			/* Switch to dp clock source only if there is
			 * no non dp stream that shares the same timing
			 * with the dp stream.
			 */
			if (dc_is_dp_signal(pipe_ctx->stream->signal) &&
				!find_pll_sharable_stream(stream, new_ctx)) {

				resource_unreference_clock_source(
						&new_ctx->res_ctx,
						dc->res_pool,
						pipe_ctx->clock_source);

				pipe_ctx->clock_source = dc->res_pool->dp_clock_source;
				resource_reference_clock_source(
						&new_ctx->res_ctx,
						dc->res_pool,
						 pipe_ctx->clock_source);
			}
		}
	}

	result = resource_build_scaling_params_for_context(dc, new_ctx);

	if (result == DC_OK)
		if (!dc->res_pool->funcs->validate_bandwidth(dc, new_ctx, fast_validate))
			result = DC_FAIL_BANDWIDTH_VALIDATE;

	return result;
}