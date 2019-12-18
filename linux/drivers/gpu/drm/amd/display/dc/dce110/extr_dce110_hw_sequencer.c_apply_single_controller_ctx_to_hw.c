#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_19__ ;
typedef  struct TYPE_28__   TYPE_16__ ;
typedef  struct TYPE_27__   TYPE_14__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct TYPE_30__ {int alpha_en; } ;
struct TYPE_31__ {TYPE_1__ lb_params; } ;
struct TYPE_32__ {TYPE_2__ scl_data; } ;
struct TYPE_25__ {TYPE_19__* opp; TYPE_14__* tg; TYPE_13__* stream_enc; TYPE_16__* audio; } ;
struct pipe_ctx {scalar_t__ bottom_pipe; struct dc_stream_state* stream; TYPE_3__ plane_res; struct pipe_ctx* next_odm_pipe; TYPE_12__ stream_res; } ;
struct drr_params {scalar_t__ vertical_total_min; scalar_t__ vertical_total_max; int /*<<< orphan*/  member_0; } ;
struct TYPE_23__ {int /*<<< orphan*/  display_color_depth; } ;
struct TYPE_36__ {scalar_t__ v_total_min; scalar_t__ v_total_max; } ;
struct dc_stream_state {TYPE_4__* link; int /*<<< orphan*/  dpms_off; int /*<<< orphan*/  clamping; int /*<<< orphan*/  bit_depth_params; int /*<<< orphan*/  signal; TYPE_10__ timing; TYPE_7__ adjust; int /*<<< orphan*/  apply_seamless_boot_optimization; int /*<<< orphan*/  audio_info; } ;
struct dc_state {int dummy; } ;
struct TYPE_35__ {int /*<<< orphan*/  (* setup_vupdate_interrupt ) (struct pipe_ctx*) ;int /*<<< orphan*/  (* enable_stream_timing ) (struct pipe_ctx*,struct dc_state*,struct dc*) ;int /*<<< orphan*/  (* disable_stream_gating ) (struct dc*,struct pipe_ctx*) ;} ;
struct dc {TYPE_6__ hwss; } ;
struct audio_output {int /*<<< orphan*/  crtc_info; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_38__ {int /*<<< orphan*/  (* dig_connect_to_otg ) (TYPE_13__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* hdmi_audio_setup ) (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dp_audio_setup ) (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_37__ {int /*<<< orphan*/  (* set_static_screen_control ) (TYPE_14__*,unsigned int) ;int /*<<< orphan*/  (* set_drr ) (TYPE_14__*,struct drr_params*) ;} ;
struct TYPE_34__ {int /*<<< orphan*/  (* az_configure ) (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_33__ {int psr_enabled; } ;
struct TYPE_29__ {TYPE_11__* funcs; } ;
struct TYPE_28__ {TYPE_5__* funcs; int /*<<< orphan*/  inst; } ;
struct TYPE_27__ {int /*<<< orphan*/  inst; TYPE_8__* funcs; } ;
struct TYPE_26__ {TYPE_9__* funcs; } ;
struct TYPE_24__ {int /*<<< orphan*/  (* opp_program_fmt ) (TYPE_19__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* opp_set_dyn_expansion ) (TYPE_19__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_SPACE_YCBCR601 ; 
 int DC_OK ; 
 int /*<<< orphan*/  build_audio_output (struct dc_state*,struct pipe_ctx*,struct audio_output*) ; 
 int /*<<< orphan*/  core_link_enable_stream (struct dc_state*,struct pipe_ctx*) ; 
 scalar_t__ dc_is_dp_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_is_virtual_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub10 (TYPE_19__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (TYPE_19__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub12 (TYPE_19__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (TYPE_19__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (struct pipe_ctx*,struct dc_state*,struct dc*) ; 
 int /*<<< orphan*/  stub6 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub7 (TYPE_14__*,struct drr_params*) ; 
 int /*<<< orphan*/  stub8 (TYPE_14__*,unsigned int) ; 
 int /*<<< orphan*/  stub9 (TYPE_13__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum dc_status apply_single_controller_ctx_to_hw(
		struct pipe_ctx *pipe_ctx,
		struct dc_state *context,
		struct dc *dc)
{
	struct dc_stream_state *stream = pipe_ctx->stream;
	struct drr_params params = {0};
	unsigned int event_triggers = 0;
#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	struct pipe_ctx *odm_pipe = pipe_ctx->next_odm_pipe;
#endif

	if (dc->hwss.disable_stream_gating) {
		dc->hwss.disable_stream_gating(dc, pipe_ctx);
	}

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
	/* Do not touch stream timing on seamless boot optimization. */
	if (!pipe_ctx->stream->apply_seamless_boot_optimization)
		dc->hwss.enable_stream_timing(pipe_ctx, context, dc);

	if (dc->hwss.setup_vupdate_interrupt)
		dc->hwss.setup_vupdate_interrupt(pipe_ctx);

	params.vertical_total_min = stream->adjust.v_total_min;
	params.vertical_total_max = stream->adjust.v_total_max;
	if (pipe_ctx->stream_res.tg->funcs->set_drr)
		pipe_ctx->stream_res.tg->funcs->set_drr(
			pipe_ctx->stream_res.tg, &params);

	// DRR should set trigger event to monitor surface update event
	if (stream->adjust.v_total_min != 0 && stream->adjust.v_total_max != 0)
		event_triggers = 0x80;
	if (pipe_ctx->stream_res.tg->funcs->set_static_screen_control)
		pipe_ctx->stream_res.tg->funcs->set_static_screen_control(
				pipe_ctx->stream_res.tg, event_triggers);

	if (!dc_is_virtual_signal(pipe_ctx->stream->signal))
		pipe_ctx->stream_res.stream_enc->funcs->dig_connect_to_otg(
			pipe_ctx->stream_res.stream_enc,
			pipe_ctx->stream_res.tg->inst);

	pipe_ctx->stream_res.opp->funcs->opp_set_dyn_expansion(
			pipe_ctx->stream_res.opp,
			COLOR_SPACE_YCBCR601,
			stream->timing.display_color_depth,
			stream->signal);

	pipe_ctx->stream_res.opp->funcs->opp_program_fmt(
		pipe_ctx->stream_res.opp,
		&stream->bit_depth_params,
		&stream->clamping);
#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	while (odm_pipe) {
		odm_pipe->stream_res.opp->funcs->opp_set_dyn_expansion(
				odm_pipe->stream_res.opp,
				COLOR_SPACE_YCBCR601,
				stream->timing.display_color_depth,
				stream->signal);

		odm_pipe->stream_res.opp->funcs->opp_program_fmt(
				odm_pipe->stream_res.opp,
				&stream->bit_depth_params,
				&stream->clamping);
		odm_pipe = odm_pipe->next_odm_pipe;
	}
#endif

	if (!stream->dpms_off)
		core_link_enable_stream(context, pipe_ctx);

	pipe_ctx->plane_res.scl_data.lb_params.alpha_en = pipe_ctx->bottom_pipe != 0;

	pipe_ctx->stream->link->psr_enabled = false;

	return DC_OK;
}