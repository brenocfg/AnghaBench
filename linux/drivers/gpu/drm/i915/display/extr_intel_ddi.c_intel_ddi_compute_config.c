#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_2__ base; } ;
struct TYPE_6__ {int force_thru; scalar_t__ enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {scalar_t__ cpu_transcoder; int /*<<< orphan*/  lane_count; int /*<<< orphan*/  lane_lat_optim_mask; scalar_t__ crc_enabled; TYPE_3__ pch_pfit; TYPE_1__ base; } ;
struct intel_crtc {scalar_t__ pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 scalar_t__ HAS_TRANSCODER_EDP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ PIPE_A ; 
 int PORT_A ; 
 scalar_t__ TRANSCODER_EDP ; 
 int /*<<< orphan*/  bxt_ddi_phy_calc_lane_lat_optim_mask (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ddi_compute_min_voltage_level (struct drm_i915_private*,struct intel_crtc_state*) ; 
 int intel_dp_compute_config (struct intel_encoder*,struct intel_crtc_state*,struct drm_connector_state*) ; 
 int intel_hdmi_compute_config (struct intel_encoder*,struct intel_crtc_state*,struct drm_connector_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_ddi_compute_config(struct intel_encoder *encoder,
				    struct intel_crtc_state *pipe_config,
				    struct drm_connector_state *conn_state)
{
	struct intel_crtc *crtc = to_intel_crtc(pipe_config->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum port port = encoder->port;
	int ret;

	if (HAS_TRANSCODER_EDP(dev_priv) && port == PORT_A)
		pipe_config->cpu_transcoder = TRANSCODER_EDP;

	if (intel_crtc_has_type(pipe_config, INTEL_OUTPUT_HDMI))
		ret = intel_hdmi_compute_config(encoder, pipe_config, conn_state);
	else
		ret = intel_dp_compute_config(encoder, pipe_config, conn_state);
	if (ret)
		return ret;

	if (IS_HASWELL(dev_priv) && crtc->pipe == PIPE_A &&
	    pipe_config->cpu_transcoder == TRANSCODER_EDP)
		pipe_config->pch_pfit.force_thru =
			pipe_config->pch_pfit.enabled ||
			pipe_config->crc_enabled;

	if (IS_GEN9_LP(dev_priv))
		pipe_config->lane_lat_optim_mask =
			bxt_ddi_phy_calc_lane_lat_optim_mask(pipe_config->lane_count);

	intel_ddi_compute_min_voltage_level(dev_priv, pipe_config);

	return 0;
}