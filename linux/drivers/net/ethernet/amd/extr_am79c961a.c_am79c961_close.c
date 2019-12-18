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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  base_addr; } ;
struct dev_priv {int /*<<< orphan*/  chip_lock; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR0 ; 
 int /*<<< orphan*/  CSR0_STOP ; 
 int /*<<< orphan*/  CSR3 ; 
 int /*<<< orphan*/  CSR3_MASKALL ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_rreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
am79c961_close(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	unsigned long flags;

	del_timer_sync(&priv->timer);

	netif_stop_queue(dev);
	netif_carrier_off(dev);

	spin_lock_irqsave(&priv->chip_lock, flags);
	write_rreg (dev->base_addr, CSR0, CSR0_STOP);
	write_rreg (dev->base_addr, CSR3, CSR3_MASKALL);
	spin_unlock_irqrestore(&priv->chip_lock, flags);

	free_irq (dev->irq, dev);

	return 0;
}