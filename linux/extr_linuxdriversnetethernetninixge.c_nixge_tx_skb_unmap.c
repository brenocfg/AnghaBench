#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nixge_tx_skb {int /*<<< orphan*/ * skb; scalar_t__ mapping; int /*<<< orphan*/  size; scalar_t__ mapped_as_page; } ;
struct nixge_priv {TYPE_2__* ndev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nixge_tx_skb_unmap(struct nixge_priv *priv,
			       struct nixge_tx_skb *tx_skb)
{
	if (tx_skb->mapping) {
		if (tx_skb->mapped_as_page)
			dma_unmap_page(priv->ndev->dev.parent, tx_skb->mapping,
				       tx_skb->size, DMA_TO_DEVICE);
		else
			dma_unmap_single(priv->ndev->dev.parent,
					 tx_skb->mapping,
					 tx_skb->size, DMA_TO_DEVICE);
		tx_skb->mapping = 0;
	}

	if (tx_skb->skb) {
		dev_kfree_skb_any(tx_skb->skb);
		tx_skb->skb = NULL;
	}
}