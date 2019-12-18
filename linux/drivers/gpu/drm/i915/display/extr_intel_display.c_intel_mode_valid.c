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
struct drm_i915_private {int dummy; } ;
struct drm_display_mode {int vscan; int flags; int hdisplay; int hsync_start; int hsync_end; int htotal; int vdisplay; int vsync_start; int vsync_end; int vtotal; } ;
struct drm_device {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int DRM_MODE_FLAG_BCAST ; 
 int DRM_MODE_FLAG_CLKDIV2 ; 
 int DRM_MODE_FLAG_CSYNC ; 
 int DRM_MODE_FLAG_HSKEW ; 
 int DRM_MODE_FLAG_NCSYNC ; 
 int DRM_MODE_FLAG_PCSYNC ; 
 int DRM_MODE_FLAG_PIXMUX ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int MODE_BAD ; 
 int MODE_HSYNC ; 
 int MODE_H_ILLEGAL ; 
 int MODE_NO_VSCAN ; 
 int MODE_OK ; 
 int MODE_V_ILLEGAL ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static enum drm_mode_status
intel_mode_valid(struct drm_device *dev,
		 const struct drm_display_mode *mode)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	int hdisplay_max, htotal_max;
	int vdisplay_max, vtotal_max;

	/*
	 * Can't reject DBLSCAN here because Xorg ddxen can add piles
	 * of DBLSCAN modes to the output's mode list when they detect
	 * the scaling mode property on the connector. And they don't
	 * ask the kernel to validate those modes in any way until
	 * modeset time at which point the client gets a protocol error.
	 * So in order to not upset those clients we silently ignore the
	 * DBLSCAN flag on such connectors. For other connectors we will
	 * reject modes with the DBLSCAN flag in encoder->compute_config().
	 * And we always reject DBLSCAN modes in connector->mode_valid()
	 * as we never want such modes on the connector's mode list.
	 */

	if (mode->vscan > 1)
		return MODE_NO_VSCAN;

	if (mode->flags & DRM_MODE_FLAG_HSKEW)
		return MODE_H_ILLEGAL;

	if (mode->flags & (DRM_MODE_FLAG_CSYNC |
			   DRM_MODE_FLAG_NCSYNC |
			   DRM_MODE_FLAG_PCSYNC))
		return MODE_HSYNC;

	if (mode->flags & (DRM_MODE_FLAG_BCAST |
			   DRM_MODE_FLAG_PIXMUX |
			   DRM_MODE_FLAG_CLKDIV2))
		return MODE_BAD;

	if (INTEL_GEN(dev_priv) >= 9 ||
	    IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv)) {
		hdisplay_max = 8192; /* FDI max 4096 handled elsewhere */
		vdisplay_max = 4096;
		htotal_max = 8192;
		vtotal_max = 8192;
	} else if (INTEL_GEN(dev_priv) >= 3) {
		hdisplay_max = 4096;
		vdisplay_max = 4096;
		htotal_max = 8192;
		vtotal_max = 8192;
	} else {
		hdisplay_max = 2048;
		vdisplay_max = 2048;
		htotal_max = 4096;
		vtotal_max = 4096;
	}

	if (mode->hdisplay > hdisplay_max ||
	    mode->hsync_start > htotal_max ||
	    mode->hsync_end > htotal_max ||
	    mode->htotal > htotal_max)
		return MODE_H_ILLEGAL;

	if (mode->vdisplay > vdisplay_max ||
	    mode->vsync_start > vtotal_max ||
	    mode->vsync_end > vtotal_max ||
	    mode->vtotal > vtotal_max)
		return MODE_V_ILLEGAL;

	return MODE_OK;
}