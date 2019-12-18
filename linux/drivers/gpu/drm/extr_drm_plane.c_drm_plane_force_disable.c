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
struct drm_plane {int /*<<< orphan*/ * crtc; int /*<<< orphan*/ * fb; int /*<<< orphan*/ * old_fb; TYPE_1__* funcs; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int (* disable_plane ) (struct drm_plane*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_drv_uses_atomic_modeset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_framebuffer_put (int /*<<< orphan*/ *) ; 
 int stub1 (struct drm_plane*,int /*<<< orphan*/ *) ; 

void drm_plane_force_disable(struct drm_plane *plane)
{
	int ret;

	if (!plane->fb)
		return;

	WARN_ON(drm_drv_uses_atomic_modeset(plane->dev));

	plane->old_fb = plane->fb;
	ret = plane->funcs->disable_plane(plane, NULL);
	if (ret) {
		DRM_ERROR("failed to disable plane with busy fb\n");
		plane->old_fb = NULL;
		return;
	}
	/* disconnect the plane from the fb and crtc: */
	drm_framebuffer_put(plane->old_fb);
	plane->old_fb = NULL;
	plane->fb = NULL;
	plane->crtc = NULL;
}