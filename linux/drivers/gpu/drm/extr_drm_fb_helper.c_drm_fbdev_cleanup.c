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
struct fb_ops {int dummy; } ;
struct fb_info {struct fb_ops* fbops; void* screen_buffer; scalar_t__ fbdefio; } ;
struct drm_fb_helper {int /*<<< orphan*/  buffer; int /*<<< orphan*/  dev; struct fb_info* fbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_client_framebuffer_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_fini (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  fb_deferred_io_cleanup (struct fb_info*) ; 
 int /*<<< orphan*/  kfree (struct fb_ops*) ; 
 int /*<<< orphan*/  vfree (void*) ; 

__attribute__((used)) static void drm_fbdev_cleanup(struct drm_fb_helper *fb_helper)
{
	struct fb_info *fbi = fb_helper->fbdev;
	struct fb_ops *fbops = NULL;
	void *shadow = NULL;

	if (!fb_helper->dev)
		return;

	if (fbi && fbi->fbdefio) {
		fb_deferred_io_cleanup(fbi);
		shadow = fbi->screen_buffer;
		fbops = fbi->fbops;
	}

	drm_fb_helper_fini(fb_helper);

	if (shadow) {
		vfree(shadow);
		kfree(fbops);
	}

	drm_client_framebuffer_delete(fb_helper->buffer);
}