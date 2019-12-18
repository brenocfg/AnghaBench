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
struct tx_desc {int /*<<< orphan*/  TxBuffAddr; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct rx_desc {int OWN; } ;
struct rtl8192_tx_ring {size_t idx; int entries; int /*<<< orphan*/  queue; struct tx_desc* desc; } ;
struct r8192_priv {int rxringcount; int /*<<< orphan*/  irq_th_lock; int /*<<< orphan*/  pdev; struct rtl8192_tx_ring* tx_ring; scalar_t__* rx_idx; struct rx_desc** rx_ring; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int MAX_RX_QUEUE ; 
 int MAX_TX_QUEUE_COUNT ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rtl92e_reset_desc_ring(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	int i, rx_queue_idx;
	unsigned long flags = 0;

	for (rx_queue_idx = 0; rx_queue_idx < MAX_RX_QUEUE; rx_queue_idx++) {
		if (priv->rx_ring[rx_queue_idx]) {
			struct rx_desc *entry = NULL;

			for (i = 0; i < priv->rxringcount; i++) {
				entry = &priv->rx_ring[rx_queue_idx][i];
				entry->OWN = 1;
			}
			priv->rx_idx[rx_queue_idx] = 0;
		}
	}

	spin_lock_irqsave(&priv->irq_th_lock, flags);
	for (i = 0; i < MAX_TX_QUEUE_COUNT; i++) {
		if (priv->tx_ring[i].desc) {
			struct rtl8192_tx_ring *ring = &priv->tx_ring[i];

			while (skb_queue_len(&ring->queue)) {
				struct tx_desc *entry = &ring->desc[ring->idx];
				struct sk_buff *skb =
						 __skb_dequeue(&ring->queue);

				pci_unmap_single(priv->pdev,
						 entry->TxBuffAddr,
						 skb->len, PCI_DMA_TODEVICE);
				kfree_skb(skb);
				ring->idx = (ring->idx + 1) % ring->entries;
			}
			ring->idx = 0;
		}
	}
	spin_unlock_irqrestore(&priv->irq_th_lock, flags);
}