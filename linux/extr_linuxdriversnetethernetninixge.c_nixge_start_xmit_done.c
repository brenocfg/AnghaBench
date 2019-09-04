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
typedef  scalar_t__ u32 ;
struct nixge_tx_skb {int dummy; } ;
struct nixge_priv {size_t tx_bd_ci; struct nixge_tx_skb* tx_skb; struct nixge_hw_dma_bd* tx_bd_v; } ;
struct nixge_hw_dma_bd {unsigned int status; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 size_t TX_BD_NUM ; 
 unsigned int XAXIDMA_BD_STS_ACTUAL_LEN_MASK ; 
 unsigned int XAXIDMA_BD_STS_COMPLETE_MASK ; 
 struct nixge_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  nixge_tx_skb_unmap (struct nixge_priv*,struct nixge_tx_skb*) ; 

__attribute__((used)) static void nixge_start_xmit_done(struct net_device *ndev)
{
	struct nixge_priv *priv = netdev_priv(ndev);
	struct nixge_hw_dma_bd *cur_p;
	struct nixge_tx_skb *tx_skb;
	unsigned int status = 0;
	u32 packets = 0;
	u32 size = 0;

	cur_p = &priv->tx_bd_v[priv->tx_bd_ci];
	tx_skb = &priv->tx_skb[priv->tx_bd_ci];

	status = cur_p->status;

	while (status & XAXIDMA_BD_STS_COMPLETE_MASK) {
		nixge_tx_skb_unmap(priv, tx_skb);
		cur_p->status = 0;

		size += status & XAXIDMA_BD_STS_ACTUAL_LEN_MASK;
		packets++;

		++priv->tx_bd_ci;
		priv->tx_bd_ci %= TX_BD_NUM;
		cur_p = &priv->tx_bd_v[priv->tx_bd_ci];
		tx_skb = &priv->tx_skb[priv->tx_bd_ci];
		status = cur_p->status;
	}

	ndev->stats.tx_packets += packets;
	ndev->stats.tx_bytes += size;

	if (packets)
		netif_wake_queue(ndev);
}