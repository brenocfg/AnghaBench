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
struct TYPE_2__ {int ctrlmode; } ;
struct grcan_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  hang_timer; scalar_t__ need_txbug_workaround; TYPE_1__ can; int /*<<< orphan*/  closing; int /*<<< orphan*/  resetting; } ;

/* Variables and functions */
 int CAN_CTRLMODE_LISTENONLY ; 
 int catch_up_echo_skb (struct net_device*,int,int) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct grcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int grcan_transmit_catch_up(struct net_device *dev, int budget)
{
	struct grcan_priv *priv = netdev_priv(dev);
	unsigned long flags;
	int work_done;

	spin_lock_irqsave(&priv->lock, flags);

	work_done = catch_up_echo_skb(dev, budget, true);
	if (work_done) {
		if (!priv->resetting && !priv->closing &&
		    !(priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY))
			netif_wake_queue(dev);

		/* With napi we don't get TX interrupts for a while,
		 * so prevent a running reset while catching up
		 */
		if (priv->need_txbug_workaround)
			del_timer(&priv->hang_timer);
	}

	spin_unlock_irqrestore(&priv->lock, flags);

	return work_done;
}