#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_1__ base; } ;
struct intel_crtc_state {int /*<<< orphan*/  lane_count; int /*<<< orphan*/  lane_lat_optim_mask; int /*<<< orphan*/  cpu_transcoder; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int PORT_A ; 
 int /*<<< orphan*/  TRANSCODER_EDP ; 
 int /*<<< orphan*/  bxt_ddi_phy_calc_lane_lat_optim_mask (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ddi_compute_min_voltage_level (struct drm_i915_private*,struct intel_crtc_state*) ; 
 int intel_dp_compute_config (struct intel_encoder*,struct intel_crtc_state*,struct drm_connector_state*) ; 
 int intel_hdmi_compute_config (struct intel_encoder*,struct intel_crtc_state*,struct drm_connector_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_ddi_compute_config(struct intel_encoder *encoder,
				     struct intel_crtc_state *pipe_config,
				     struct drm_connector_state *conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum port port = encoder->port;
	int ret;

	if (port == PORT_A)
		pipe_config->cpu_transcoder = TRANSCODER_EDP;

	if (intel_crtc_has_type(pipe_config, INTEL_OUTPUT_HDMI))
		ret = intel_hdmi_compute_config(encoder, pipe_config, conn_state);
	else
		ret = intel_dp_compute_config(encoder, pipe_config, conn_state);

	if (IS_GEN9_LP(dev_priv) && ret)
		pipe_config->lane_lat_optim_mask =
			bxt_ddi_phy_calc_lane_lat_optim_mask(pipe_config->lane_count);

	intel_ddi_compute_min_voltage_level(dev_priv, pipe_config);

	return ret;

}