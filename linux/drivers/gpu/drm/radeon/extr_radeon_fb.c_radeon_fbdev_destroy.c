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
struct drm_framebuffer {int /*<<< orphan*/ ** obj; } ;
struct radeon_fbdev {int /*<<< orphan*/  helper; struct drm_framebuffer fb; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_framebuffer_unregister_private (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  radeonfb_destroy_pinned_object (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int radeon_fbdev_destroy(struct drm_device *dev, struct radeon_fbdev *rfbdev)
{
	struct drm_framebuffer *fb = &rfbdev->fb;

	drm_fb_helper_unregister_fbi(&rfbdev->helper);

	if (fb->obj[0]) {
		radeonfb_destroy_pinned_object(fb->obj[0]);
		fb->obj[0] = NULL;
		drm_framebuffer_unregister_private(fb);
		drm_framebuffer_cleanup(fb);
	}
	drm_fb_helper_fini(&rfbdev->helper);

	return 0;
}