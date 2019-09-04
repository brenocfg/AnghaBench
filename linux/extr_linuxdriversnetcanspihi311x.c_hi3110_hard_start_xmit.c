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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct hi3110_priv {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  wq; struct sk_buff* tx_skb; scalar_t__ tx_len; struct spi_device* spi; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct hi3110_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t hi3110_hard_start_xmit(struct sk_buff *skb,
					  struct net_device *net)
{
	struct hi3110_priv *priv = netdev_priv(net);
	struct spi_device *spi = priv->spi;

	if (priv->tx_skb || priv->tx_len) {
		dev_err(&spi->dev, "hard_xmit called while tx busy\n");
		return NETDEV_TX_BUSY;
	}

	if (can_dropped_invalid_skb(net, skb))
		return NETDEV_TX_OK;

	netif_stop_queue(net);
	priv->tx_skb = skb;
	queue_work(priv->wq, &priv->tx_work);

	return NETDEV_TX_OK;
}