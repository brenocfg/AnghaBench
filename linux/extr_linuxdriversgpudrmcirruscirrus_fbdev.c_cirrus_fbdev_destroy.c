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
struct drm_framebuffer {int dummy; } ;
struct drm_device {int dummy; } ;
struct cirrus_fbdev {int /*<<< orphan*/  helper; int /*<<< orphan*/  sysram; struct drm_framebuffer* gfb; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_put (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cirrus_fbdev_destroy(struct drm_device *dev,
				struct cirrus_fbdev *gfbdev)
{
	struct drm_framebuffer *gfb = gfbdev->gfb;

	drm_fb_helper_unregister_fbi(&gfbdev->helper);

	vfree(gfbdev->sysram);
	drm_fb_helper_fini(&gfbdev->helper);
	if (gfb)
		drm_framebuffer_put(gfb);

	return 0;
}