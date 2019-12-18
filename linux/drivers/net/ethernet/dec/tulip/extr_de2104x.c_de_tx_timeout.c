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
struct de_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  media_timer; int /*<<< orphan*/  tx_tail; int /*<<< orphan*/  tx_head; int /*<<< orphan*/  rx_tail; TYPE_1__* pdev; } ;
struct TYPE_2__ {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MacMode ; 
 int /*<<< orphan*/  MacStatus ; 
 int /*<<< orphan*/  SIAStatus ; 
 int /*<<< orphan*/  __de_get_stats (struct de_private*) ; 
 int /*<<< orphan*/  de_clean_rings (struct de_private*) ; 
 int /*<<< orphan*/  de_init_hw (struct de_private*) ; 
 int /*<<< orphan*/  de_init_rings (struct de_private*) ; 
 int /*<<< orphan*/  de_stop_hw (struct de_private*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int const) ; 
 int /*<<< orphan*/  dr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int const) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct de_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int const) ; 

__attribute__((used)) static void de_tx_timeout (struct net_device *dev)
{
	struct de_private *de = netdev_priv(dev);
	const int irq = de->pdev->irq;

	netdev_dbg(dev, "NIC status %08x mode %08x sia %08x desc %u/%u/%u\n",
		   dr32(MacStatus), dr32(MacMode), dr32(SIAStatus),
		   de->rx_tail, de->tx_head, de->tx_tail);

	del_timer_sync(&de->media_timer);

	disable_irq(irq);
	spin_lock_irq(&de->lock);

	de_stop_hw(de);
	netif_stop_queue(dev);
	netif_carrier_off(dev);

	spin_unlock_irq(&de->lock);
	enable_irq(irq);

	/* Update the error counts. */
	__de_get_stats(de);

	synchronize_irq(irq);
	de_clean_rings(de);

	de_init_rings(de);

	de_init_hw(de);

	netif_wake_queue(dev);
}