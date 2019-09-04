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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct encx24j600_priv {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  kworker; struct sk_buff* tx_skb; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  kthread_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct encx24j600_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 

__attribute__((used)) static netdev_tx_t encx24j600_tx(struct sk_buff *skb, struct net_device *dev)
{
	struct encx24j600_priv *priv = netdev_priv(dev);

	netif_stop_queue(dev);

	/* save the timestamp */
	netif_trans_update(dev);

	/* Remember the skb for deferred processing */
	priv->tx_skb = skb;

	kthread_queue_work(&priv->kworker, &priv->tx_work);

	return NETDEV_TX_OK;
}