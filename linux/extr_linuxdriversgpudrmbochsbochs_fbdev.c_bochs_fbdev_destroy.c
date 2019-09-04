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
struct bochs_framebuffer {int /*<<< orphan*/  base; int /*<<< orphan*/ * obj; } ;
struct TYPE_2__ {int /*<<< orphan*/  helper; struct bochs_framebuffer gfb; } ;
struct bochs_device {TYPE_1__ fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_unregister_private (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bochs_fbdev_destroy(struct bochs_device *bochs)
{
	struct bochs_framebuffer *gfb = &bochs->fb.gfb;

	DRM_DEBUG_DRIVER("\n");

	drm_fb_helper_unregister_fbi(&bochs->fb.helper);

	if (gfb->obj) {
		drm_gem_object_unreference_unlocked(gfb->obj);
		gfb->obj = NULL;
	}

	drm_framebuffer_unregister_private(&gfb->base);
	drm_framebuffer_cleanup(&gfb->base);

	return 0;
}