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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct fs_enet_private {int /*<<< orphan*/  interrupt; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_lock; TYPE_1__* ops; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct fs_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

__attribute__((used)) static int fs_enet_close(struct net_device *dev)
{
	struct fs_enet_private *fep = netdev_priv(dev);
	unsigned long flags;

	netif_stop_queue(dev);
	netif_carrier_off(dev);
	napi_disable(&fep->napi);
	cancel_work_sync(&fep->timeout_work);
	phy_stop(dev->phydev);

	spin_lock_irqsave(&fep->lock, flags);
	spin_lock(&fep->tx_lock);
	(*fep->ops->stop)(dev);
	spin_unlock(&fep->tx_lock);
	spin_unlock_irqrestore(&fep->lock, flags);

	/* release any irqs */
	phy_disconnect(dev->phydev);
	free_irq(fep->interrupt, dev);

	return 0;
}