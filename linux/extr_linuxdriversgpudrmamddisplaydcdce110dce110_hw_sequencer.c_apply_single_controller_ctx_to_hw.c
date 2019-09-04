#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_50__   TYPE_9__ ;
typedef  struct TYPE_49__   TYPE_8__ ;
typedef  struct TYPE_48__   TYPE_7__ ;
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_24__ ;
typedef  struct TYPE_41__   TYPE_21__ ;
typedef  struct TYPE_40__   TYPE_1__ ;
typedef  struct TYPE_39__   TYPE_18__ ;
typedef  struct TYPE_38__   TYPE_17__ ;
typedef  struct TYPE_37__   TYPE_16__ ;
typedef  struct TYPE_36__   TYPE_15__ ;
typedef  struct TYPE_35__   TYPE_14__ ;
typedef  struct TYPE_34__   TYPE_13__ ;
typedef  struct TYPE_33__   TYPE_12__ ;
typedef  struct TYPE_32__   TYPE_11__ ;
typedef  struct TYPE_31__   TYPE_10__ ;

/* Type definitions */
struct TYPE_40__ {int alpha_en; } ;
struct TYPE_43__ {TYPE_1__ lb_params; } ;
struct TYPE_44__ {TYPE_2__ scl_data; } ;
struct TYPE_36__ {TYPE_16__* stream_enc; TYPE_21__* audio; TYPE_18__* opp; TYPE_13__* tg; } ;
struct pipe_ctx {size_t pipe_idx; scalar_t__ bottom_pipe; struct dc_stream_state* stream; TYPE_3__ plane_res; TYPE_15__ stream_res; } ;
struct TYPE_42__ {scalar_t__ timing_3d_format; int /*<<< orphan*/  display_color_depth; } ;
struct dc_stream_state {scalar_t__ signal; TYPE_11__* sink; TYPE_24__ timing; int /*<<< orphan*/  phy_pix_clk; int /*<<< orphan*/  output_color_space; int /*<<< orphan*/  clamping; int /*<<< orphan*/  bit_depth_params; int /*<<< orphan*/  audio_info; } ;
struct dc_state {int dummy; } ;
struct TYPE_48__ {int /*<<< orphan*/  (* enable_stream_timing ) (struct pipe_ctx*,struct dc_state*,struct dc*) ;} ;
struct dc {TYPE_8__* ctx; TYPE_7__ hwss; TYPE_5__* current_state; } ;
struct audio_output {int /*<<< orphan*/  crtc_info; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_50__ {int /*<<< orphan*/  (* setup ) (TYPE_17__*,scalar_t__) ;} ;
struct TYPE_49__ {int /*<<< orphan*/  dce_environment; } ;
struct TYPE_47__ {int /*<<< orphan*/  (* az_configure ) (TYPE_21__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_45__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_46__ {TYPE_4__ res_ctx; } ;
struct TYPE_41__ {TYPE_6__* funcs; int /*<<< orphan*/  inst; } ;
struct TYPE_39__ {TYPE_14__* funcs; } ;
struct TYPE_38__ {TYPE_9__* funcs; } ;
struct TYPE_37__ {TYPE_12__* funcs; } ;
struct TYPE_35__ {int /*<<< orphan*/  (* opp_program_fmt ) (TYPE_18__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* opp_set_dyn_expansion ) (TYPE_18__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_34__ {int /*<<< orphan*/  inst; } ;
struct TYPE_33__ {int /*<<< orphan*/  (* dvi_set_stream_attribute ) (TYPE_16__*,TYPE_24__*,int) ;int /*<<< orphan*/  (* hdmi_set_stream_attribute ) (TYPE_16__*,TYPE_24__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dp_set_stream_attribute ) (TYPE_16__*,TYPE_24__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* setup_stereo_sync ) (TYPE_16__*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* hdmi_audio_setup ) (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dp_audio_setup ) (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_32__ {TYPE_10__* link; } ;
struct TYPE_31__ {int psr_enabled; TYPE_17__* link_enc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  COLOR_SPACE_YCBCR601 ; 
 int DC_ERROR_UNEXPECTED ; 
 int DC_OK ; 
 scalar_t__ IS_FPGA_MAXIMUS_DC (int /*<<< orphan*/ ) ; 
 scalar_t__ SIGNAL_TYPE_DVI_DUAL_LINK ; 
 scalar_t__ SIGNAL_TYPE_VIRTUAL ; 
 scalar_t__ TIMING_3D_FORMAT_NONE ; 
 int bios_parser_crtc_source_select (struct pipe_ctx*) ; 
 int /*<<< orphan*/  build_audio_output (struct dc_state*,struct pipe_ctx*,struct audio_output*) ; 
 int /*<<< orphan*/  core_link_enable_stream (struct dc_state*,struct pipe_ctx*) ; 
 scalar_t__ dc_is_dp_signal (scalar_t__) ; 
 scalar_t__ dc_is_dvi_signal (scalar_t__) ; 
 scalar_t__ dc_is_hdmi_signal (scalar_t__) ; 
 int /*<<< orphan*/  dce110_update_info_frame (struct pipe_ctx*) ; 
 int /*<<< orphan*/  resource_build_info_frame (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub1 (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (TYPE_18__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub11 (TYPE_16__*,TYPE_24__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (TYPE_16__*,TYPE_24__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (TYPE_16__*,TYPE_24__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_21__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct pipe_ctx*,struct dc_state*,struct dc*) ; 
 int /*<<< orphan*/  stub5 (TYPE_18__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub6 (TYPE_18__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (TYPE_18__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub8 (TYPE_17__*,scalar_t__) ; 
 int /*<<< orphan*/  stub9 (TYPE_16__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum dc_status apply_single_controller_ctx_to_hw(
		struct pipe_ctx *pipe_ctx,
		struct dc_state *context,
		struct dc *dc)
{
	struct dc_stream_state *stream = pipe_ctx->stream;
	struct pipe_ctx *pipe_ctx_old = &dc->current_state->res_ctx.
			pipe_ctx[pipe_ctx->pipe_idx];

	if (pipe_ctx->stream_res.audio != NULL) {
		struct audio_output audio_output;

		build_audio_output(context, pipe_ctx, &audio_output);

		if (dc_is_dp_signal(pipe_ctx->stream->signal))
			pipe_ctx->stream_res.stream_enc->funcs->dp_audio_setup(
					pipe_ctx->stream_res.stream_enc,
					pipe_ctx->stream_res.audio->inst,
					&pipe_ctx->stream->audio_info);
		else
			pipe_ctx->stream_res.stream_enc->funcs->hdmi_audio_setup(
					pipe_ctx->stream_res.stream_enc,
					pipe_ctx->stream_res.audio->inst,
					&pipe_ctx->stream->audio_info,
					&audio_output.crtc_info);

		pipe_ctx->stream_res.audio->funcs->az_configure(
				pipe_ctx->stream_res.audio,
				pipe_ctx->stream->signal,
				&audio_output.crtc_info,
				&pipe_ctx->stream->audio_info);
	}

	/*  */
	dc->hwss.enable_stream_timing(pipe_ctx, context, dc);

	/* FPGA does not program backend */
	if (IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) {
		pipe_ctx->stream_res.opp->funcs->opp_set_dyn_expansion(
		pipe_ctx->stream_res.opp,
		COLOR_SPACE_YCBCR601,
		stream->timing.display_color_depth,
		pipe_ctx->stream->signal);

		pipe_ctx->stream_res.opp->funcs->opp_program_fmt(
			pipe_ctx->stream_res.opp,
			&stream->bit_depth_params,
			&stream->clamping);
		return DC_OK;
	}
	/* TODO: move to stream encoder */
	if (pipe_ctx->stream->signal != SIGNAL_TYPE_VIRTUAL)
		if (DC_OK != bios_parser_crtc_source_select(pipe_ctx)) {
			BREAK_TO_DEBUGGER();
			return DC_ERROR_UNEXPECTED;
		}
	pipe_ctx->stream_res.opp->funcs->opp_set_dyn_expansion(
			pipe_ctx->stream_res.opp,
			COLOR_SPACE_YCBCR601,
			stream->timing.display_color_depth,
			pipe_ctx->stream->signal);

	if (pipe_ctx->stream->signal != SIGNAL_TYPE_VIRTUAL)
		stream->sink->link->link_enc->funcs->setup(
			stream->sink->link->link_enc,
			pipe_ctx->stream->signal);

	if (pipe_ctx->stream->signal != SIGNAL_TYPE_VIRTUAL)
		pipe_ctx->stream_res.stream_enc->funcs->setup_stereo_sync(
		pipe_ctx->stream_res.stream_enc,
		pipe_ctx->stream_res.tg->inst,
		stream->timing.timing_3d_format != TIMING_3D_FORMAT_NONE);


	pipe_ctx->stream_res.opp->funcs->opp_program_fmt(
		pipe_ctx->stream_res.opp,
		&stream->bit_depth_params,
		&stream->clamping);

	if (dc_is_dp_signal(pipe_ctx->stream->signal))
		pipe_ctx->stream_res.stream_enc->funcs->dp_set_stream_attribute(
			pipe_ctx->stream_res.stream_enc,
			&stream->timing,
			stream->output_color_space);

	if (dc_is_hdmi_signal(pipe_ctx->stream->signal))
		pipe_ctx->stream_res.stream_enc->funcs->hdmi_set_stream_attribute(
			pipe_ctx->stream_res.stream_enc,
			&stream->timing,
			stream->phy_pix_clk,
			pipe_ctx->stream_res.audio != NULL);

	if (dc_is_dvi_signal(pipe_ctx->stream->signal))
		pipe_ctx->stream_res.stream_enc->funcs->dvi_set_stream_attribute(
			pipe_ctx->stream_res.stream_enc,
			&stream->timing,
			(pipe_ctx->stream->signal == SIGNAL_TYPE_DVI_DUAL_LINK) ?
			true : false);

	resource_build_info_frame(pipe_ctx);
	dce110_update_info_frame(pipe_ctx);
	if (!pipe_ctx_old->stream)
		core_link_enable_stream(context, pipe_ctx);

	pipe_ctx->plane_res.scl_data.lb_params.alpha_en = pipe_ctx->bottom_pipe != 0;

	pipe_ctx->stream->sink->link->psr_enabled = false;

	return DC_OK;
}