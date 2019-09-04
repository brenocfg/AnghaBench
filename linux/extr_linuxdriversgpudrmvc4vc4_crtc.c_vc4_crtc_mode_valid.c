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
struct drm_display_mode {int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {TYPE_1__ base; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 int MODE_NO_DBLESCAN ; 
 int MODE_OK ; 

__attribute__((used)) static enum drm_mode_status vc4_crtc_mode_valid(struct drm_crtc *crtc,
						const struct drm_display_mode *mode)
{
	/* Do not allow doublescan modes from user space */
	if (mode->flags & DRM_MODE_FLAG_DBLSCAN) {
		DRM_DEBUG_KMS("[CRTC:%d] Doublescan mode rejected.\n",
			      crtc->base.id);
		return MODE_NO_DBLESCAN;
	}

	return MODE_OK;
}