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
struct intel_dp {int dummy; } ;
struct intel_crtc_state {scalar_t__ has_audio; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int PORT_A ; 
 struct intel_dp* enc_to_intel_dp (TYPE_1__*) ; 
 int /*<<< orphan*/  intel_audio_codec_enable (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_dp_stop_link_train (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_ycbcr_420_enable (struct intel_dp*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_edp_backlight_on (struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_edp_drrs_enable (struct intel_dp*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_psr_enable (struct intel_dp*,struct intel_crtc_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_enable_ddi_dp(struct intel_encoder *encoder,
				const struct intel_crtc_state *crtc_state,
				const struct drm_connector_state *conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	enum port port = encoder->port;

	if (port == PORT_A && INTEL_GEN(dev_priv) < 9)
		intel_dp_stop_link_train(intel_dp);

	intel_edp_backlight_on(crtc_state, conn_state);
	intel_psr_enable(intel_dp, crtc_state);
	intel_dp_ycbcr_420_enable(intel_dp, crtc_state);
	intel_edp_drrs_enable(intel_dp, crtc_state);

	if (crtc_state->has_audio)
		intel_audio_codec_enable(encoder, crtc_state, conn_state);
}