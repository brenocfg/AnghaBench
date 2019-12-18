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
struct psb_fbdev {int /*<<< orphan*/  psb_fb_helper; } ;
struct drm_psb_private {struct psb_fbdev* fbdev; } ;
struct drm_device {int /*<<< orphan*/  dev; struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTELFB_CONN_LIMIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int drm_fb_helper_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_fb_helper_initial_config (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_fb_helper_single_add_all_connectors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_disable_unused_functions (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (struct psb_fbdev*) ; 
 struct psb_fbdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psb_fb_helper_funcs ; 

int psb_fbdev_init(struct drm_device *dev)
{
	struct psb_fbdev *fbdev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	int ret;

	fbdev = kzalloc(sizeof(struct psb_fbdev), GFP_KERNEL);
	if (!fbdev) {
		dev_err(dev->dev, "no memory\n");
		return -ENOMEM;
	}

	dev_priv->fbdev = fbdev;

	drm_fb_helper_prepare(dev, &fbdev->psb_fb_helper, &psb_fb_helper_funcs);

	ret = drm_fb_helper_init(dev, &fbdev->psb_fb_helper,
				 INTELFB_CONN_LIMIT);
	if (ret)
		goto free;

	ret = drm_fb_helper_single_add_all_connectors(&fbdev->psb_fb_helper);
	if (ret)
		goto fini;

	/* disable all the possible outputs/crtcs before entering KMS mode */
	drm_helper_disable_unused_functions(dev);

	ret = drm_fb_helper_initial_config(&fbdev->psb_fb_helper, 32);
	if (ret)
		goto fini;

	return 0;

fini:
	drm_fb_helper_fini(&fbdev->psb_fb_helper);
free:
	kfree(fbdev);
	return ret;
}