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
typedef  int u32 ;
struct ravb_tx_desc {scalar_t__ die_dt; int /*<<< orphan*/  dptr; int /*<<< orphan*/  ds_tagl; } ;
struct ravb_private {int num_tx_desc; scalar_t__* cur_tx; int* dirty_tx; int* num_tx_ring; int /*<<< orphan*/ *** tx_skb; struct ravb_tx_desc** tx_ring; struct net_device_stats* stats; } ;
struct net_device_stats {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ DT_EEMPTY ; 
 scalar_t__ DT_FEMPTY ; 
 int TX_DS ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ravb_tx_free(struct net_device *ndev, int q, bool free_txed_only)
{
	struct ravb_private *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &priv->stats[q];
	int num_tx_desc = priv->num_tx_desc;
	struct ravb_tx_desc *desc;
	int free_num = 0;
	int entry;
	u32 size;

	for (; priv->cur_tx[q] - priv->dirty_tx[q] > 0; priv->dirty_tx[q]++) {
		bool txed;

		entry = priv->dirty_tx[q] % (priv->num_tx_ring[q] *
					     num_tx_desc);
		desc = &priv->tx_ring[q][entry];
		txed = desc->die_dt == DT_FEMPTY;
		if (free_txed_only && !txed)
			break;
		/* Descriptor type must be checked before all other reads */
		dma_rmb();
		size = le16_to_cpu(desc->ds_tagl) & TX_DS;
		/* Free the original skb. */
		if (priv->tx_skb[q][entry / num_tx_desc]) {
			dma_unmap_single(ndev->dev.parent, le32_to_cpu(desc->dptr),
					 size, DMA_TO_DEVICE);
			/* Last packet descriptor? */
			if (entry % num_tx_desc == num_tx_desc - 1) {
				entry /= num_tx_desc;
				dev_kfree_skb_any(priv->tx_skb[q][entry]);
				priv->tx_skb[q][entry] = NULL;
				if (txed)
					stats->tx_packets++;
			}
			free_num++;
		}
		if (txed)
			stats->tx_bytes += size;
		desc->die_dt = DT_EEMPTY;
	}
	return free_num;
}