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
struct sk_buff {scalar_t__ cb; } ;
struct rtl8180_priv {int rx_ring_sz; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  rx_ring_dma; int /*<<< orphan*/  pdev; struct sk_buff** rx_buf; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RX_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8180_free_rx_ring(struct ieee80211_hw *dev)
{
	struct rtl8180_priv *priv = dev->priv;
	int i;

	for (i = 0; i < 32; i++) {
		struct sk_buff *skb = priv->rx_buf[i];
		if (!skb)
			continue;

		pci_unmap_single(priv->pdev,
				 *((dma_addr_t *)skb->cb),
				 MAX_RX_SIZE, PCI_DMA_FROMDEVICE);
		kfree_skb(skb);
	}

	pci_free_consistent(priv->pdev, priv->rx_ring_sz * 32,
			    priv->rx_ring, priv->rx_ring_dma);
	priv->rx_ring = NULL;
}