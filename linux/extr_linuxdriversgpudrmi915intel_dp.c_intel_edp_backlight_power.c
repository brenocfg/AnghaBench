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
struct intel_connector {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char*) ; 
 int EDP_BLC_ENABLE ; 
 int /*<<< orphan*/  _intel_edp_backlight_off (struct intel_dp*) ; 
 int /*<<< orphan*/  _intel_edp_backlight_on (struct intel_dp*) ; 
 struct intel_dp* intel_attached_dp (int /*<<< orphan*/ *) ; 
 int ironlake_get_pp_control (struct intel_dp*) ; 
 int /*<<< orphan*/  pps_lock (struct intel_dp*) ; 
 int /*<<< orphan*/  pps_unlock (struct intel_dp*) ; 

__attribute__((used)) static void intel_edp_backlight_power(struct intel_connector *connector,
				      bool enable)
{
	struct intel_dp *intel_dp = intel_attached_dp(&connector->base);
	bool is_enabled;

	pps_lock(intel_dp);
	is_enabled = ironlake_get_pp_control(intel_dp) & EDP_BLC_ENABLE;
	pps_unlock(intel_dp);

	if (is_enabled == enable)
		return;

	DRM_DEBUG_KMS("panel power control backlight %s\n",
		      enable ? "enable" : "disable");

	if (enable)
		_intel_edp_backlight_on(intel_dp);
	else
		_intel_edp_backlight_off(intel_dp);
}