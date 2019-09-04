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
struct tilcdc_crtc {int /*<<< orphan*/  simulate_vesa_sync; } ;
struct drm_display_mode {int flags; scalar_t__ hsync_start; scalar_t__ hsync_end; scalar_t__ hskew; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_HSKEW ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 struct tilcdc_crtc* to_tilcdc_crtc (struct drm_crtc*) ; 

__attribute__((used)) static bool tilcdc_crtc_mode_fixup(struct drm_crtc *crtc,
		const struct drm_display_mode *mode,
		struct drm_display_mode *adjusted_mode)
{
	struct tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);

	if (!tilcdc_crtc->simulate_vesa_sync)
		return true;

	/*
	 * tilcdc does not generate VESA-compliant sync but aligns
	 * VS on the second edge of HS instead of first edge.
	 * We use adjusted_mode, to fixup sync by aligning both rising
	 * edges and add HSKEW offset to fix the sync.
	 */
	adjusted_mode->hskew = mode->hsync_end - mode->hsync_start;
	adjusted_mode->flags |= DRM_MODE_FLAG_HSKEW;

	if (mode->flags & DRM_MODE_FLAG_NHSYNC) {
		adjusted_mode->flags |= DRM_MODE_FLAG_PHSYNC;
		adjusted_mode->flags &= ~DRM_MODE_FLAG_NHSYNC;
	} else {
		adjusted_mode->flags |= DRM_MODE_FLAG_NHSYNC;
		adjusted_mode->flags &= ~DRM_MODE_FLAG_PHSYNC;
	}

	return true;
}