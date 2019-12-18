#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct channel_data {int /*<<< orphan*/ * tx_skb; TYPE_3__* cosa; TYPE_2__* netdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  rxtx; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_errors; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXBIT ; 
 int /*<<< orphan*/  cosa_kick (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 struct channel_data* dev_to_chan (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cosa_net_timeout(struct net_device *dev)
{
	struct channel_data *chan = dev_to_chan(dev);

	if (test_bit(RXBIT, &chan->cosa->rxtx)) {
		chan->netdev->stats.rx_errors++;
		chan->netdev->stats.rx_missed_errors++;
	} else {
		chan->netdev->stats.tx_errors++;
		chan->netdev->stats.tx_aborted_errors++;
	}
	cosa_kick(chan->cosa);
	if (chan->tx_skb) {
		dev_kfree_skb(chan->tx_skb);
		chan->tx_skb = NULL;
	}
	netif_wake_queue(dev);
}