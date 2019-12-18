#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct channel_data {TYPE_2__* netdev; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_consume_skb_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cosa_net_tx_done(struct channel_data *chan, int size)
{
	if (!chan->tx_skb) {
		pr_warn("%s: tx_done with empty skb!\n", chan->name);
		chan->netdev->stats.tx_errors++;
		chan->netdev->stats.tx_aborted_errors++;
		return 1;
	}
	dev_consume_skb_irq(chan->tx_skb);
	chan->tx_skb = NULL;
	chan->netdev->stats.tx_packets++;
	chan->netdev->stats.tx_bytes += size;
	netif_wake_queue(chan->netdev);
	return 1;
}