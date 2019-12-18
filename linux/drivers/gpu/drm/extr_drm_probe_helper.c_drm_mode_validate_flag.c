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
struct drm_display_mode {int flags; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int DRM_MODE_FLAG_3D_MASK ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int MODE_NO_DBLESCAN ; 
 int MODE_NO_INTERLACE ; 
 int MODE_NO_STEREO ; 
 int MODE_OK ; 

__attribute__((used)) static enum drm_mode_status
drm_mode_validate_flag(const struct drm_display_mode *mode,
		       int flags)
{
	if ((mode->flags & DRM_MODE_FLAG_INTERLACE) &&
	    !(flags & DRM_MODE_FLAG_INTERLACE))
		return MODE_NO_INTERLACE;

	if ((mode->flags & DRM_MODE_FLAG_DBLSCAN) &&
	    !(flags & DRM_MODE_FLAG_DBLSCAN))
		return MODE_NO_DBLESCAN;

	if ((mode->flags & DRM_MODE_FLAG_3D_MASK) &&
	    !(flags & DRM_MODE_FLAG_3D_MASK))
		return MODE_NO_STEREO;

	return MODE_OK;
}