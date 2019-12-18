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
struct omap_fbdev {struct drm_fb_helper base; int /*<<< orphan*/  work; } ;
struct omap_drm_private {struct drm_fb_helper* fbdev; int /*<<< orphan*/  num_pipes; } ;
struct drm_device {int /*<<< orphan*/  dev; struct omap_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_fb_helper_fini (struct drm_fb_helper*) ; 
 int drm_fb_helper_init (struct drm_device*,struct drm_fb_helper*,int /*<<< orphan*/ ) ; 
 int drm_fb_helper_initial_config (struct drm_fb_helper*,int) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (struct drm_device*,struct drm_fb_helper*,int /*<<< orphan*/ *) ; 
 int drm_fb_helper_single_add_all_connectors (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  kfree (struct omap_fbdev*) ; 
 struct omap_fbdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_fb_helper_funcs ; 
 int /*<<< orphan*/  pan_worker ; 

void omap_fbdev_init(struct drm_device *dev)
{
	struct omap_drm_private *priv = dev->dev_private;
	struct omap_fbdev *fbdev = NULL;
	struct drm_fb_helper *helper;
	int ret = 0;

	if (!priv->num_pipes)
		return;

	fbdev = kzalloc(sizeof(*fbdev), GFP_KERNEL);
	if (!fbdev)
		goto fail;

	INIT_WORK(&fbdev->work, pan_worker);

	helper = &fbdev->base;

	drm_fb_helper_prepare(dev, helper, &omap_fb_helper_funcs);

	ret = drm_fb_helper_init(dev, helper, priv->num_pipes);
	if (ret)
		goto fail;

	ret = drm_fb_helper_single_add_all_connectors(helper);
	if (ret)
		goto fini;

	ret = drm_fb_helper_initial_config(helper, 32);
	if (ret)
		goto fini;

	priv->fbdev = helper;

	return;

fini:
	drm_fb_helper_fini(helper);
fail:
	kfree(fbdev);

	dev_warn(dev->dev, "omap_fbdev_init failed\n");
}