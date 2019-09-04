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
struct drm_display_mode {int hdisplay; int vdisplay; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int MODE_OK ; 
 int MODE_VIRTUAL_X ; 
 int MODE_VIRTUAL_Y ; 

enum drm_mode_status
drm_mode_validate_size(const struct drm_display_mode *mode,
		       int maxX, int maxY)
{
	if (maxX > 0 && mode->hdisplay > maxX)
		return MODE_VIRTUAL_X;

	if (maxY > 0 && mode->vdisplay > maxY)
		return MODE_VIRTUAL_Y;

	return MODE_OK;
}