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
struct pl111_drm_dev_private {int /*<<< orphan*/  bridge; scalar_t__ panel; } ;
struct drm_device {struct pl111_drm_dev_private* dev_private; } ;
struct device {int dummy; } ;
struct amba_device {struct device dev; } ;

/* Variables and functions */
 struct drm_device* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_panel_bridge_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_reserved_mem_device_release (struct device*) ; 

__attribute__((used)) static int pl111_amba_remove(struct amba_device *amba_dev)
{
	struct device *dev = &amba_dev->dev;
	struct drm_device *drm = amba_get_drvdata(amba_dev);
	struct pl111_drm_dev_private *priv = drm->dev_private;

	drm_dev_unregister(drm);
	if (priv->panel)
		drm_panel_bridge_remove(priv->bridge);
	drm_mode_config_cleanup(drm);
	drm_dev_put(drm);
	of_reserved_mem_device_release(dev);

	return 0;
}