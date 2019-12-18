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
struct intel_dp {int dummy; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_connector_state {int /*<<< orphan*/  best_encoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  _intel_edp_backlight_on (struct intel_dp*) ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_panel_enable_backlight (struct intel_crtc_state const*,struct drm_connector_state const*) ; 

void intel_edp_backlight_on(const struct intel_crtc_state *crtc_state,
			    const struct drm_connector_state *conn_state)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(conn_state->best_encoder);

	if (!intel_dp_is_edp(intel_dp))
		return;

	DRM_DEBUG_KMS("\n");

	intel_panel_enable_backlight(crtc_state, conn_state);
	_intel_edp_backlight_on(intel_dp);
}