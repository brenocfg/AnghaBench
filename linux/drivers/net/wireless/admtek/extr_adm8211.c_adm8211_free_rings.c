#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_priv {unsigned int rx_ring_size; unsigned int tx_ring_size; TYPE_2__* tx_buffers; int /*<<< orphan*/  pdev; TYPE_1__* rx_buffers; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {TYPE_3__* skb; int /*<<< orphan*/  mapping; } ;
struct TYPE_4__ {TYPE_3__* skb; int /*<<< orphan*/  mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  RX_PKT_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adm8211_free_rings(struct ieee80211_hw *dev)
{
	struct adm8211_priv *priv = dev->priv;
	unsigned int i;

	for (i = 0; i < priv->rx_ring_size; i++) {
		if (!priv->rx_buffers[i].skb)
			continue;

		pci_unmap_single(
			priv->pdev,
			priv->rx_buffers[i].mapping,
			RX_PKT_SIZE, PCI_DMA_FROMDEVICE);

		dev_kfree_skb(priv->rx_buffers[i].skb);
	}

	for (i = 0; i < priv->tx_ring_size; i++) {
		if (!priv->tx_buffers[i].skb)
			continue;

		pci_unmap_single(priv->pdev,
				 priv->tx_buffers[i].mapping,
				 priv->tx_buffers[i].skb->len,
				 PCI_DMA_TODEVICE);

		dev_kfree_skb(priv->tx_buffers[i].skb);
	}
}