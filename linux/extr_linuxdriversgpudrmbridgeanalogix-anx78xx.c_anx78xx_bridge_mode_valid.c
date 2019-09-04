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
struct drm_bridge {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_NO_INTERLACE ; 
 int MODE_OK ; 

__attribute__((used)) static enum drm_mode_status
anx78xx_bridge_mode_valid(struct drm_bridge *bridge,
			  const struct drm_display_mode *mode)
{
	if (mode->flags & DRM_MODE_FLAG_INTERLACE)
		return MODE_NO_INTERLACE;

	/* Max 1200p at 5.4 Ghz, one lane */
	if (mode->clock > 154000)
		return MODE_CLOCK_HIGH;

	return MODE_OK;
}