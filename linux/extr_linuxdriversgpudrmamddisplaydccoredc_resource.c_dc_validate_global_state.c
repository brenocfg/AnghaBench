#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pipe_ctx {int /*<<< orphan*/  clock_source; struct dc_stream_state* stream; } ;
struct dc_stream_state {int /*<<< orphan*/  signal; } ;
struct TYPE_7__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {int stream_count; TYPE_2__ res_ctx; struct dc_stream_state** streams; } ;
struct dc {TYPE_3__* res_pool; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_8__ {int pipe_count; TYPE_1__* funcs; int /*<<< orphan*/  dp_clock_source; } ;
struct TYPE_6__ {int (* validate_global ) (struct dc*,struct dc_state*) ;int /*<<< orphan*/  (* validate_bandwidth ) (struct dc*,struct dc_state*) ;} ;

/* Variables and functions */
 int DC_ERROR_UNEXPECTED ; 
 int DC_FAIL_BANDWIDTH_VALIDATE ; 
 int DC_OK ; 
 scalar_t__ dc_is_dp_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_pll_sharable_stream (struct dc_stream_state*,struct dc_state*) ; 
 int resource_build_scaling_params_for_context (struct dc*,struct dc_state*) ; 
 int /*<<< orphan*/  resource_reference_clock_source (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_unreference_clock_source (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dc*,struct dc_state*) ; 
 int /*<<< orphan*/  stub2 (struct dc*,struct dc_state*) ; 

enum dc_status dc_validate_global_state(
		struct dc *dc,
		struct dc_state *new_ctx)
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
		if (!dc->res_pool->funcs->validate_bandwidth(dc, new_ctx))
			result = DC_FAIL_BANDWIDTH_VALIDATE;

	return result;
}