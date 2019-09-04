#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_2__ base; } ;
struct intel_dp {int /*<<< orphan*/  output_reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {scalar_t__ has_audio; int /*<<< orphan*/  lane_count; TYPE_1__ base; } ;
struct intel_crtc {int pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int DP_PORT_EN ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  edp_panel_on (struct intel_dp*) ; 
 int /*<<< orphan*/  edp_panel_vdd_off (struct intel_dp*,int) ; 
 int /*<<< orphan*/  edp_panel_vdd_on (struct intel_dp*) ; 
 struct intel_dp* enc_to_intel_dp (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_audio_codec_enable (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_dp_enable_port (struct intel_dp*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_dp_sink_dpms (struct intel_dp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_start_link_train (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_stop_link_train (struct intel_dp*) ; 
 unsigned int intel_dp_unused_lane_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  pps_lock (struct intel_dp*) ; 
 int /*<<< orphan*/  pps_unlock (struct intel_dp*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_init_panel_power_sequencer (struct intel_encoder*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  vlv_wait_port_ready (struct drm_i915_private*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void intel_enable_dp(struct intel_encoder *encoder,
			    const struct intel_crtc_state *pipe_config,
			    const struct drm_connector_state *conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	struct intel_crtc *crtc = to_intel_crtc(pipe_config->base.crtc);
	uint32_t dp_reg = I915_READ(intel_dp->output_reg);
	enum pipe pipe = crtc->pipe;

	if (WARN_ON(dp_reg & DP_PORT_EN))
		return;

	pps_lock(intel_dp);

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		vlv_init_panel_power_sequencer(encoder, pipe_config);

	intel_dp_enable_port(intel_dp, pipe_config);

	edp_panel_vdd_on(intel_dp);
	edp_panel_on(intel_dp);
	edp_panel_vdd_off(intel_dp, true);

	pps_unlock(intel_dp);

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		unsigned int lane_mask = 0x0;

		if (IS_CHERRYVIEW(dev_priv))
			lane_mask = intel_dp_unused_lane_mask(pipe_config->lane_count);

		vlv_wait_port_ready(dev_priv, dp_to_dig_port(intel_dp),
				    lane_mask);
	}

	intel_dp_sink_dpms(intel_dp, DRM_MODE_DPMS_ON);
	intel_dp_start_link_train(intel_dp);
	intel_dp_stop_link_train(intel_dp);

	if (pipe_config->has_audio) {
		DRM_DEBUG_DRIVER("Enabling DP audio on pipe %c\n",
				 pipe_name(pipe));
		intel_audio_codec_enable(encoder, pipe_config, conn_state);
	}
}