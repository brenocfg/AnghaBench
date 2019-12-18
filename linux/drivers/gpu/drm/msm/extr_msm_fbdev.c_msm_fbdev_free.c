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
struct msm_fbdev {scalar_t__ fb; } ;
struct msm_drm_private {struct drm_fb_helper* fbdev; } ;
struct drm_gem_object {int dummy; } ;
struct drm_fb_helper {int dummy; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG () ; 
 int /*<<< orphan*/  drm_fb_helper_fini (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  drm_framebuffer_remove (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct msm_fbdev*) ; 
 struct drm_gem_object* msm_framebuffer_bo (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gem_put_vaddr (struct drm_gem_object*) ; 
 struct msm_fbdev* to_msm_fbdev (struct drm_fb_helper*) ; 

void msm_fbdev_free(struct drm_device *dev)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct drm_fb_helper *helper = priv->fbdev;
	struct msm_fbdev *fbdev;

	DBG();

	drm_fb_helper_unregister_fbi(helper);

	drm_fb_helper_fini(helper);

	fbdev = to_msm_fbdev(priv->fbdev);

	/* this will free the backing object */
	if (fbdev->fb) {
		struct drm_gem_object *bo =
			msm_framebuffer_bo(fbdev->fb, 0);
		msm_gem_put_vaddr(bo);
		drm_framebuffer_remove(fbdev->fb);
	}

	kfree(fbdev);

	priv->fbdev = NULL;
}