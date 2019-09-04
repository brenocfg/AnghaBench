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
struct net_device {int dummy; } ;
struct de_private {TYPE_1__* pdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  media_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  de_adapter_sleep (struct de_private*) ; 
 int /*<<< orphan*/  de_free_rings (struct de_private*) ; 
 int /*<<< orphan*/  de_stop_hw (struct de_private*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  ifdown ; 
 struct de_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct de_private*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int de_close (struct net_device *dev)
{
	struct de_private *de = netdev_priv(dev);
	unsigned long flags;

	netif_dbg(de, ifdown, dev, "disabling interface\n");

	del_timer_sync(&de->media_timer);

	spin_lock_irqsave(&de->lock, flags);
	de_stop_hw(de);
	netif_stop_queue(dev);
	netif_carrier_off(dev);
	spin_unlock_irqrestore(&de->lock, flags);

	free_irq(de->pdev->irq, dev);

	de_free_rings(de);
	de_adapter_sleep(de);
	return 0;
}