#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dp {int link_trained; } ;
struct intel_crtc_state {scalar_t__ has_audio; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_audio_codec_disable (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_dp_sink_dpms (struct intel_dp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_edp_backlight_off (struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_edp_panel_off (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_edp_panel_vdd_on (struct intel_dp*) ; 

__attribute__((used)) static void intel_disable_dp(struct intel_encoder *encoder,
			     const struct intel_crtc_state *old_crtc_state,
			     const struct drm_connector_state *old_conn_state)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);

	intel_dp->link_trained = false;

	if (old_crtc_state->has_audio)
		intel_audio_codec_disable(encoder,
					  old_crtc_state, old_conn_state);

	/* Make sure the panel is off before trying to change the mode. But also
	 * ensure that we have vdd while we switch off the panel. */
	intel_edp_panel_vdd_on(intel_dp);
	intel_edp_backlight_off(old_conn_state);
	intel_dp_sink_dpms(intel_dp, DRM_MODE_DPMS_OFF);
	intel_edp_panel_off(intel_dp);
}