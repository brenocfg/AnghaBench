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
struct g2d_data {int /*<<< orphan*/  drm_dev; int /*<<< orphan*/  runqueue_work; int /*<<< orphan*/  flags; } ;
struct exynos_drm_private {int /*<<< orphan*/ * g2d_dev; } ;
struct drm_device {struct exynos_drm_private* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G2D_BIT_SUSPEND_RUNQUEUE ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct g2d_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  exynos_drm_unregister_dma (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  g2d_wait_finish (struct g2d_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void g2d_unbind(struct device *dev, struct device *master, void *data)
{
	struct g2d_data *g2d = dev_get_drvdata(dev);
	struct drm_device *drm_dev = data;
	struct exynos_drm_private *priv = drm_dev->dev_private;

	/* Suspend operation and wait for engine idle. */
	set_bit(G2D_BIT_SUSPEND_RUNQUEUE, &g2d->flags);
	g2d_wait_finish(g2d, NULL);
	priv->g2d_dev = NULL;

	cancel_work_sync(&g2d->runqueue_work);
	exynos_drm_unregister_dma(g2d->drm_dev, dev);
}