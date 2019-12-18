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
struct channel_data {TYPE_1__* cosa; scalar_t__ usage; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/ * rx_skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  cosa_disable_rx (struct channel_data*) ; 
 struct channel_data* dev_to_chan (struct net_device*) ; 
 int /*<<< orphan*/  hdlc_close (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cosa_net_close(struct net_device *dev)
{
	struct channel_data *chan = dev_to_chan(dev);
	unsigned long flags;

	netif_stop_queue(dev);
	hdlc_close(dev);
	cosa_disable_rx(chan);
	spin_lock_irqsave(&chan->cosa->lock, flags);
	if (chan->rx_skb) {
		kfree_skb(chan->rx_skb);
		chan->rx_skb = NULL;
	}
	if (chan->tx_skb) {
		kfree_skb(chan->tx_skb);
		chan->tx_skb = NULL;
	}
	chan->usage = 0;
	chan->cosa->usage--;
	spin_unlock_irqrestore(&chan->cosa->lock, flags);
	return 0;
}