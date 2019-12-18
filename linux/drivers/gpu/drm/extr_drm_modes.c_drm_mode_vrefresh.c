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
struct drm_display_mode {int vrefresh; unsigned int htotal; unsigned int vtotal; int clock; int flags; int vscan; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 int DRM_MODE_FLAG_INTERLACE ; 

int drm_mode_vrefresh(const struct drm_display_mode *mode)
{
	int refresh = 0;

	if (mode->vrefresh > 0)
		refresh = mode->vrefresh;
	else if (mode->htotal > 0 && mode->vtotal > 0) {
		unsigned int num, den;

		num = mode->clock * 1000;
		den = mode->htotal * mode->vtotal;

		if (mode->flags & DRM_MODE_FLAG_INTERLACE)
			num *= 2;
		if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
			den *= 2;
		if (mode->vscan > 1)
			den *= mode->vscan;

		refresh = DIV_ROUND_CLOSEST(num, den);
	}
	return refresh;
}