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
struct omap_drm_private {int /*<<< orphan*/  dispc; TYPE_1__* dispc_ops; } ;
struct drm_device {int irq_enabled; struct omap_drm_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_irq ) (int /*<<< orphan*/ ,struct drm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct drm_device*) ; 

void omap_drm_irq_uninstall(struct drm_device *dev)
{
	struct omap_drm_private *priv = dev->dev_private;

	if (!dev->irq_enabled)
		return;

	dev->irq_enabled = false;

	priv->dispc_ops->free_irq(priv->dispc, dev);
}