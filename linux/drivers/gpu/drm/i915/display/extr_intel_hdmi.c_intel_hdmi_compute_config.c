#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct intel_hdmi {int has_audio; scalar_t__ has_hdmi_sink; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_4__ base; } ;
struct intel_digital_connector_state {scalar_t__ force_audio; scalar_t__ broadcast_rgb; } ;
struct drm_display_mode {int crtc_clock; int flags; int /*<<< orphan*/  picture_aspect_ratio; } ;
struct TYPE_7__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {int has_hdmi_sink; int has_infoframe; int limited_color_range; int pixel_multiplier; int has_pch_encoder; int has_audio; int port_clock; int pipe_bpp; int lane_count; int hdmi_scrambling; int hdmi_high_tmds_clock_ratio; int /*<<< orphan*/  bw_constrained; int /*<<< orphan*/  output_format; TYPE_2__ base; } ;
struct TYPE_8__ {scalar_t__ low_rates; scalar_t__ supported; } ;
struct drm_scdc {TYPE_3__ scrambling; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int /*<<< orphan*/  picture_aspect_ratio; struct drm_connector* connector; } ;
struct TYPE_6__ {struct drm_scdc scdc; } ;
struct TYPE_10__ {TYPE_1__ hdmi; } ;
struct drm_connector {TYPE_5__ display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_MODE_FLAG_DBLCLK ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 int EINVAL ; 
 int /*<<< orphan*/  HAS_DDI (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 scalar_t__ HDMI_AUDIO_AUTO ; 
 scalar_t__ HDMI_AUDIO_OFF_DVI ; 
 scalar_t__ HDMI_AUDIO_ON ; 
 scalar_t__ HDMI_QUANTIZATION_RANGE_LIMITED ; 
 scalar_t__ INTEL_BROADCAST_RGB_AUTO ; 
 scalar_t__ INTEL_BROADCAST_RGB_LIMITED ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_FORMAT_RGB ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ MODE_OK ; 
 scalar_t__ drm_default_rgb_quant_range (struct drm_display_mode*) ; 
 scalar_t__ drm_mode_is_420_only (TYPE_5__*,struct drm_display_mode*) ; 
 struct intel_hdmi* enc_to_intel_hdmi (TYPE_4__*) ; 
 scalar_t__ hdmi_deep_color_possible (struct intel_crtc_state*,int) ; 
 scalar_t__ hdmi_port_clock_valid (struct intel_hdmi*,int,int,int) ; 
 int /*<<< orphan*/  intel_hdmi_compute_avi_infoframe (struct intel_encoder*,struct intel_crtc_state*,struct drm_connector_state*) ; 
 int /*<<< orphan*/  intel_hdmi_compute_drm_infoframe (struct intel_encoder*,struct intel_crtc_state*,struct drm_connector_state*) ; 
 int /*<<< orphan*/  intel_hdmi_compute_gcp_infoframe (struct intel_encoder*,struct intel_crtc_state*,struct drm_connector_state*) ; 
 int /*<<< orphan*/  intel_hdmi_compute_hdmi_infoframe (struct intel_encoder*,struct intel_crtc_state*,struct drm_connector_state*) ; 
 int /*<<< orphan*/  intel_hdmi_compute_spd_infoframe (struct intel_encoder*,struct intel_crtc_state*,struct drm_connector_state*) ; 
 int /*<<< orphan*/  intel_hdmi_ycbcr420_config (struct drm_connector*,struct intel_crtc_state*,int*,int*,int*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_digital_connector_state* to_intel_digital_connector_state (struct drm_connector_state*) ; 

int intel_hdmi_compute_config(struct intel_encoder *encoder,
			      struct intel_crtc_state *pipe_config,
			      struct drm_connector_state *conn_state)
{
	struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(&encoder->base);
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct drm_display_mode *adjusted_mode = &pipe_config->base.adjusted_mode;
	struct drm_connector *connector = conn_state->connector;
	struct drm_scdc *scdc = &connector->display_info.hdmi.scdc;
	struct intel_digital_connector_state *intel_conn_state =
		to_intel_digital_connector_state(conn_state);
	int clock_8bpc = pipe_config->base.adjusted_mode.crtc_clock;
	int clock_10bpc = clock_8bpc * 5 / 4;
	int clock_12bpc = clock_8bpc * 3 / 2;
	int desired_bpp;
	bool force_dvi = intel_conn_state->force_audio == HDMI_AUDIO_OFF_DVI;

	if (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return -EINVAL;

	pipe_config->output_format = INTEL_OUTPUT_FORMAT_RGB;
	pipe_config->has_hdmi_sink = !force_dvi && intel_hdmi->has_hdmi_sink;

	if (pipe_config->has_hdmi_sink)
		pipe_config->has_infoframe = true;

	if (intel_conn_state->broadcast_rgb == INTEL_BROADCAST_RGB_AUTO) {
		/* See CEA-861-E - 5.1 Default Encoding Parameters */
		pipe_config->limited_color_range =
			pipe_config->has_hdmi_sink &&
			drm_default_rgb_quant_range(adjusted_mode) ==
			HDMI_QUANTIZATION_RANGE_LIMITED;
	} else {
		pipe_config->limited_color_range =
			intel_conn_state->broadcast_rgb == INTEL_BROADCAST_RGB_LIMITED;
	}

	if (adjusted_mode->flags & DRM_MODE_FLAG_DBLCLK) {
		pipe_config->pixel_multiplier = 2;
		clock_8bpc *= 2;
		clock_10bpc *= 2;
		clock_12bpc *= 2;
	}

	if (drm_mode_is_420_only(&connector->display_info, adjusted_mode)) {
		if (!intel_hdmi_ycbcr420_config(connector, pipe_config,
						&clock_12bpc, &clock_10bpc,
						&clock_8bpc)) {
			DRM_ERROR("Can't support YCBCR420 output\n");
			return -EINVAL;
		}
	}

	if (HAS_PCH_SPLIT(dev_priv) && !HAS_DDI(dev_priv))
		pipe_config->has_pch_encoder = true;

	if (pipe_config->has_hdmi_sink) {
		if (intel_conn_state->force_audio == HDMI_AUDIO_AUTO)
			pipe_config->has_audio = intel_hdmi->has_audio;
		else
			pipe_config->has_audio =
				intel_conn_state->force_audio == HDMI_AUDIO_ON;
	}

	/*
	 * Note that g4x/vlv don't support 12bpc hdmi outputs. We also need
	 * to check that the higher clock still fits within limits.
	 */
	if (hdmi_deep_color_possible(pipe_config, 12) &&
	    hdmi_port_clock_valid(intel_hdmi, clock_12bpc,
				  true, force_dvi) == MODE_OK) {
		DRM_DEBUG_KMS("picking bpc to 12 for HDMI output\n");
		desired_bpp = 12*3;

		/* Need to adjust the port link by 1.5x for 12bpc. */
		pipe_config->port_clock = clock_12bpc;
	} else if (hdmi_deep_color_possible(pipe_config, 10) &&
		   hdmi_port_clock_valid(intel_hdmi, clock_10bpc,
					 true, force_dvi) == MODE_OK) {
		DRM_DEBUG_KMS("picking bpc to 10 for HDMI output\n");
		desired_bpp = 10 * 3;

		/* Need to adjust the port link by 1.25x for 10bpc. */
		pipe_config->port_clock = clock_10bpc;
	} else {
		DRM_DEBUG_KMS("picking bpc to 8 for HDMI output\n");
		desired_bpp = 8*3;

		pipe_config->port_clock = clock_8bpc;
	}

	if (!pipe_config->bw_constrained) {
		DRM_DEBUG_KMS("forcing pipe bpp to %i for HDMI\n", desired_bpp);
		pipe_config->pipe_bpp = desired_bpp;
	}

	if (hdmi_port_clock_valid(intel_hdmi, pipe_config->port_clock,
				  false, force_dvi) != MODE_OK) {
		DRM_DEBUG_KMS("unsupported HDMI clock, rejecting mode\n");
		return -EINVAL;
	}

	/* Set user selected PAR to incoming mode's member */
	adjusted_mode->picture_aspect_ratio = conn_state->picture_aspect_ratio;

	pipe_config->lane_count = 4;

	if (scdc->scrambling.supported && (INTEL_GEN(dev_priv) >= 10 ||
					   IS_GEMINILAKE(dev_priv))) {
		if (scdc->scrambling.low_rates)
			pipe_config->hdmi_scrambling = true;

		if (pipe_config->port_clock > 340000) {
			pipe_config->hdmi_scrambling = true;
			pipe_config->hdmi_high_tmds_clock_ratio = true;
		}
	}

	intel_hdmi_compute_gcp_infoframe(encoder, pipe_config, conn_state);

	if (!intel_hdmi_compute_avi_infoframe(encoder, pipe_config, conn_state)) {
		DRM_DEBUG_KMS("bad AVI infoframe\n");
		return -EINVAL;
	}

	if (!intel_hdmi_compute_spd_infoframe(encoder, pipe_config, conn_state)) {
		DRM_DEBUG_KMS("bad SPD infoframe\n");
		return -EINVAL;
	}

	if (!intel_hdmi_compute_hdmi_infoframe(encoder, pipe_config, conn_state)) {
		DRM_DEBUG_KMS("bad HDMI infoframe\n");
		return -EINVAL;
	}

	if (!intel_hdmi_compute_drm_infoframe(encoder, pipe_config, conn_state)) {
		DRM_DEBUG_KMS("bad DRM infoframe\n");
		return -EINVAL;
	}

	return 0;
}