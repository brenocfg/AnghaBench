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
struct drm_fb_helper {int /*<<< orphan*/ * fbdev; int /*<<< orphan*/ * dev; int /*<<< orphan*/  preferred_bpp; scalar_t__ funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_connector; } ;
struct drm_device {int /*<<< orphan*/  dev; TYPE_1__ mode_config; scalar_t__ fb_helper; } ;
struct drm_client_dev {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_drv_uses_atomic_modeset (struct drm_device*) ; 
 struct drm_fb_helper* drm_fb_helper_from_client (struct drm_client_dev*) ; 
 int /*<<< orphan*/  drm_fb_helper_generic_funcs ; 
 int drm_fb_helper_hotplug_event (scalar_t__) ; 
 int drm_fb_helper_init (struct drm_device*,struct drm_fb_helper*,int /*<<< orphan*/ ) ; 
 int drm_fb_helper_initial_config (struct drm_fb_helper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (struct drm_device*,struct drm_fb_helper*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fbdev_cleanup (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  drm_helper_disable_unused_functions (struct drm_device*) ; 

__attribute__((used)) static int drm_fbdev_client_hotplug(struct drm_client_dev *client)
{
	struct drm_fb_helper *fb_helper = drm_fb_helper_from_client(client);
	struct drm_device *dev = client->dev;
	int ret;

	/* Setup is not retried if it has failed */
	if (!fb_helper->dev && fb_helper->funcs)
		return 0;

	if (dev->fb_helper)
		return drm_fb_helper_hotplug_event(dev->fb_helper);

	if (!dev->mode_config.num_connector) {
		DRM_DEV_DEBUG(dev->dev, "No connectors found, will not create framebuffer!\n");
		return 0;
	}

	drm_fb_helper_prepare(dev, fb_helper, &drm_fb_helper_generic_funcs);

	ret = drm_fb_helper_init(dev, fb_helper, 0);
	if (ret)
		goto err;

	if (!drm_drv_uses_atomic_modeset(dev))
		drm_helper_disable_unused_functions(dev);

	ret = drm_fb_helper_initial_config(fb_helper, fb_helper->preferred_bpp);
	if (ret)
		goto err_cleanup;

	return 0;

err_cleanup:
	drm_fbdev_cleanup(fb_helper);
err:
	fb_helper->dev = NULL;
	fb_helper->fbdev = NULL;

	DRM_DEV_ERROR(dev->dev, "fbdev: Failed to setup generic emulation (ret=%d)\n", ret);

	return ret;
}