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
struct sk_buff {scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_aborted_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct ftmac100_txdes {int dummy; } ;
struct ftmac100 {scalar_t__ tx_pending; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  dev; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ftmac100_txdes* ftmac100_current_clean_txdes (struct ftmac100*) ; 
 int /*<<< orphan*/  ftmac100_tx_clean_pointer_advance (struct ftmac100*) ; 
 scalar_t__ ftmac100_txdes_excessive_collision (struct ftmac100_txdes*) ; 
 int /*<<< orphan*/  ftmac100_txdes_get_dma_addr (struct ftmac100_txdes*) ; 
 struct sk_buff* ftmac100_txdes_get_skb (struct ftmac100_txdes*) ; 
 scalar_t__ ftmac100_txdes_late_collision (struct ftmac100_txdes*) ; 
 scalar_t__ ftmac100_txdes_owned_by_dma (struct ftmac100_txdes*) ; 
 int /*<<< orphan*/  ftmac100_txdes_reset (struct ftmac100_txdes*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool ftmac100_tx_complete_packet(struct ftmac100 *priv)
{
	struct net_device *netdev = priv->netdev;
	struct ftmac100_txdes *txdes;
	struct sk_buff *skb;
	dma_addr_t map;

	if (priv->tx_pending == 0)
		return false;

	txdes = ftmac100_current_clean_txdes(priv);

	if (ftmac100_txdes_owned_by_dma(txdes))
		return false;

	skb = ftmac100_txdes_get_skb(txdes);
	map = ftmac100_txdes_get_dma_addr(txdes);

	if (unlikely(ftmac100_txdes_excessive_collision(txdes) ||
		     ftmac100_txdes_late_collision(txdes))) {
		/*
		 * packet transmitted to ethernet lost due to late collision
		 * or excessive collision
		 */
		netdev->stats.tx_aborted_errors++;
	} else {
		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += skb->len;
	}

	dma_unmap_single(priv->dev, map, skb_headlen(skb), DMA_TO_DEVICE);
	dev_kfree_skb(skb);

	ftmac100_txdes_reset(txdes);

	ftmac100_tx_clean_pointer_advance(priv);

	spin_lock(&priv->tx_lock);
	priv->tx_pending--;
	spin_unlock(&priv->tx_lock);
	netif_wake_queue(netdev);

	return true;
}