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
struct intel_dp {int dummy; } ;
struct TYPE_2__ {struct drm_display_mode* fixed_mode; } ;
struct intel_connector {TYPE_1__ panel; } ;
struct drm_display_mode {int clock; int flags; scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLCLK ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_CLOCK_LOW ; 
 int MODE_H_ILLEGAL ; 
 int MODE_NO_DBLESCAN ; 
 int MODE_OK ; 
 int MODE_PANEL ; 
 struct intel_dp* intel_attached_dp (struct drm_connector*) ; 
 int intel_dp_downstream_max_dotclock (struct intel_dp*) ; 
 scalar_t__ intel_dp_is_edp (struct intel_dp*) ; 
 int intel_dp_link_required (int,int) ; 
 int intel_dp_max_data_rate (int,int) ; 
 int intel_dp_max_lane_count (struct intel_dp*) ; 
 int intel_dp_max_link_rate (struct intel_dp*) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static enum drm_mode_status
intel_dp_mode_valid(struct drm_connector *connector,
		    struct drm_display_mode *mode)
{
	struct intel_dp *intel_dp = intel_attached_dp(connector);
	struct intel_connector *intel_connector = to_intel_connector(connector);
	struct drm_display_mode *fixed_mode = intel_connector->panel.fixed_mode;
	int target_clock = mode->clock;
	int max_rate, mode_rate, max_lanes, max_link_clock;
	int max_dotclk;

	if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return MODE_NO_DBLESCAN;

	max_dotclk = intel_dp_downstream_max_dotclock(intel_dp);

	if (intel_dp_is_edp(intel_dp) && fixed_mode) {
		if (mode->hdisplay > fixed_mode->hdisplay)
			return MODE_PANEL;

		if (mode->vdisplay > fixed_mode->vdisplay)
			return MODE_PANEL;

		target_clock = fixed_mode->clock;
	}

	max_link_clock = intel_dp_max_link_rate(intel_dp);
	max_lanes = intel_dp_max_lane_count(intel_dp);

	max_rate = intel_dp_max_data_rate(max_link_clock, max_lanes);
	mode_rate = intel_dp_link_required(target_clock, 18);

	if (mode_rate > max_rate || target_clock > max_dotclk)
		return MODE_CLOCK_HIGH;

	if (mode->clock < 10000)
		return MODE_CLOCK_LOW;

	if (mode->flags & DRM_MODE_FLAG_DBLCLK)
		return MODE_H_ILLEGAL;

	return MODE_OK;
}