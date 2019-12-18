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
struct sk_buff {scalar_t__ len; } ;
struct net_device_stats {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; } ;
struct net_device {int /*<<< orphan*/  dev; struct net_device_stats stats; } ;
struct buffer_state {struct sk_buff* skb; } ;
struct arc_emac_priv {unsigned int txbd_dirty; struct buffer_state* tx_buff; struct arc_emac_bd* txbd; } ;
struct arc_emac_bd {int /*<<< orphan*/  info; scalar_t__ data; } ;

/* Variables and functions */
 unsigned int DEFR ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned int DROP ; 
 unsigned int FIRST_OR_LAST_MASK ; 
 unsigned int FOR_EMAC ; 
 unsigned int LTCL ; 
 unsigned int TX_BD_NUM ; 
 unsigned int UFLO ; 
 int /*<<< orphan*/  addr ; 
 scalar_t__ arc_emac_tx_avail (struct arc_emac_priv*) ; 
 int /*<<< orphan*/  dev_consume_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct buffer_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct buffer_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 scalar_t__ likely (unsigned int) ; 
 struct arc_emac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static void arc_emac_tx_clean(struct net_device *ndev)
{
	struct arc_emac_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	unsigned int i;

	for (i = 0; i < TX_BD_NUM; i++) {
		unsigned int *txbd_dirty = &priv->txbd_dirty;
		struct arc_emac_bd *txbd = &priv->txbd[*txbd_dirty];
		struct buffer_state *tx_buff = &priv->tx_buff[*txbd_dirty];
		struct sk_buff *skb = tx_buff->skb;
		unsigned int info = le32_to_cpu(txbd->info);

		if ((info & FOR_EMAC) || !txbd->data || !skb)
			break;

		if (unlikely(info & (DROP | DEFR | LTCL | UFLO))) {
			stats->tx_errors++;
			stats->tx_dropped++;

			if (info & DEFR)
				stats->tx_carrier_errors++;

			if (info & LTCL)
				stats->collisions++;

			if (info & UFLO)
				stats->tx_fifo_errors++;
		} else if (likely(info & FIRST_OR_LAST_MASK)) {
			stats->tx_packets++;
			stats->tx_bytes += skb->len;
		}

		dma_unmap_single(&ndev->dev, dma_unmap_addr(tx_buff, addr),
				 dma_unmap_len(tx_buff, len), DMA_TO_DEVICE);

		/* return the sk_buff to system */
		dev_consume_skb_irq(skb);

		txbd->data = 0;
		txbd->info = 0;
		tx_buff->skb = NULL;

		*txbd_dirty = (*txbd_dirty + 1) % TX_BD_NUM;
	}

	/* Ensure that txbd_dirty is visible to tx() before checking
	 * for queue stopped.
	 */
	smp_mb();

	if (netif_queue_stopped(ndev) && arc_emac_tx_avail(priv))
		netif_wake_queue(ndev);
}