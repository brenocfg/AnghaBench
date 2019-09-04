#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kirin_drm_private {int /*<<< orphan*/  fbdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_connector; int /*<<< orphan*/  num_crtc; } ;
struct drm_device {int irq_enabled; struct kirin_drm_private* dev_private; int /*<<< orphan*/  dev; TYPE_1__ mode_config; } ;
struct TYPE_4__ {int (* init ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cleanup ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int component_bind_all (int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  component_unbind_all (int /*<<< orphan*/ ,struct drm_device*) ; 
 TYPE_2__* dc_ops ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct kirin_drm_private*) ; 
 struct kirin_drm_private* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fbdev_cma_init (struct drm_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int drm_vblank_init (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kirin_drm_mode_config_init (struct drm_device*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kirin_drm_kms_init(struct drm_device *dev)
{
	struct kirin_drm_private *priv;
	int ret;

	priv = devm_kzalloc(dev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	dev->dev_private = priv;
	dev_set_drvdata(dev->dev, dev);

	/* dev->mode_config initialization */
	drm_mode_config_init(dev);
	kirin_drm_mode_config_init(dev);

	/* display controller init */
	ret = dc_ops->init(to_platform_device(dev->dev));
	if (ret)
		goto err_mode_config_cleanup;

	/* bind and init sub drivers */
	ret = component_bind_all(dev->dev, dev);
	if (ret) {
		DRM_ERROR("failed to bind all component.\n");
		goto err_dc_cleanup;
	}

	/* vblank init */
	ret = drm_vblank_init(dev, dev->mode_config.num_crtc);
	if (ret) {
		DRM_ERROR("failed to initialize vblank.\n");
		goto err_unbind_all;
	}
	/* with irq_enabled = true, we can use the vblank feature. */
	dev->irq_enabled = true;

	/* reset all the states of crtc/plane/encoder/connector */
	drm_mode_config_reset(dev);

	/* init kms poll for handling hpd */
	drm_kms_helper_poll_init(dev);

	priv->fbdev = drm_fbdev_cma_init(dev, 32,
					 dev->mode_config.num_connector);

	if (IS_ERR(priv->fbdev)) {
		DRM_ERROR("failed to initialize fbdev.\n");
		ret = PTR_ERR(priv->fbdev);
		goto err_cleanup_poll;
	}
	return 0;

err_cleanup_poll:
	drm_kms_helper_poll_fini(dev);
err_unbind_all:
	component_unbind_all(dev->dev, dev);
err_dc_cleanup:
	dc_ops->cleanup(to_platform_device(dev->dev));
err_mode_config_cleanup:
	drm_mode_config_cleanup(dev);
	devm_kfree(dev->dev, priv);
	dev->dev_private = NULL;

	return ret;
}