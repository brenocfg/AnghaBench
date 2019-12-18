#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct intel_lspcon {scalar_t__ active; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_6__ base; } ;
struct intel_dp {int has_audio; int /*<<< orphan*/  desc; struct intel_connector* attached_connector; } ;
struct intel_digital_connector_state {scalar_t__ force_audio; } ;
struct TYPE_9__ {int compressed_bpp; scalar_t__ compression_enable; } ;
struct drm_display_mode {int flags; int /*<<< orphan*/  crtc_clock; } ;
struct TYPE_8__ {int /*<<< orphan*/  crtc; struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {int has_pch_encoder; int has_drrs; int has_audio; int /*<<< orphan*/  fec_enable; int /*<<< orphan*/  dp_m2_n2; int /*<<< orphan*/  port_clock; int /*<<< orphan*/  lane_count; int /*<<< orphan*/  dp_m_n; int /*<<< orphan*/  pipe_bpp; TYPE_2__ dsc_params; int /*<<< orphan*/  limited_color_range; int /*<<< orphan*/  output_format; TYPE_1__ base; } ;
struct intel_crtc {int dummy; } ;
struct TYPE_12__ {TYPE_4__* downclock_mode; scalar_t__ fixed_mode; } ;
struct intel_connector {TYPE_5__ panel; int /*<<< orphan*/  base; } ;
struct TYPE_10__ {scalar_t__ type; } ;
struct drm_i915_private {TYPE_3__ drrs; } ;
struct drm_connector_state {int /*<<< orphan*/  scaling_mode; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_11__ {int /*<<< orphan*/  clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DPCD_QUIRK_CONSTANT_N ; 
 int DRM_MODE_FLAG_DBLCLK ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int EINVAL ; 
 int /*<<< orphan*/  HAS_DDI (struct drm_i915_private*) ; 
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 scalar_t__ HDMI_AUDIO_AUTO ; 
 scalar_t__ HDMI_AUDIO_ON ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_FORMAT_RGB ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 int PORT_A ; 
 scalar_t__ SEAMLESS_DRRS_SUPPORT ; 
 int drm_dp_has_quirk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct intel_dp* enc_to_intel_dp (TYPE_6__*) ; 
 struct intel_lspcon* enc_to_intel_lspcon (TYPE_6__*) ; 
 int intel_dp_compute_link_config (struct intel_encoder*,struct intel_crtc_state*,struct drm_connector_state*) ; 
 scalar_t__ intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_limited_color_range (struct intel_crtc_state*,struct drm_connector_state*) ; 
 int intel_dp_output_bpp (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_set_clock (struct intel_encoder*,struct intel_crtc_state*) ; 
 int intel_dp_ycbcr420_config (struct intel_dp*,int /*<<< orphan*/ *,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_fixed_panel_mode (scalar_t__,struct drm_display_mode*) ; 
 int /*<<< orphan*/  intel_gmch_panel_fitting (struct intel_crtc*,struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_link_compute_m_n (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pch_panel_fitting (struct intel_crtc*,struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_psr_compute_config (struct intel_dp*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  lspcon_ycbcr420_config (int /*<<< orphan*/ *,struct intel_crtc_state*) ; 
 int skl_update_scaler_crtc (struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 struct intel_digital_connector_state* to_intel_digital_connector_state (struct drm_connector_state*) ; 

int
intel_dp_compute_config(struct intel_encoder *encoder,
			struct intel_crtc_state *pipe_config,
			struct drm_connector_state *conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct drm_display_mode *adjusted_mode = &pipe_config->base.adjusted_mode;
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	struct intel_lspcon *lspcon = enc_to_intel_lspcon(&encoder->base);
	enum port port = encoder->port;
	struct intel_crtc *intel_crtc = to_intel_crtc(pipe_config->base.crtc);
	struct intel_connector *intel_connector = intel_dp->attached_connector;
	struct intel_digital_connector_state *intel_conn_state =
		to_intel_digital_connector_state(conn_state);
	bool constant_n = drm_dp_has_quirk(&intel_dp->desc,
					   DP_DPCD_QUIRK_CONSTANT_N);
	int ret = 0, output_bpp;

	if (HAS_PCH_SPLIT(dev_priv) && !HAS_DDI(dev_priv) && port != PORT_A)
		pipe_config->has_pch_encoder = true;

	pipe_config->output_format = INTEL_OUTPUT_FORMAT_RGB;
	if (lspcon->active)
		lspcon_ycbcr420_config(&intel_connector->base, pipe_config);
	else
		ret = intel_dp_ycbcr420_config(intel_dp, &intel_connector->base,
					       pipe_config);

	if (ret)
		return ret;

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
			ret = skl_update_scaler_crtc(pipe_config);
			if (ret)
				return ret;
		}

		if (HAS_GMCH(dev_priv))
			intel_gmch_panel_fitting(intel_crtc, pipe_config,
						 conn_state->scaling_mode);
		else
			intel_pch_panel_fitting(intel_crtc, pipe_config,
						conn_state->scaling_mode);
	}

	if (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return -EINVAL;

	if (HAS_GMCH(dev_priv) &&
	    adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE)
		return -EINVAL;

	if (adjusted_mode->flags & DRM_MODE_FLAG_DBLCLK)
		return -EINVAL;

	ret = intel_dp_compute_link_config(encoder, pipe_config, conn_state);
	if (ret < 0)
		return ret;

	pipe_config->limited_color_range =
		intel_dp_limited_color_range(pipe_config, conn_state);

	if (pipe_config->dsc_params.compression_enable)
		output_bpp = pipe_config->dsc_params.compressed_bpp;
	else
		output_bpp = intel_dp_output_bpp(pipe_config, pipe_config->pipe_bpp);

	intel_link_compute_m_n(output_bpp,
			       pipe_config->lane_count,
			       adjusted_mode->crtc_clock,
			       pipe_config->port_clock,
			       &pipe_config->dp_m_n,
			       constant_n, pipe_config->fec_enable);

	if (intel_connector->panel.downclock_mode != NULL &&
		dev_priv->drrs.type == SEAMLESS_DRRS_SUPPORT) {
			pipe_config->has_drrs = true;
			intel_link_compute_m_n(output_bpp,
					       pipe_config->lane_count,
					       intel_connector->panel.downclock_mode->clock,
					       pipe_config->port_clock,
					       &pipe_config->dp_m2_n2,
					       constant_n, pipe_config->fec_enable);
	}

	if (!HAS_DDI(dev_priv))
		intel_dp_set_clock(encoder, pipe_config);

	intel_psr_compute_config(intel_dp, pipe_config);

	return 0;
}