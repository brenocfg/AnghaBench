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
struct exynos_drm_private {struct drm_fb_helper* fb_helper; } ;
struct drm_fb_helper {int dummy; } ;
struct exynos_drm_fbdev {struct drm_fb_helper drm_fb_helper; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_crtc; } ;
struct drm_device {int /*<<< orphan*/  dev; TYPE_1__ mode_config; struct exynos_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_CONNECTOR ; 
 int /*<<< orphan*/  PREFERRED_BPP ; 
 int /*<<< orphan*/  drm_fb_helper_fini (struct drm_fb_helper*) ; 
 int drm_fb_helper_init (struct drm_device*,struct drm_fb_helper*,int /*<<< orphan*/ ) ; 
 int drm_fb_helper_initial_config (struct drm_fb_helper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (struct drm_device*,struct drm_fb_helper*,int /*<<< orphan*/ *) ; 
 int drm_fb_helper_single_add_all_connectors (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  exynos_drm_fb_helper_funcs ; 
 int /*<<< orphan*/  kfree (struct exynos_drm_fbdev*) ; 
 struct exynos_drm_fbdev* kzalloc (int,int /*<<< orphan*/ ) ; 

int exynos_drm_fbdev_init(struct drm_device *dev)
{
	struct exynos_drm_fbdev *fbdev;
	struct exynos_drm_private *private = dev->dev_private;
	struct drm_fb_helper *helper;
	int ret;

	if (!dev->mode_config.num_crtc)
		return 0;

	fbdev = kzalloc(sizeof(*fbdev), GFP_KERNEL);
	if (!fbdev)
		return -ENOMEM;

	private->fb_helper = helper = &fbdev->drm_fb_helper;

	drm_fb_helper_prepare(dev, helper, &exynos_drm_fb_helper_funcs);

	ret = drm_fb_helper_init(dev, helper, MAX_CONNECTOR);
	if (ret < 0) {
		DRM_DEV_ERROR(dev->dev,
			      "failed to initialize drm fb helper.\n");
		goto err_init;
	}

	ret = drm_fb_helper_single_add_all_connectors(helper);
	if (ret < 0) {
		DRM_DEV_ERROR(dev->dev,
			      "failed to register drm_fb_helper_connector.\n");
		goto err_setup;

	}

	ret = drm_fb_helper_initial_config(helper, PREFERRED_BPP);
	if (ret < 0) {
		DRM_DEV_ERROR(dev->dev,
			      "failed to set up hw configuration.\n");
		goto err_setup;
	}

	return 0;

err_setup:
	drm_fb_helper_fini(helper);

err_init:
	private->fb_helper = NULL;
	kfree(fbdev);

	return ret;
}