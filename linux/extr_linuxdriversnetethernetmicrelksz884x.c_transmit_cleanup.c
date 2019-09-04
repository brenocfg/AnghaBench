#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ hw_owned; } ;
union desc_stat {TYPE_3__ tx; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct ksz_desc_info {int last; scalar_t__ avail; scalar_t__ alloc; int mask; struct ksz_desc* ring; } ;
struct ksz_hw {struct ksz_desc_info tx_desc_info; } ;
struct ksz_dma_buf {TYPE_4__* skb; int /*<<< orphan*/  len; int /*<<< orphan*/  dma; } ;
struct ksz_desc {TYPE_2__* phw; } ;
struct dev_info {int /*<<< orphan*/  hwlock; int /*<<< orphan*/  pdev; struct ksz_hw hw; } ;
struct TYPE_8__ {struct net_device* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_1__ ctrl; } ;

/* Variables and functions */
 struct ksz_dma_buf* DMA_BUFFER (struct ksz_desc*) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (TYPE_4__*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_desc (struct ksz_desc*,union desc_stat) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void transmit_cleanup(struct dev_info *hw_priv, int normal)
{
	int last;
	union desc_stat status;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_desc_info *info = &hw->tx_desc_info;
	struct ksz_desc *desc;
	struct ksz_dma_buf *dma_buf;
	struct net_device *dev = NULL;

	spin_lock_irq(&hw_priv->hwlock);
	last = info->last;

	while (info->avail < info->alloc) {
		/* Get next descriptor which is not hardware owned. */
		desc = &info->ring[last];
		status.data = le32_to_cpu(desc->phw->ctrl.data);
		if (status.tx.hw_owned) {
			if (normal)
				break;
			else
				reset_desc(desc, status);
		}

		dma_buf = DMA_BUFFER(desc);
		pci_unmap_single(
			hw_priv->pdev, dma_buf->dma, dma_buf->len,
			PCI_DMA_TODEVICE);

		/* This descriptor contains the last buffer in the packet. */
		if (dma_buf->skb) {
			dev = dma_buf->skb->dev;

			/* Release the packet back to network subsystem. */
			dev_kfree_skb_irq(dma_buf->skb);
			dma_buf->skb = NULL;
		}

		/* Free the transmitted descriptor. */
		last++;
		last &= info->mask;
		info->avail++;
	}
	info->last = last;
	spin_unlock_irq(&hw_priv->hwlock);

	/* Notify the network subsystem that the packet has been sent. */
	if (dev)
		netif_trans_update(dev);
}