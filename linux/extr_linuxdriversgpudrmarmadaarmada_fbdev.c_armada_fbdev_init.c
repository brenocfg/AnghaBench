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
struct drm_device {int /*<<< orphan*/  dev; struct armada_private* dev_private; } ;
struct armada_private {struct drm_fb_helper* fbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  armada_fb_helper_funcs ; 
 struct drm_fb_helper* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_fini (struct drm_fb_helper*) ; 
 int drm_fb_helper_init (struct drm_device*,struct drm_fb_helper*,int) ; 
 int drm_fb_helper_initial_config (struct drm_fb_helper*,int) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (struct drm_device*,struct drm_fb_helper*,int /*<<< orphan*/ *) ; 
 int drm_fb_helper_single_add_all_connectors (struct drm_fb_helper*) ; 

int armada_fbdev_init(struct drm_device *dev)
{
	struct armada_private *priv = dev->dev_private;
	struct drm_fb_helper *fbh;
	int ret;

	fbh = devm_kzalloc(dev->dev, sizeof(*fbh), GFP_KERNEL);
	if (!fbh)
		return -ENOMEM;

	priv->fbdev = fbh;

	drm_fb_helper_prepare(dev, fbh, &armada_fb_helper_funcs);

	ret = drm_fb_helper_init(dev, fbh, 1);
	if (ret) {
		DRM_ERROR("failed to initialize drm fb helper\n");
		goto err_fb_helper;
	}

	ret = drm_fb_helper_single_add_all_connectors(fbh);
	if (ret) {
		DRM_ERROR("failed to add fb connectors\n");
		goto err_fb_setup;
	}

	ret = drm_fb_helper_initial_config(fbh, 32);
	if (ret) {
		DRM_ERROR("failed to set initial config\n");
		goto err_fb_setup;
	}

	return 0;
 err_fb_setup:
	drm_fb_helper_fini(fbh);
 err_fb_helper:
	priv->fbdev = NULL;
	return ret;
}