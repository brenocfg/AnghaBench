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
struct fb_ops {int dummy; } ;
struct drm_fb_helper {scalar_t__ fb; TYPE_1__* fbdev; } ;
struct drm_device {struct drm_fb_helper* fb_helper; } ;
struct TYPE_2__ {struct fb_ops* fbops; struct fb_ops* fbdefio; scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  drm_framebuffer_remove (scalar_t__) ; 
 int /*<<< orphan*/  fb_deferred_io_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct fb_ops*) ; 

void drm_fb_helper_fbdev_teardown(struct drm_device *dev)
{
	struct drm_fb_helper *fb_helper = dev->fb_helper;
	struct fb_ops *fbops = NULL;

	if (!fb_helper)
		return;

	/* Unregister if it hasn't been done already */
	if (fb_helper->fbdev && fb_helper->fbdev->dev)
		drm_fb_helper_unregister_fbi(fb_helper);

	if (fb_helper->fbdev && fb_helper->fbdev->fbdefio) {
		fb_deferred_io_cleanup(fb_helper->fbdev);
		kfree(fb_helper->fbdev->fbdefio);
		fbops = fb_helper->fbdev->fbops;
	}

	drm_fb_helper_fini(fb_helper);
	kfree(fbops);

	if (fb_helper->fb)
		drm_framebuffer_remove(fb_helper->fb);
}