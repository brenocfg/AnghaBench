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
struct w5100_priv {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  xfer_wq; struct sk_buff* tx_skb; TYPE_1__* ops; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {scalar_t__ may_sleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  WARN_ON (struct sk_buff*) ; 
 struct w5100_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w5100_tx_skb (struct net_device*,struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t w5100_start_tx(struct sk_buff *skb, struct net_device *ndev)
{
	struct w5100_priv *priv = netdev_priv(ndev);

	netif_stop_queue(ndev);

	if (priv->ops->may_sleep) {
		WARN_ON(priv->tx_skb);
		priv->tx_skb = skb;
		queue_work(priv->xfer_wq, &priv->tx_work);
	} else {
		w5100_tx_skb(ndev, skb);
	}

	return NETDEV_TX_OK;
}