#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource_context {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_11__ {TYPE_7__* tg; } ;
struct pipe_ctx {unsigned int pipe_idx; TYPE_6__* stream; TYPE_4__ stream_res; } ;
struct dc {TYPE_3__* res_pool; TYPE_1__* ctx; } ;
struct crtc_position {int horizontal_count; int vertical_count; } ;
struct TYPE_14__ {int /*<<< orphan*/  inst; TYPE_2__* funcs; } ;
struct TYPE_12__ {int /*<<< orphan*/  v_total; int /*<<< orphan*/  h_total; } ;
struct TYPE_13__ {TYPE_5__ timing; } ;
struct TYPE_10__ {unsigned int underlay_pipe_index; int pipe_count; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* get_position ) (TYPE_7__*,struct crtc_position*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  logger; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int MAX_PIPES ; 
 int /*<<< orphan*/  TIMING_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,struct crtc_position*) ; 

void context_timing_trace(
		struct dc *dc,
		struct resource_context *res_ctx)
{
	int i;
	struct dc  *core_dc = dc;
	int h_pos[MAX_PIPES], v_pos[MAX_PIPES];
	struct crtc_position position;
	unsigned int underlay_idx = core_dc->res_pool->underlay_pipe_index;
	DC_LOGGER_INIT(dc->ctx->logger);


	for (i = 0; i < core_dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx = &res_ctx->pipe_ctx[i];
		/* get_position() returns CRTC vertical/horizontal counter
		 * hence not applicable for underlay pipe
		 */
		if (pipe_ctx->stream == NULL
				 || pipe_ctx->pipe_idx == underlay_idx)
			continue;

		pipe_ctx->stream_res.tg->funcs->get_position(pipe_ctx->stream_res.tg, &position);
		h_pos[i] = position.horizontal_count;
		v_pos[i] = position.vertical_count;
	}
	for (i = 0; i < core_dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx = &res_ctx->pipe_ctx[i];

		if (pipe_ctx->stream == NULL)
			continue;

		TIMING_TRACE("OTG_%d   H_tot:%d  V_tot:%d   H_pos:%d  V_pos:%d\n",
				pipe_ctx->stream_res.tg->inst,
				pipe_ctx->stream->timing.h_total,
				pipe_ctx->stream->timing.v_total,
				h_pos[i], v_pos[i]);
	}
}