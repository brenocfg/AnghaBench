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
struct drm_fb_helper {int dummy; } ;
struct msm_fbdev {struct drm_fb_helper base; } ;
struct msm_drm_private {struct drm_fb_helper* fbdev; int /*<<< orphan*/  num_connectors; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_fb_helper_fini (struct drm_fb_helper*) ; 
 int drm_fb_helper_init (struct drm_device*,struct drm_fb_helper*,int /*<<< orphan*/ ) ; 
 int drm_fb_helper_initial_config (struct drm_fb_helper*,int) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (struct drm_device*,struct drm_fb_helper*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_remove_conflicting_framebuffers (int /*<<< orphan*/ *,char*,int) ; 
 int drm_fb_helper_single_add_all_connectors (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  kfree (struct msm_fbdev*) ; 
 struct msm_fbdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_fb_helper_funcs ; 

struct drm_fb_helper *msm_fbdev_init(struct drm_device *dev)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct msm_fbdev *fbdev = NULL;
	struct drm_fb_helper *helper;
	int ret;

	fbdev = kzalloc(sizeof(*fbdev), GFP_KERNEL);
	if (!fbdev)
		goto fail;

	helper = &fbdev->base;

	drm_fb_helper_prepare(dev, helper, &msm_fb_helper_funcs);

	ret = drm_fb_helper_init(dev, helper, priv->num_connectors);
	if (ret) {
		DRM_DEV_ERROR(dev->dev, "could not init fbdev: ret=%d\n", ret);
		goto fail;
	}

	ret = drm_fb_helper_single_add_all_connectors(helper);
	if (ret)
		goto fini;

	/* the fw fb could be anywhere in memory */
	drm_fb_helper_remove_conflicting_framebuffers(NULL, "msm", false);

	ret = drm_fb_helper_initial_config(helper, 32);
	if (ret)
		goto fini;

	priv->fbdev = helper;

	return helper;

fini:
	drm_fb_helper_fini(helper);
fail:
	kfree(fbdev);
	return NULL;
}