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
struct drm_display_mode {int vscan; int flags; } ;
struct drm_crtc {int dummy; } ;
struct armada_crtc {TYPE_1__* variant; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_2__ {int /*<<< orphan*/  has_spu_adv_reg; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_BCAST ; 
 int DRM_MODE_FLAG_CLKDIV2 ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 int DRM_MODE_FLAG_HSKEW ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int DRM_MODE_FLAG_PIXMUX ; 
 int MODE_BAD ; 
 int MODE_H_ILLEGAL ; 
 int MODE_NO_DBLESCAN ; 
 int MODE_NO_INTERLACE ; 
 int MODE_NO_VSCAN ; 
 int MODE_OK ; 
 struct armada_crtc* drm_to_armada_crtc (struct drm_crtc*) ; 

__attribute__((used)) static enum drm_mode_status armada_drm_crtc_mode_valid(struct drm_crtc *crtc,
	const struct drm_display_mode *mode)
{
	struct armada_crtc *dcrtc = drm_to_armada_crtc(crtc);

	if (mode->vscan > 1)
		return MODE_NO_VSCAN;

	if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return MODE_NO_DBLESCAN;

	if (mode->flags & DRM_MODE_FLAG_HSKEW)
		return MODE_H_ILLEGAL;

	/* We can't do interlaced modes if we don't have the SPU_ADV_REG */
	if (!dcrtc->variant->has_spu_adv_reg &&
	    mode->flags & DRM_MODE_FLAG_INTERLACE)
		return MODE_NO_INTERLACE;

	if (mode->flags & (DRM_MODE_FLAG_BCAST | DRM_MODE_FLAG_PIXMUX |
			   DRM_MODE_FLAG_CLKDIV2))
		return MODE_BAD;

	return MODE_OK;
}