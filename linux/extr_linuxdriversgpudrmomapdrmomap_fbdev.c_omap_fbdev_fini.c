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
struct omap_fbdev {scalar_t__ fb; scalar_t__ bo; } ;
struct omap_drm_private {struct drm_fb_helper* fbdev; } ;
struct drm_fb_helper {int dummy; } ;
struct drm_device {struct omap_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG () ; 
 int /*<<< orphan*/  drm_fb_helper_fini (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  drm_framebuffer_remove (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct omap_fbdev*) ; 
 int /*<<< orphan*/  omap_gem_unpin (scalar_t__) ; 
 struct omap_fbdev* to_omap_fbdev (struct drm_fb_helper*) ; 

void omap_fbdev_fini(struct drm_device *dev)
{
	struct omap_drm_private *priv = dev->dev_private;
	struct drm_fb_helper *helper = priv->fbdev;
	struct omap_fbdev *fbdev;

	DBG();

	if (!helper)
		return;

	drm_fb_helper_unregister_fbi(helper);

	drm_fb_helper_fini(helper);

	fbdev = to_omap_fbdev(helper);

	/* unpin the GEM object pinned in omap_fbdev_create() */
	if (fbdev->bo)
		omap_gem_unpin(fbdev->bo);

	/* this will free the backing object */
	if (fbdev->fb)
		drm_framebuffer_remove(fbdev->fb);

	kfree(fbdev);

	priv->fbdev = NULL;
}