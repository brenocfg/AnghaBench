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
struct intel_dp {int* edp_dpcd; } ;
struct intel_connector {TYPE_1__* encoder; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int DP_EDP_BACKLIGHT_BRIGHTNESS_AUX_SET_CAP ; 
 int DP_EDP_BACKLIGHT_BRIGHTNESS_PWM_PIN_CAP ; 
 int DP_EDP_TCON_BACKLIGHT_ADJUSTMENT_CAP ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
intel_dp_aux_display_control_capable(struct intel_connector *connector)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&connector->encoder->base);

	/* Check the eDP Display control capabilities registers to determine if
	 * the panel can support backlight control over the aux channel
	 */
	if (intel_dp->edp_dpcd[1] & DP_EDP_TCON_BACKLIGHT_ADJUSTMENT_CAP &&
	    (intel_dp->edp_dpcd[2] & DP_EDP_BACKLIGHT_BRIGHTNESS_AUX_SET_CAP) &&
	    !(intel_dp->edp_dpcd[2] & DP_EDP_BACKLIGHT_BRIGHTNESS_PWM_PIN_CAP)) {
		DRM_DEBUG_KMS("AUX Backlight Control Supported!\n");
		return true;
	}
	return false;
}