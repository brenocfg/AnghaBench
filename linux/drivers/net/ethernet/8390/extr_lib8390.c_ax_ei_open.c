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
struct net_device {scalar_t__ watchdog_timeo; } ;
struct ei_device {scalar_t__ irqlock; int /*<<< orphan*/  page_lock; } ;

/* Variables and functions */
 scalar_t__ TX_TIMEOUT ; 
 int /*<<< orphan*/  __NS8390_init (struct net_device*,int) ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int __ei_open(struct net_device *dev)
{
	unsigned long flags;
	struct ei_device *ei_local = netdev_priv(dev);

	if (dev->watchdog_timeo <= 0)
		dev->watchdog_timeo = TX_TIMEOUT;

	/*
	 *	Grab the page lock so we own the register set, then call
	 *	the init function.
	 */

	spin_lock_irqsave(&ei_local->page_lock, flags);
	__NS8390_init(dev, 1);
	/* Set the flag before we drop the lock, That way the IRQ arrives
	   after its set and we get no silly warnings */
	netif_start_queue(dev);
	spin_unlock_irqrestore(&ei_local->page_lock, flags);
	ei_local->irqlock = 0;
	return 0;
}