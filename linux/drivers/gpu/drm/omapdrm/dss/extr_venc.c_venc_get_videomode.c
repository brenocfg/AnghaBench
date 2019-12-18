#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_display_mode {int flags; scalar_t__ clock; scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
typedef  enum venc_videomode { ____Placeholder_venc_videomode } venc_videomode ;
struct TYPE_4__ {scalar_t__ clock; scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct TYPE_3__ {scalar_t__ clock; scalar_t__ hdisplay; scalar_t__ vdisplay; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int VENC_MODE_NTSC ; 
 int VENC_MODE_PAL ; 
 int VENC_MODE_UNKNOWN ; 
 TYPE_2__ omap_dss_ntsc_mode ; 
 TYPE_1__ omap_dss_pal_mode ; 

__attribute__((used)) static enum venc_videomode venc_get_videomode(const struct drm_display_mode *mode)
{
	if (!(mode->flags & DRM_MODE_FLAG_INTERLACE))
		return VENC_MODE_UNKNOWN;

	if (mode->clock == omap_dss_pal_mode.clock &&
	    mode->hdisplay == omap_dss_pal_mode.hdisplay &&
	    mode->vdisplay == omap_dss_pal_mode.vdisplay)
		return VENC_MODE_PAL;

	if (mode->clock == omap_dss_ntsc_mode.clock &&
	    mode->hdisplay == omap_dss_ntsc_mode.hdisplay &&
	    mode->vdisplay == omap_dss_ntsc_mode.vdisplay)
		return VENC_MODE_NTSC;

	return VENC_MODE_UNKNOWN;
}