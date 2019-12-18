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
struct hibmc_framebuffer {int /*<<< orphan*/  fb; } ;
struct drm_fb_helper {int dummy; } ;
struct hibmc_fbdev {struct drm_fb_helper helper; struct hibmc_framebuffer* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  drm_framebuffer_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hibmc_fbdev_destroy(struct hibmc_fbdev *fbdev)
{
	struct hibmc_framebuffer *gfb = fbdev->fb;
	struct drm_fb_helper *fbh = &fbdev->helper;

	drm_fb_helper_unregister_fbi(fbh);

	drm_fb_helper_fini(fbh);

	if (gfb)
		drm_framebuffer_put(&gfb->fb);
}