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
struct drm_display_mode {int clock; int flags; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLSCAN ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_CLOCK_LOW ; 
 int MODE_NO_DBLESCAN ; 
 int MODE_OK ; 

__attribute__((used)) static enum drm_mode_status oaktrail_hdmi_mode_valid(struct drm_connector *connector,
				struct drm_display_mode *mode)
{
	if (mode->clock > 165000)
		return MODE_CLOCK_HIGH;
	if (mode->clock < 20000)
		return MODE_CLOCK_LOW;

	if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return MODE_NO_DBLESCAN;

	return MODE_OK;
}