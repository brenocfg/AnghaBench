#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct tg_color {int /*<<< orphan*/  member_0; } ;
struct TYPE_15__ {TYPE_6__* tg; int /*<<< orphan*/  pix_clk_params; } ;
struct pipe_ctx {size_t pipe_idx; TYPE_5__ stream_res; struct dc_stream_state* stream; int /*<<< orphan*/  pll_settings; TYPE_8__* clock_source; } ;
struct dc_stream_state {int /*<<< orphan*/  signal; int /*<<< orphan*/  timing; int /*<<< orphan*/  output_color_space; } ;
struct dc_state {int dummy; } ;
struct dc {TYPE_2__* current_state; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_17__ {TYPE_3__* funcs; } ;
struct TYPE_16__ {TYPE_4__* funcs; } ;
struct TYPE_14__ {int (* enable_crtc ) (TYPE_6__*) ;int /*<<< orphan*/  (* program_timing ) (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* set_blank ) (TYPE_6__*,int) ;int /*<<< orphan*/  (* set_blank_color ) (TYPE_6__*,struct tg_color*) ;} ;
struct TYPE_13__ {int (* program_pix_clk ) (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_12__ {TYPE_1__ res_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int DC_ERROR_UNEXPECTED ; 
 int DC_OK ; 
 int /*<<< orphan*/  color_space_to_black_color (struct dc*,int /*<<< orphan*/ ,struct tg_color*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,struct tg_color*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int) ; 
 int stub3 (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub5 (TYPE_6__*) ; 

__attribute__((used)) static enum dc_status dce110_enable_stream_timing(
		struct pipe_ctx *pipe_ctx,
		struct dc_state *context,
		struct dc *dc)
{
	struct dc_stream_state *stream = pipe_ctx->stream;
	struct pipe_ctx *pipe_ctx_old = &dc->current_state->res_ctx.
			pipe_ctx[pipe_ctx->pipe_idx];
	struct tg_color black_color = {0};

	if (!pipe_ctx_old->stream) {

		/* program blank color */
		color_space_to_black_color(dc,
				stream->output_color_space, &black_color);
		pipe_ctx->stream_res.tg->funcs->set_blank_color(
				pipe_ctx->stream_res.tg,
				&black_color);

		/*
		 * Must blank CRTC after disabling power gating and before any
		 * programming, otherwise CRTC will be hung in bad state
		 */
		pipe_ctx->stream_res.tg->funcs->set_blank(pipe_ctx->stream_res.tg, true);

		if (false == pipe_ctx->clock_source->funcs->program_pix_clk(
				pipe_ctx->clock_source,
				&pipe_ctx->stream_res.pix_clk_params,
				&pipe_ctx->pll_settings)) {
			BREAK_TO_DEBUGGER();
			return DC_ERROR_UNEXPECTED;
		}

		pipe_ctx->stream_res.tg->funcs->program_timing(
				pipe_ctx->stream_res.tg,
				&stream->timing,
				0,
				0,
				0,
				0,
				pipe_ctx->stream->signal,
				true);
	}

	if (!pipe_ctx_old->stream) {
		if (false == pipe_ctx->stream_res.tg->funcs->enable_crtc(
				pipe_ctx->stream_res.tg)) {
			BREAK_TO_DEBUGGER();
			return DC_ERROR_UNEXPECTED;
		}
	}

	return DC_OK;
}