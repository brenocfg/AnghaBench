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
struct tx_desc {int /*<<< orphan*/  TxBuffAddr; scalar_t__ OWN; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct rtl8192_tx_ring {size_t idx; int entries; int /*<<< orphan*/  queue; struct tx_desc* desc; } ;
struct r8192_priv {int /*<<< orphan*/  irq_tx_tasklet; int /*<<< orphan*/  pdev; struct rtl8192_tx_ring* tx_ring; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BEACON_QUEUE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _rtl92e_tx_isr(struct net_device *dev, int prio)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	struct rtl8192_tx_ring *ring = &priv->tx_ring[prio];

	while (skb_queue_len(&ring->queue)) {
		struct tx_desc *entry = &ring->desc[ring->idx];
		struct sk_buff *skb;

		if (prio != BEACON_QUEUE) {
			if (entry->OWN)
				return;
			ring->idx = (ring->idx + 1) % ring->entries;
		}

		skb = __skb_dequeue(&ring->queue);
		pci_unmap_single(priv->pdev, entry->TxBuffAddr,
		skb->len, PCI_DMA_TODEVICE);

		kfree_skb(skb);
	}
	if (prio != BEACON_QUEUE)
		tasklet_schedule(&priv->irq_tx_tasklet);
}