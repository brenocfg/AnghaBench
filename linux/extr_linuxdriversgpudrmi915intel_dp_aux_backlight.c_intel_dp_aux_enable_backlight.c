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
typedef  int u8 ;
struct intel_dp {int* edp_dpcd; int /*<<< orphan*/  aux; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  level; } ;
struct TYPE_6__ {TYPE_2__ backlight; } ;
struct intel_connector {TYPE_3__ panel; TYPE_1__* encoder; } ;
struct drm_connector_state {int /*<<< orphan*/  connector; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
#define  DP_EDP_BACKLIGHT_CONTROL_MODE_DPCD 131 
 int DP_EDP_BACKLIGHT_CONTROL_MODE_MASK ; 
#define  DP_EDP_BACKLIGHT_CONTROL_MODE_PRESET 130 
#define  DP_EDP_BACKLIGHT_CONTROL_MODE_PRODUCT 129 
#define  DP_EDP_BACKLIGHT_CONTROL_MODE_PWM 128 
 int DP_EDP_BACKLIGHT_FREQ_AUX_SET_CAP ; 
 int DP_EDP_BACKLIGHT_FREQ_AUX_SET_ENABLE ; 
 int /*<<< orphan*/  DP_EDP_BACKLIGHT_MODE_SET_REGISTER ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_dp_aux_set_backlight (struct drm_connector_state const*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_dp_aux_set_pwm_freq (struct intel_connector*) ; 
 int /*<<< orphan*/  set_aux_backlight_enable (struct intel_dp*,int) ; 
 struct intel_connector* to_intel_connector (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_dp_aux_enable_backlight(const struct intel_crtc_state *crtc_state,
					  const struct drm_connector_state *conn_state)
{
	struct intel_connector *connector = to_intel_connector(conn_state->connector);
	struct intel_dp *intel_dp = enc_to_intel_dp(&connector->encoder->base);
	u8 dpcd_buf, new_dpcd_buf, edp_backlight_mode;

	if (drm_dp_dpcd_readb(&intel_dp->aux,
			DP_EDP_BACKLIGHT_MODE_SET_REGISTER, &dpcd_buf) != 1) {
		DRM_DEBUG_KMS("Failed to read DPCD register 0x%x\n",
			      DP_EDP_BACKLIGHT_MODE_SET_REGISTER);
		return;
	}

	new_dpcd_buf = dpcd_buf;
	edp_backlight_mode = dpcd_buf & DP_EDP_BACKLIGHT_CONTROL_MODE_MASK;

	switch (edp_backlight_mode) {
	case DP_EDP_BACKLIGHT_CONTROL_MODE_PWM:
	case DP_EDP_BACKLIGHT_CONTROL_MODE_PRESET:
	case DP_EDP_BACKLIGHT_CONTROL_MODE_PRODUCT:
		new_dpcd_buf &= ~DP_EDP_BACKLIGHT_CONTROL_MODE_MASK;
		new_dpcd_buf |= DP_EDP_BACKLIGHT_CONTROL_MODE_DPCD;
		break;

	/* Do nothing when it is already DPCD mode */
	case DP_EDP_BACKLIGHT_CONTROL_MODE_DPCD:
	default:
		break;
	}

	if (intel_dp->edp_dpcd[2] & DP_EDP_BACKLIGHT_FREQ_AUX_SET_CAP)
		if (intel_dp_aux_set_pwm_freq(connector))
			new_dpcd_buf |= DP_EDP_BACKLIGHT_FREQ_AUX_SET_ENABLE;

	if (new_dpcd_buf != dpcd_buf) {
		if (drm_dp_dpcd_writeb(&intel_dp->aux,
			DP_EDP_BACKLIGHT_MODE_SET_REGISTER, new_dpcd_buf) < 0) {
			DRM_DEBUG_KMS("Failed to write aux backlight mode\n");
		}
	}

	set_aux_backlight_enable(intel_dp, true);
	intel_dp_aux_set_backlight(conn_state, connector->panel.backlight.level);
}