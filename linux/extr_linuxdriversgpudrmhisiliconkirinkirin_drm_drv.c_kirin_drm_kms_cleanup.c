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
struct kirin_drm_private {int /*<<< orphan*/ * fbdev; } ;
struct drm_device {struct kirin_drm_private* dev_private; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cleanup ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* dc_ops ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct kirin_drm_private*) ; 
 int /*<<< orphan*/  drm_fbdev_cma_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kirin_drm_kms_cleanup(struct drm_device *dev)
{
	struct kirin_drm_private *priv = dev->dev_private;

	if (priv->fbdev) {
		drm_fbdev_cma_fini(priv->fbdev);
		priv->fbdev = NULL;
	}

	drm_kms_helper_poll_fini(dev);
	dc_ops->cleanup(to_platform_device(dev->dev));
	drm_mode_config_cleanup(dev);
	devm_kfree(dev->dev, priv);
	dev->dev_private = NULL;

	return 0;
}