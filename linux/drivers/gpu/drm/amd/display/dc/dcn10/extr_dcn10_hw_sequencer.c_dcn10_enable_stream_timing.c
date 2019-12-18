#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct tg_color {int /*<<< orphan*/  member_0; } ;
struct TYPE_24__ {TYPE_6__* tg; TYPE_10__* opp; int /*<<< orphan*/  pix_clk_params; } ;
struct TYPE_21__ {int /*<<< orphan*/  vupdate_width; int /*<<< orphan*/  vupdate_offset; int /*<<< orphan*/  vstartup_start; int /*<<< orphan*/  vready_offset; } ;
struct pipe_ctx {TYPE_5__ stream_res; struct dc_stream_state* stream; TYPE_2__ pipe_dlg_param; int /*<<< orphan*/  pll_settings; TYPE_12__* clock_source; int /*<<< orphan*/ * top_pipe; } ;
struct dc_stream_state {int output_color_space; int /*<<< orphan*/  clamping; int /*<<< orphan*/  bit_depth_params; int /*<<< orphan*/  signal; int /*<<< orphan*/  timing; } ;
struct dc_state {int dummy; } ;
struct dc {int dummy; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;
struct TYPE_25__ {size_t inst; TYPE_4__* funcs; } ;
struct TYPE_23__ {int (* enable_crtc ) (TYPE_6__*) ;int /*<<< orphan*/  (* set_blank ) (TYPE_6__*,int) ;int /*<<< orphan*/  (* is_blanked ) (TYPE_6__*) ;int /*<<< orphan*/  (* set_blank_color ) (TYPE_6__*,struct tg_color*) ;int /*<<< orphan*/  (* program_timing ) (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* enable_optc_clock ) (TYPE_6__*,int) ;} ;
struct TYPE_22__ {int /*<<< orphan*/  (* opp_program_fmt ) (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_20__ {int (* program_pix_clk ) (TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  fmt; } ;
struct TYPE_18__ {TYPE_1__* funcs; } ;
struct TYPE_17__ {TYPE_3__* funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int DC_ERROR_UNEXPECTED ; 
 int DC_OK ; 
 int /*<<< orphan*/  color_space_to_black_color (struct dc*,int,struct tg_color*) ; 
 int /*<<< orphan*/  false_optc_underflow_wa (struct dc*,struct dc_stream_state*,TYPE_6__*) ; 
 int /*<<< orphan*/  hwss_wait_for_blank_complete (TYPE_6__*) ; 
 int /*<<< orphan*/  inst_offset ; 
 TYPE_14__* reg_offsets ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int) ; 
 int stub2 (TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*,struct tg_color*) ; 
 int /*<<< orphan*/  stub6 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub7 (TYPE_6__*,int) ; 
 int stub8 (TYPE_6__*) ; 

__attribute__((used)) static enum dc_status dcn10_enable_stream_timing(
		struct pipe_ctx *pipe_ctx,
		struct dc_state *context,
		struct dc *dc)
{
	struct dc_stream_state *stream = pipe_ctx->stream;
	enum dc_color_space color_space;
	struct tg_color black_color = {0};

	/* by upper caller loop, pipe0 is parent pipe and be called first.
	 * back end is set up by for pipe0. Other children pipe share back end
	 * with pipe 0. No program is needed.
	 */
	if (pipe_ctx->top_pipe != NULL)
		return DC_OK;

	/* TODO check if timing_changed, disable stream if timing changed */

	/* HW program guide assume display already disable
	 * by unplug sequence. OTG assume stop.
	 */
	pipe_ctx->stream_res.tg->funcs->enable_optc_clock(pipe_ctx->stream_res.tg, true);

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
			pipe_ctx->pipe_dlg_param.vready_offset,
			pipe_ctx->pipe_dlg_param.vstartup_start,
			pipe_ctx->pipe_dlg_param.vupdate_offset,
			pipe_ctx->pipe_dlg_param.vupdate_width,
			pipe_ctx->stream->signal,
			true);

#if 0 /* move to after enable_crtc */
	/* TODO: OPP FMT, ABM. etc. should be done here. */
	/* or FPGA now. instance 0 only. TODO: move to opp.c */

	inst_offset = reg_offsets[pipe_ctx->stream_res.tg->inst].fmt;

	pipe_ctx->stream_res.opp->funcs->opp_program_fmt(
				pipe_ctx->stream_res.opp,
				&stream->bit_depth_params,
				&stream->clamping);
#endif
	/* program otg blank color */
	color_space = stream->output_color_space;
	color_space_to_black_color(dc, color_space, &black_color);

	if (pipe_ctx->stream_res.tg->funcs->set_blank_color)
		pipe_ctx->stream_res.tg->funcs->set_blank_color(
				pipe_ctx->stream_res.tg,
				&black_color);

	if (pipe_ctx->stream_res.tg->funcs->is_blanked &&
			!pipe_ctx->stream_res.tg->funcs->is_blanked(pipe_ctx->stream_res.tg)) {
		pipe_ctx->stream_res.tg->funcs->set_blank(pipe_ctx->stream_res.tg, true);
		hwss_wait_for_blank_complete(pipe_ctx->stream_res.tg);
		false_optc_underflow_wa(dc, pipe_ctx->stream, pipe_ctx->stream_res.tg);
	}

	/* VTG is  within DCHUB command block. DCFCLK is always on */
	if (false == pipe_ctx->stream_res.tg->funcs->enable_crtc(pipe_ctx->stream_res.tg)) {
		BREAK_TO_DEBUGGER();
		return DC_ERROR_UNEXPECTED;
	}

	/* TODO program crtc source select for non-virtual signal*/
	/* TODO program FMT */
	/* TODO setup link_enc */
	/* TODO set stream attributes */
	/* TODO program audio */
	/* TODO enable stream if timing changed */
	/* TODO unblank stream if DP */

	return DC_OK;
}