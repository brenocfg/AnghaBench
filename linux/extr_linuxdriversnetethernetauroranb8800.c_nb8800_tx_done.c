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
struct TYPE_2__ {int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  dev; } ;
struct nb8800_tx_desc {scalar_t__ report; } ;
struct nb8800_tx_buf {int ready; struct sk_buff* skb; int /*<<< orphan*/  dma_len; int /*<<< orphan*/  dma_addr; } ;
struct nb8800_priv {unsigned int tx_next; unsigned int tx_done; int /*<<< orphan*/  tx_free; struct nb8800_tx_buf* tx_bufs; struct nb8800_tx_desc* tx_descs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ IS_TX_ERROR (scalar_t__) ; 
 scalar_t__ TX_BYTES_TRANSFERRED (scalar_t__) ; 
 unsigned int TX_DESC_COUNT ; 
 scalar_t__ TX_EARLY_COLLISIONS (scalar_t__) ; 
 int /*<<< orphan*/  atomic_add (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nb8800_tx_error (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_completed_queue (struct net_device*,unsigned int,unsigned int) ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static void nb8800_tx_done(struct net_device *dev)
{
	struct nb8800_priv *priv = netdev_priv(dev);
	unsigned int limit = priv->tx_next;
	unsigned int done = priv->tx_done;
	unsigned int packets = 0;
	unsigned int len = 0;

	while (done != limit) {
		struct nb8800_tx_desc *txd = &priv->tx_descs[done];
		struct nb8800_tx_buf *txb = &priv->tx_bufs[done];
		struct sk_buff *skb;

		if (!txd->report)
			break;

		skb = txb->skb;
		len += skb->len;

		dma_unmap_single(&dev->dev, txb->dma_addr, txb->dma_len,
				 DMA_TO_DEVICE);

		if (IS_TX_ERROR(txd->report)) {
			nb8800_tx_error(dev, txd->report);
			kfree_skb(skb);
		} else {
			consume_skb(skb);
		}

		dev->stats.tx_packets++;
		dev->stats.tx_bytes += TX_BYTES_TRANSFERRED(txd->report);
		dev->stats.collisions += TX_EARLY_COLLISIONS(txd->report);

		txb->skb = NULL;
		txb->ready = false;
		txd->report = 0;

		done = (done + 1) % TX_DESC_COUNT;
		packets++;
	}

	if (packets) {
		smp_mb__before_atomic();
		atomic_add(packets, &priv->tx_free);
		netdev_completed_queue(dev, packets, len);
		netif_wake_queue(dev);
		priv->tx_done = done;
	}
}