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
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_5__ base; } ;
struct intel_dp {int has_audio; int /*<<< orphan*/  desc; struct intel_connector* attached_connector; } ;
struct intel_digital_connector_state {scalar_t__ force_audio; scalar_t__ broadcast_rgb; } ;
struct drm_display_mode {int flags; int /*<<< orphan*/  crtc_clock; } ;
struct TYPE_6__ {int /*<<< orphan*/  crtc; struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {int has_pch_encoder; int has_drrs; int has_audio; int limited_color_range; int pipe_bpp; int /*<<< orphan*/  dp_m2_n2; int /*<<< orphan*/  port_clock; int /*<<< orphan*/  lane_count; int /*<<< orphan*/  dp_m_n; TYPE_1__ base; } ;
struct intel_crtc {int dummy; } ;
struct TYPE_9__ {TYPE_3__* downclock_mode; scalar_t__ fixed_mode; } ;
struct intel_connector {TYPE_4__ panel; } ;
struct TYPE_7__ {scalar_t__ type; } ;
struct drm_i915_private {TYPE_2__ drrs; } ;
struct drm_connector_state {int /*<<< orphan*/  scaling_mode; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_8__ {int /*<<< orphan*/  clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DPCD_QUIRK_LIMITED_M_N ; 
 int DRM_MODE_FLAG_DBLCLK ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  HAS_DDI (struct drm_i915_private*) ; 
 scalar_t__ HAS_GMCH_DISPLAY (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 scalar_t__ HDMI_AUDIO_AUTO ; 
 scalar_t__ HDMI_AUDIO_ON ; 
 scalar_t__ HDMI_QUANTIZATION_RANGE_LIMITED ; 
 scalar_t__ INTEL_BROADCAST_RGB_AUTO ; 
 scalar_t__ INTEL_BROADCAST_RGB_LIMITED ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 int PORT_A ; 
 scalar_t__ SEAMLESS_DRRS_SUPPORT ; 
 scalar_t__ drm_default_rgb_quant_range (struct drm_display_mode*) ; 
 int drm_dp_has_quirk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct intel_dp* enc_to_intel_dp (TYPE_5__*) ; 
 int /*<<< orphan*/  intel_dp_compute_link_config (struct intel_encoder*,struct intel_crtc_state*) ; 
 scalar_t__ intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_set_clock (struct intel_encoder*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_fixed_panel_mode (scalar_t__,struct drm_display_mode*) ; 
 int /*<<< orphan*/  intel_gmch_panel_fitting (struct intel_crtc*,struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_link_compute_m_n (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  intel_pch_panel_fitting (struct intel_crtc*,struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_psr_compute_config (struct intel_dp*,struct intel_crtc_state*) ; 
 int skl_update_scaler_crtc (struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 struct intel_digital_connector_state* to_intel_digital_connector_state (struct drm_connector_state*) ; 

bool
intel_dp_compute_config(struct intel_encoder *encoder,
			struct intel_crtc_state *pipe_config,
			struct drm_connector_state *conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct drm_display_mode *adjusted_mode = &pipe_config->base.adjusted_mode;
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	enum port port = encoder->port;
	struct intel_crtc *intel_crtc = to_intel_crtc(pipe_config->base.crtc);
	struct intel_connector *intel_connector = intel_dp->attached_connector;
	struct intel_digital_connector_state *intel_conn_state =
		to_intel_digital_connector_state(conn_state);
	bool reduce_m_n = drm_dp_has_quirk(&intel_dp->desc,
					   DP_DPCD_QUIRK_LIMITED_M_N);

	if (HAS_PCH_SPLIT(dev_priv) && !HAS_DDI(dev_priv) && port != PORT_A)
		pipe_config->has_pch_encoder = true;

	pipe_config->has_drrs = false;
	if (IS_G4X(dev_priv) || port == PORT_A)
		pipe_config->has_audio = false;
	else if (intel_conn_state->force_audio == HDMI_AUDIO_AUTO)
		pipe_config->has_audio = intel_dp->has_audio;
	else
		pipe_config->has_audio = intel_conn_state->force_audio == HDMI_AUDIO_ON;

	if (intel_dp_is_edp(intel_dp) && intel_connector->panel.fixed_mode) {
		intel_fixed_panel_mode(intel_connector->panel.fixed_mode,
				       adjusted_mode);

		if (INTEL_GEN(dev_priv) >= 9) {
			int ret;

			ret = skl_update_scaler_crtc(pipe_config);
			if (ret)
				return ret;
		}

		if (HAS_GMCH_DISPLAY(dev_priv))
			intel_gmch_panel_fitting(intel_crtc, pipe_config,
						 conn_state->scaling_mode);
		else
			intel_pch_panel_fitting(intel_crtc, pipe_config,
						conn_state->scaling_mode);
	}

	if (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return false;

	if (HAS_GMCH_DISPLAY(dev_priv) &&
	    adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE)
		return false;

	if (adjusted_mode->flags & DRM_MODE_FLAG_DBLCLK)
		return false;

	if (!intel_dp_compute_link_config(encoder, pipe_config))
		return false;

	if (intel_conn_state->broadcast_rgb == INTEL_BROADCAST_RGB_AUTO) {
		/*
		 * See:
		 * CEA-861-E - 5.1 Default Encoding Parameters
		 * VESA DisplayPort Ver.1.2a - 5.1.1.1 Video Colorimetry
		 */
		pipe_config->limited_color_range =
			pipe_config->pipe_bpp != 18 &&
			drm_default_rgb_quant_range(adjusted_mode) ==
			HDMI_QUANTIZATION_RANGE_LIMITED;
	} else {
		pipe_config->limited_color_range =
			intel_conn_state->broadcast_rgb == INTEL_BROADCAST_RGB_LIMITED;
	}

	intel_link_compute_m_n(pipe_config->pipe_bpp, pipe_config->lane_count,
			       adjusted_mode->crtc_clock,
			       pipe_config->port_clock,
			       &pipe_config->dp_m_n,
			       reduce_m_n);

	if (intel_connector->panel.downclock_mode != NULL &&
		dev_priv->drrs.type == SEAMLESS_DRRS_SUPPORT) {
			pipe_config->has_drrs = true;
			intel_link_compute_m_n(pipe_config->pipe_bpp,
					       pipe_config->lane_count,
					       intel_connector->panel.downclock_mode->clock,
					       pipe_config->port_clock,
					       &pipe_config->dp_m2_n2,
					       reduce_m_n);
	}

	if (!HAS_DDI(dev_priv))
		intel_dp_set_clock(encoder, pipe_config);

	intel_psr_compute_config(intel_dp, pipe_config);

	return true;
}