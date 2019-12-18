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
struct sge_fl {int /*<<< orphan*/  buf_size; int /*<<< orphan*/  alloc_size; scalar_t__ use_pages; } ;
struct TYPE_2__ {int /*<<< orphan*/ * page; int /*<<< orphan*/  mapping; int /*<<< orphan*/ * p_cnt; } ;
struct rx_sw_desc {int /*<<< orphan*/ * skb; TYPE_1__ pg_chunk; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dma_addr ; 
 int /*<<< orphan*/  dma_unmap_addr (struct rx_sw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_rx_desc(struct pci_dev *pdev, const struct sge_fl *q,
			  struct rx_sw_desc *d)
{
	if (q->use_pages && d->pg_chunk.page) {
		(*d->pg_chunk.p_cnt)--;
		if (!*d->pg_chunk.p_cnt)
			pci_unmap_page(pdev,
				       d->pg_chunk.mapping,
				       q->alloc_size, PCI_DMA_FROMDEVICE);

		put_page(d->pg_chunk.page);
		d->pg_chunk.page = NULL;
	} else {
		pci_unmap_single(pdev, dma_unmap_addr(d, dma_addr),
				 q->buf_size, PCI_DMA_FROMDEVICE);
		kfree_skb(d->skb);
		d->skb = NULL;
	}
}