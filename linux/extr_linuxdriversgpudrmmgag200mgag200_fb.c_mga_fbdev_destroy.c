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
struct mga_framebuffer {int /*<<< orphan*/  base; int /*<<< orphan*/ * obj; } ;
struct mga_fbdev {int /*<<< orphan*/  sysram; int /*<<< orphan*/  helper; struct mga_framebuffer mfb; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_unregister_private (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mga_fbdev_destroy(struct drm_device *dev,
				struct mga_fbdev *mfbdev)
{
	struct mga_framebuffer *mfb = &mfbdev->mfb;

	drm_fb_helper_unregister_fbi(&mfbdev->helper);

	if (mfb->obj) {
		drm_gem_object_put_unlocked(mfb->obj);
		mfb->obj = NULL;
	}
	drm_fb_helper_fini(&mfbdev->helper);
	vfree(mfbdev->sysram);
	drm_framebuffer_unregister_private(&mfb->base);
	drm_framebuffer_cleanup(&mfb->base);

	return 0;
}