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
struct drm_device {struct armada_private* dev_private; } ;
struct device {int dummy; } ;
struct armada_private {int /*<<< orphan*/  drm; int /*<<< orphan*/  linear; } ;

/* Variables and functions */
 int /*<<< orphan*/  armada_fbdev_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  component_unbind_all (struct device*,int /*<<< orphan*/ *) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_atomic_helper_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void armada_drm_unbind(struct device *dev)
{
	struct drm_device *drm = dev_get_drvdata(dev);
	struct armada_private *priv = drm->dev_private;

	drm_kms_helper_poll_fini(&priv->drm);
	armada_fbdev_fini(&priv->drm);

	drm_dev_unregister(&priv->drm);

	drm_atomic_helper_shutdown(&priv->drm);

	component_unbind_all(dev, &priv->drm);

	drm_mode_config_cleanup(&priv->drm);
	drm_mm_takedown(&priv->linear);

	drm_dev_put(&priv->drm);
}