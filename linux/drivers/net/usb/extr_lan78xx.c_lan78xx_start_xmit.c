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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct lan78xx_net {int /*<<< orphan*/  bh; TYPE_3__* net; int /*<<< orphan*/  txq_pend; TYPE_1__* udev; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_5__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;
struct TYPE_4__ {scalar_t__ speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ USB_SPEED_SUPER ; 
 struct sk_buff* lan78xx_tx_prep (struct lan78xx_net*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct lan78xx_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct lan78xx_net*,int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_err ; 

__attribute__((used)) static netdev_tx_t
lan78xx_start_xmit(struct sk_buff *skb, struct net_device *net)
{
	struct lan78xx_net *dev = netdev_priv(net);
	struct sk_buff *skb2 = NULL;

	if (skb) {
		skb_tx_timestamp(skb);
		skb2 = lan78xx_tx_prep(dev, skb, GFP_ATOMIC);
	}

	if (skb2) {
		skb_queue_tail(&dev->txq_pend, skb2);

		/* throttle TX patch at slower than SUPER SPEED USB */
		if ((dev->udev->speed < USB_SPEED_SUPER) &&
		    (skb_queue_len(&dev->txq_pend) > 10))
			netif_stop_queue(net);
	} else {
		netif_dbg(dev, tx_err, dev->net,
			  "lan78xx_tx_prep return NULL\n");
		dev->net->stats.tx_errors++;
		dev->net->stats.tx_dropped++;
	}

	tasklet_schedule(&dev->bh);

	return NETDEV_TX_OK;
}