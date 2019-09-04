#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_9__* tg; scalar_t__ audio; int /*<<< orphan*/ * stream_enc; } ;
struct pipe_ctx {TYPE_8__ stream_res; int /*<<< orphan*/  pipe_idx; TYPE_7__* stream; int /*<<< orphan*/ * top_pipe; } ;
struct dc_state {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* disable_audio_stream ) (struct pipe_ctx*,int /*<<< orphan*/ ) ;} ;
struct dc {TYPE_6__* res_pool; TYPE_5__* current_state; TYPE_2__ hwss; TYPE_1__* ctx; } ;
struct TYPE_19__ {int /*<<< orphan*/  inst; TYPE_3__* funcs; } ;
struct TYPE_17__ {int /*<<< orphan*/  dpms_off; } ;
struct TYPE_16__ {int pipe_count; } ;
struct TYPE_14__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_15__ {TYPE_4__ res_ctx; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* enable_optc_clock ) (TYPE_9__*,int) ;int /*<<< orphan*/  (* disable_crtc ) (TYPE_9__*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  dce_environment; int /*<<< orphan*/  logger; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE_ACQUIRED_RESOURCE ; 
 int /*<<< orphan*/  IS_FPGA_MAXIMUS_DC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_link_disable_stream (struct pipe_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pipe_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_9__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_9__*,int) ; 

__attribute__((used)) static void reset_back_end_for_pipe(
		struct dc *dc,
		struct pipe_ctx *pipe_ctx,
		struct dc_state *context)
{
	int i;
	DC_LOGGER_INIT(dc->ctx->logger);
	if (pipe_ctx->stream_res.stream_enc == NULL) {
		pipe_ctx->stream = NULL;
		return;
	}

	if (!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) {
		/* DPMS may already disable */
		if (!pipe_ctx->stream->dpms_off)
			core_link_disable_stream(pipe_ctx, FREE_ACQUIRED_RESOURCE);
		else if (pipe_ctx->stream_res.audio) {
			dc->hwss.disable_audio_stream(pipe_ctx, FREE_ACQUIRED_RESOURCE);
		}

	}

	/* by upper caller loop, parent pipe: pipe0, will be reset last.
	 * back end share by all pipes and will be disable only when disable
	 * parent pipe.
	 */
	if (pipe_ctx->top_pipe == NULL) {
		pipe_ctx->stream_res.tg->funcs->disable_crtc(pipe_ctx->stream_res.tg);

		pipe_ctx->stream_res.tg->funcs->enable_optc_clock(pipe_ctx->stream_res.tg, false);
	}

	for (i = 0; i < dc->res_pool->pipe_count; i++)
		if (&dc->current_state->res_ctx.pipe_ctx[i] == pipe_ctx)
			break;

	if (i == dc->res_pool->pipe_count)
		return;

	pipe_ctx->stream = NULL;
	DC_LOG_DEBUG("Reset back end for pipe %d, tg:%d\n",
					pipe_ctx->pipe_idx, pipe_ctx->stream_res.tg->inst);
}