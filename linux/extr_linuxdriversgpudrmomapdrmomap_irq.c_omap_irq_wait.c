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
struct omap_irq_wait {scalar_t__ count; int /*<<< orphan*/  node; int /*<<< orphan*/  wq; } ;
struct omap_drm_private {int /*<<< orphan*/  wait_lock; } ;
struct drm_device {struct omap_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct omap_irq_wait*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_irq_update (struct drm_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

int omap_irq_wait(struct drm_device *dev, struct omap_irq_wait *wait,
		unsigned long timeout)
{
	struct omap_drm_private *priv = dev->dev_private;
	unsigned long flags;
	int ret;

	ret = wait_event_timeout(wait->wq, (wait->count <= 0), timeout);

	spin_lock_irqsave(&priv->wait_lock, flags);
	list_del(&wait->node);
	omap_irq_update(dev);
	spin_unlock_irqrestore(&priv->wait_lock, flags);

	kfree(wait);

	return ret == 0 ? -1 : 0;
}