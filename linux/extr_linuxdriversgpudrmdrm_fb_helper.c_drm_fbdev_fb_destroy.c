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
struct TYPE_2__ {scalar_t__ funcs; } ;
struct fb_ops {TYPE_1__ client; int /*<<< orphan*/  buffer; struct fb_info* fbdev; } ;
struct fb_info {struct fb_ops* fbops; void* screen_buffer; scalar_t__ fbdefio; struct fb_ops* par; } ;
struct drm_fb_helper {TYPE_1__ client; int /*<<< orphan*/  buffer; struct fb_info* fbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_client_framebuffer_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_client_release (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_fb_helper_fini (struct fb_ops*) ; 
 int /*<<< orphan*/  fb_deferred_io_cleanup (struct fb_info*) ; 
 int /*<<< orphan*/  kfree (struct fb_ops*) ; 
 int /*<<< orphan*/  vfree (void*) ; 

__attribute__((used)) static void drm_fbdev_fb_destroy(struct fb_info *info)
{
	struct drm_fb_helper *fb_helper = info->par;
	struct fb_info *fbi = fb_helper->fbdev;
	struct fb_ops *fbops = NULL;
	void *shadow = NULL;

	if (fbi->fbdefio) {
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
	/*
	 * FIXME:
	 * Remove conditional when all CMA drivers have been moved over to using
	 * drm_fbdev_generic_setup().
	 */
	if (fb_helper->client.funcs) {
		drm_client_release(&fb_helper->client);
		kfree(fb_helper);
	}
}