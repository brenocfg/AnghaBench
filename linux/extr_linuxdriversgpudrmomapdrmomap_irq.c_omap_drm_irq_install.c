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
struct omap_drm_private {int /*<<< orphan*/  dispc; TYPE_1__* dispc_ops; scalar_t__ irq_mask; scalar_t__* planes; int /*<<< orphan*/  wait_list; int /*<<< orphan*/  wait_lock; } ;
struct drm_device {int irq_enabled; struct omap_drm_private* dev_private; } ;
struct TYPE_2__ {unsigned int (* get_num_mgrs ) (int /*<<< orphan*/ ) ;int (* request_irq ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_device*) ;int /*<<< orphan*/  (* runtime_put ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* clear_irqstatus ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* runtime_get ) (int /*<<< orphan*/ ) ;scalar_t__ (* mgr_get_sync_lost_irq ) (int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ DISPC_IRQ_OCP_ERR ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_irq_handler ; 
 scalar_t__* omap_underflow_irqs ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 unsigned int stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 
 int stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_device*) ; 

int omap_drm_irq_install(struct drm_device *dev)
{
	struct omap_drm_private *priv = dev->dev_private;
	unsigned int num_mgrs = priv->dispc_ops->get_num_mgrs(priv->dispc);
	unsigned int max_planes;
	unsigned int i;
	int ret;

	spin_lock_init(&priv->wait_lock);
	INIT_LIST_HEAD(&priv->wait_list);

	priv->irq_mask = DISPC_IRQ_OCP_ERR;

	max_planes = min(ARRAY_SIZE(priv->planes),
			 ARRAY_SIZE(omap_underflow_irqs));
	for (i = 0; i < max_planes; ++i) {
		if (priv->planes[i])
			priv->irq_mask |= omap_underflow_irqs[i];
	}

	for (i = 0; i < num_mgrs; ++i)
		priv->irq_mask |= priv->dispc_ops->mgr_get_sync_lost_irq(priv->dispc, i);

	priv->dispc_ops->runtime_get(priv->dispc);
	priv->dispc_ops->clear_irqstatus(priv->dispc, 0xffffffff);
	priv->dispc_ops->runtime_put(priv->dispc);

	ret = priv->dispc_ops->request_irq(priv->dispc, omap_irq_handler, dev);
	if (ret < 0)
		return ret;

	dev->irq_enabled = true;

	return 0;
}