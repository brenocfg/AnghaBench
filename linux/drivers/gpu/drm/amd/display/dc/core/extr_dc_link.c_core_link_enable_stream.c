#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_23__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_15__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {TYPE_13__* tg; TYPE_14__* stream_enc; int /*<<< orphan*/ * audio; } ;
struct pipe_ctx {struct dc_stream_state* stream; TYPE_12__ stream_res; } ;
struct TYPE_30__ {scalar_t__ DSC; } ;
struct TYPE_29__ {scalar_t__ timing_3d_format; TYPE_1__ flags; } ;
struct dc_stream_state {scalar_t__ signal; int apply_edp_fast_boot_optimization; int dpms_off; TYPE_9__* link; TYPE_15__ timing; scalar_t__ apply_seamless_boot_optimization; int /*<<< orphan*/  phy_pix_clk; int /*<<< orphan*/  output_color_space; TYPE_2__* ctx; } ;
struct dc_state {int dummy; } ;
struct TYPE_24__ {int /*<<< orphan*/  (* unblank_stream ) (struct pipe_ctx*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* enable_stream ) (struct pipe_ctx*) ;int /*<<< orphan*/  (* enable_audio_stream ) (struct pipe_ctx*) ;int /*<<< orphan*/  (* update_info_frame ) (struct pipe_ctx*) ;} ;
struct dc {TYPE_10__ hwss; TYPE_8__* ctx; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_34__ {int /*<<< orphan*/  SST_SPLIT_SDP_CAP; } ;
struct TYPE_35__ {TYPE_4__ bits; } ;
struct TYPE_36__ {TYPE_5__ dprx_feature; } ;
struct TYPE_39__ {int link_state_valid; int /*<<< orphan*/  cur_link_settings; int /*<<< orphan*/  link_index; TYPE_6__ dpcd_caps; TYPE_23__* link_enc; } ;
struct TYPE_38__ {int /*<<< orphan*/  dce_environment; } ;
struct TYPE_37__ {int /*<<< orphan*/  (* lvds_set_stream_attribute ) (TYPE_14__*,TYPE_15__*) ;int /*<<< orphan*/  (* dvi_set_stream_attribute ) (TYPE_14__*,TYPE_15__*,int) ;int /*<<< orphan*/  (* hdmi_set_stream_attribute ) (TYPE_14__*,TYPE_15__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dp_set_stream_attribute ) (TYPE_14__*,TYPE_15__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* setup_stereo_sync ) (TYPE_14__*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_33__ {int /*<<< orphan*/  (* setup ) (TYPE_23__*,scalar_t__) ;} ;
struct TYPE_32__ {int /*<<< orphan*/  logger; struct dc* dc; } ;
struct TYPE_31__ {TYPE_3__* funcs; } ;
struct TYPE_28__ {TYPE_7__* funcs; } ;
struct TYPE_27__ {TYPE_11__* funcs; int /*<<< orphan*/  inst; } ;
struct TYPE_25__ {int /*<<< orphan*/  (* set_test_pattern ) (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  COLOR_DEPTH_UNDEFINED ; 
 int /*<<< orphan*/  CONTROLLER_DP_TEST_PATTERN_VIDEOMODE ; 
 int DC_FAIL_DP_LINK_TRAINING ; 
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_WARNING (char*,int /*<<< orphan*/ ,int) ; 
 int DC_OK ; 
 int /*<<< orphan*/  IS_FPGA_MAXIMUS_DC (int /*<<< orphan*/ ) ; 
 scalar_t__ SIGNAL_TYPE_DISPLAY_PORT_MST ; 
 scalar_t__ SIGNAL_TYPE_DVI_DUAL_LINK ; 
 scalar_t__ SIGNAL_TYPE_EDP ; 
 scalar_t__ TIMING_3D_FORMAT_NONE ; 
 int /*<<< orphan*/  allocate_mst_payload (struct pipe_ctx*) ; 
 scalar_t__ dc_is_dp_signal (scalar_t__) ; 
 scalar_t__ dc_is_dvi_signal (scalar_t__) ; 
 scalar_t__ dc_is_hdmi_tmds_signal (scalar_t__) ; 
 scalar_t__ dc_is_lvds_signal (scalar_t__) ; 
 scalar_t__ dc_is_virtual_signal (scalar_t__) ; 
 int /*<<< orphan*/  dp_set_dsc_enable (struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  dp_set_dsc_pps_sdp (struct pipe_ctx*,int) ; 
 int enable_link (struct dc_state*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  enable_stream_features (struct pipe_ctx*) ; 
 int /*<<< orphan*/  resource_build_info_frame (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub1 (TYPE_23__*,scalar_t__) ; 
 int /*<<< orphan*/  stub10 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub11 (struct pipe_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_14__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_14__*,TYPE_15__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_14__*,TYPE_15__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_14__*,TYPE_15__*,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_14__*,TYPE_15__*) ; 
 int /*<<< orphan*/  stub7 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub8 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub9 (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void core_link_enable_stream(
		struct dc_state *state,
		struct pipe_ctx *pipe_ctx)
{
	struct dc *core_dc = pipe_ctx->stream->ctx->dc;
	struct dc_stream_state *stream = pipe_ctx->stream;
	enum dc_status status;
	DC_LOGGER_INIT(pipe_ctx->stream->ctx->logger);

	if (!dc_is_virtual_signal(pipe_ctx->stream->signal)) {
		stream->link->link_enc->funcs->setup(
			stream->link->link_enc,
			pipe_ctx->stream->signal);
		pipe_ctx->stream_res.stream_enc->funcs->setup_stereo_sync(
			pipe_ctx->stream_res.stream_enc,
			pipe_ctx->stream_res.tg->inst,
			stream->timing.timing_3d_format != TIMING_3D_FORMAT_NONE);
	}

	if (dc_is_dp_signal(pipe_ctx->stream->signal))
		pipe_ctx->stream_res.stream_enc->funcs->dp_set_stream_attribute(
			pipe_ctx->stream_res.stream_enc,
			&stream->timing,
			stream->output_color_space,
			stream->link->dpcd_caps.dprx_feature.bits.SST_SPLIT_SDP_CAP);

	if (dc_is_hdmi_tmds_signal(pipe_ctx->stream->signal))
		pipe_ctx->stream_res.stream_enc->funcs->hdmi_set_stream_attribute(
			pipe_ctx->stream_res.stream_enc,
			&stream->timing,
			stream->phy_pix_clk,
			pipe_ctx->stream_res.audio != NULL);

	pipe_ctx->stream->link->link_state_valid = true;

	if (dc_is_dvi_signal(pipe_ctx->stream->signal))
		pipe_ctx->stream_res.stream_enc->funcs->dvi_set_stream_attribute(
			pipe_ctx->stream_res.stream_enc,
			&stream->timing,
			(pipe_ctx->stream->signal == SIGNAL_TYPE_DVI_DUAL_LINK) ?
			true : false);

	if (dc_is_lvds_signal(pipe_ctx->stream->signal))
		pipe_ctx->stream_res.stream_enc->funcs->lvds_set_stream_attribute(
			pipe_ctx->stream_res.stream_enc,
			&stream->timing);

	if (!IS_FPGA_MAXIMUS_DC(core_dc->ctx->dce_environment)) {
		bool apply_edp_fast_boot_optimization =
			pipe_ctx->stream->apply_edp_fast_boot_optimization;

		pipe_ctx->stream->apply_edp_fast_boot_optimization = false;

		resource_build_info_frame(pipe_ctx);
		core_dc->hwss.update_info_frame(pipe_ctx);

		/* Do not touch link on seamless boot optimization. */
		if (pipe_ctx->stream->apply_seamless_boot_optimization) {
			pipe_ctx->stream->dpms_off = false;
			return;
		}

		/* eDP lit up by bios already, no need to enable again. */
		if (pipe_ctx->stream->signal == SIGNAL_TYPE_EDP &&
					apply_edp_fast_boot_optimization) {
			pipe_ctx->stream->dpms_off = false;
			return;
		}

		if (pipe_ctx->stream->dpms_off)
			return;

		status = enable_link(state, pipe_ctx);

		if (status != DC_OK) {
			DC_LOG_WARNING("enabling link %u failed: %d\n",
			pipe_ctx->stream->link->link_index,
			status);

			/* Abort stream enable *unless* the failure was due to
			 * DP link training - some DP monitors will recover and
			 * show the stream anyway. But MST displays can't proceed
			 * without link training.
			 */
			if (status != DC_FAIL_DP_LINK_TRAINING ||
					pipe_ctx->stream->signal == SIGNAL_TYPE_DISPLAY_PORT_MST) {
				BREAK_TO_DEBUGGER();
				return;
			}
		}

		core_dc->hwss.enable_audio_stream(pipe_ctx);

		/* turn off otg test pattern if enable */
		if (pipe_ctx->stream_res.tg->funcs->set_test_pattern)
			pipe_ctx->stream_res.tg->funcs->set_test_pattern(pipe_ctx->stream_res.tg,
					CONTROLLER_DP_TEST_PATTERN_VIDEOMODE,
					COLOR_DEPTH_UNDEFINED);

#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
		if (pipe_ctx->stream->timing.flags.DSC) {
			if (dc_is_dp_signal(pipe_ctx->stream->signal) ||
					dc_is_virtual_signal(pipe_ctx->stream->signal))
				dp_set_dsc_enable(pipe_ctx, true);
		}
#endif
		core_dc->hwss.enable_stream(pipe_ctx);

#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
		/* Set DPS PPS SDP (AKA "info frames") */
		if (pipe_ctx->stream->timing.flags.DSC) {
			if (dc_is_dp_signal(pipe_ctx->stream->signal) ||
					dc_is_virtual_signal(pipe_ctx->stream->signal))
				dp_set_dsc_pps_sdp(pipe_ctx, true);
		}
#endif

		if (pipe_ctx->stream->signal == SIGNAL_TYPE_DISPLAY_PORT_MST)
			allocate_mst_payload(pipe_ctx);

		core_dc->hwss.unblank_stream(pipe_ctx,
			&pipe_ctx->stream->link->cur_link_settings);

		if (dc_is_dp_signal(pipe_ctx->stream->signal))
			enable_stream_features(pipe_ctx);
	}
#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	else { // if (IS_FPGA_MAXIMUS_DC(core_dc->ctx->dce_environment))
		if (dc_is_dp_signal(pipe_ctx->stream->signal) ||
				dc_is_virtual_signal(pipe_ctx->stream->signal))
			dp_set_dsc_enable(pipe_ctx, true);

	}
#endif
}