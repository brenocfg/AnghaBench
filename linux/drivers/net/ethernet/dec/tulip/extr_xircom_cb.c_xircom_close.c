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
struct xircom_private {TYPE_1__* pdev; scalar_t__ open; int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  deactivate_receiver (struct xircom_private*) ; 
 int /*<<< orphan*/  deactivate_transmitter (struct xircom_private*) ; 
 int /*<<< orphan*/  disable_all_interrupts (struct xircom_private*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct xircom_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  remove_descriptors (struct xircom_private*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int xircom_close(struct net_device *dev)
{
	struct xircom_private *card;
	unsigned long flags;

	card = netdev_priv(dev);
	netif_stop_queue(dev); /* we don't want new packets */


	spin_lock_irqsave(&card->lock,flags);

	disable_all_interrupts(card);
#if 0
	/* We can enable this again once we send dummy packets on ifconfig ethX up */
	deactivate_receiver(card);
	deactivate_transmitter(card);
#endif
	remove_descriptors(card);

	spin_unlock_irqrestore(&card->lock,flags);

	card->open = 0;
	free_irq(card->pdev->irq, dev);

	return 0;

}