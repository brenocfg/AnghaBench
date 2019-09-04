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
struct drm_display_mode {int type; int flags; scalar_t__ clock; scalar_t__ hdisplay; scalar_t__ hsync_start; scalar_t__ hsync_end; scalar_t__ htotal; scalar_t__ vdisplay; scalar_t__ vsync_start; scalar_t__ vsync_end; scalar_t__ vtotal; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int DRM_MODE_FLAG_3D_MASK ; 
 int DRM_MODE_FLAG_3D_MAX ; 
 int DRM_MODE_FLAG_ALL ; 
 int DRM_MODE_TYPE_ALL ; 
 int MODE_BAD ; 
 int MODE_CLOCK_LOW ; 
 int MODE_H_ILLEGAL ; 
 int MODE_OK ; 
 int MODE_V_ILLEGAL ; 

__attribute__((used)) static enum drm_mode_status
drm_mode_validate_basic(const struct drm_display_mode *mode)
{
	if (mode->type & ~DRM_MODE_TYPE_ALL)
		return MODE_BAD;

	if (mode->flags & ~DRM_MODE_FLAG_ALL)
		return MODE_BAD;

	if ((mode->flags & DRM_MODE_FLAG_3D_MASK) > DRM_MODE_FLAG_3D_MAX)
		return MODE_BAD;

	if (mode->clock == 0)
		return MODE_CLOCK_LOW;

	if (mode->hdisplay == 0 ||
	    mode->hsync_start < mode->hdisplay ||
	    mode->hsync_end < mode->hsync_start ||
	    mode->htotal < mode->hsync_end)
		return MODE_H_ILLEGAL;

	if (mode->vdisplay == 0 ||
	    mode->vsync_start < mode->vdisplay ||
	    mode->vsync_end < mode->vsync_start ||
	    mode->vtotal < mode->vsync_end)
		return MODE_V_ILLEGAL;

	return MODE_OK;
}