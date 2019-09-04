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
struct drm_device {int dummy; } ;
struct ast_framebuffer {int /*<<< orphan*/  base; int /*<<< orphan*/ * obj; } ;
struct ast_fbdev {int /*<<< orphan*/  sysram; int /*<<< orphan*/  helper; struct ast_framebuffer afb; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_force_disable_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_unregister_private (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ast_fbdev_destroy(struct drm_device *dev,
			      struct ast_fbdev *afbdev)
{
	struct ast_framebuffer *afb = &afbdev->afb;

	drm_crtc_force_disable_all(dev);
	drm_fb_helper_unregister_fbi(&afbdev->helper);

	if (afb->obj) {
		drm_gem_object_put_unlocked(afb->obj);
		afb->obj = NULL;
	}
	drm_fb_helper_fini(&afbdev->helper);

	vfree(afbdev->sysram);
	drm_framebuffer_unregister_private(&afb->base);
	drm_framebuffer_cleanup(&afb->base);
}