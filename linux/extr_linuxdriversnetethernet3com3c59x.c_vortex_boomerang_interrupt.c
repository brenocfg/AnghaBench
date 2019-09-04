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
struct vortex_private {int /*<<< orphan*/  lock; scalar_t__ full_bus_master_rx; } ;
struct net_device {int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  _boomerang_interrupt (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  _vortex_interrupt (int /*<<< orphan*/ ,struct net_device*) ; 
 struct vortex_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t
vortex_boomerang_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct vortex_private *vp = netdev_priv(dev);
	unsigned long flags;
	irqreturn_t ret;

	spin_lock_irqsave(&vp->lock, flags);

	if (vp->full_bus_master_rx)
		ret = _boomerang_interrupt(dev->irq, dev);
	else
		ret = _vortex_interrupt(dev->irq, dev);

	spin_unlock_irqrestore(&vp->lock, flags);

	return ret;
}