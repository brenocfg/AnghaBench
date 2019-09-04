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
struct drm_display_mode {int flags; int clock; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLSCAN ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_CLOCK_LOW ; 
 int MODE_NO_DBLESCAN ; 
 int MODE_OK ; 

__attribute__((used)) static enum drm_mode_status cdv_intel_crt_mode_valid(struct drm_connector *connector,
				struct drm_display_mode *mode)
{
	if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return MODE_NO_DBLESCAN;

	/* The lowest clock for CDV is 20000KHz */
	if (mode->clock < 20000)
		return MODE_CLOCK_LOW;

	/* The max clock for CDV is 355 instead of 400 */
	if (mode->clock > 355000)
		return MODE_CLOCK_HIGH;

	return MODE_OK;
}