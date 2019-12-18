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
struct r8192_priv {int rxringcount; int /*<<< orphan*/ ** rx_ring; int /*<<< orphan*/ * rx_ring_dma; int /*<<< orphan*/  pdev; int /*<<< orphan*/  rxbuffersize; struct sk_buff*** rx_buf; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int MAX_RX_QUEUE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_free_rx_ring(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	int i, rx_queue_idx;

	for (rx_queue_idx = 0; rx_queue_idx < MAX_RX_QUEUE;
	     rx_queue_idx++) {
		for (i = 0; i < priv->rxringcount; i++) {
			struct sk_buff *skb = priv->rx_buf[rx_queue_idx][i];

			if (!skb)
				continue;

			pci_unmap_single(priv->pdev,
				*((dma_addr_t *)skb->cb),
				priv->rxbuffersize, PCI_DMA_FROMDEVICE);
			kfree_skb(skb);
		}

		pci_free_consistent(priv->pdev,
			sizeof(*priv->rx_ring[rx_queue_idx]) *
			priv->rxringcount,
			priv->rx_ring[rx_queue_idx],
			priv->rx_ring_dma[rx_queue_idx]);
		priv->rx_ring[rx_queue_idx] = NULL;
	}
}