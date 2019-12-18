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
struct ravb_private {int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 scalar_t__ ravb_queue_interrupt (struct net_device*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ravb_dma_interrupt(int irq, void *dev_id, int q)
{
	struct net_device *ndev = dev_id;
	struct ravb_private *priv = netdev_priv(ndev);
	irqreturn_t result = IRQ_NONE;

	spin_lock(&priv->lock);

	/* Network control/Best effort queue RX/TX */
	if (ravb_queue_interrupt(ndev, q))
		result = IRQ_HANDLED;

	spin_unlock(&priv->lock);
	return result;
}