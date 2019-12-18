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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct e1000_ring {unsigned int count; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/  size; int /*<<< orphan*/  desc; int /*<<< orphan*/ * rx_skb_top; struct e1000_buffer* buffer_info; struct e1000_adapter* adapter; } ;
struct e1000_ps_page {int /*<<< orphan*/ * page; scalar_t__ dma; } ;
struct e1000_buffer {struct e1000_ps_page* ps_pages; int /*<<< orphan*/ * skb; int /*<<< orphan*/ * page; scalar_t__ dma; } ;
struct e1000_adapter {scalar_t__ clean_rx; int /*<<< orphan*/  flags2; int /*<<< orphan*/  rx_ps_bsize0; int /*<<< orphan*/  rx_buffer_len; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  FLAG2_IS_DISCARDING ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned int PS_PAGE_BUFFERS ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_clean_jumbo_rx_irq ; 
 scalar_t__ e1000_clean_rx_irq ; 
 scalar_t__ e1000_clean_rx_irq_ps ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void e1000_clean_rx_ring(struct e1000_ring *rx_ring)
{
	struct e1000_adapter *adapter = rx_ring->adapter;
	struct e1000_buffer *buffer_info;
	struct e1000_ps_page *ps_page;
	struct pci_dev *pdev = adapter->pdev;
	unsigned int i, j;

	/* Free all the Rx ring sk_buffs */
	for (i = 0; i < rx_ring->count; i++) {
		buffer_info = &rx_ring->buffer_info[i];
		if (buffer_info->dma) {
			if (adapter->clean_rx == e1000_clean_rx_irq)
				dma_unmap_single(&pdev->dev, buffer_info->dma,
						 adapter->rx_buffer_len,
						 DMA_FROM_DEVICE);
			else if (adapter->clean_rx == e1000_clean_jumbo_rx_irq)
				dma_unmap_page(&pdev->dev, buffer_info->dma,
					       PAGE_SIZE, DMA_FROM_DEVICE);
			else if (adapter->clean_rx == e1000_clean_rx_irq_ps)
				dma_unmap_single(&pdev->dev, buffer_info->dma,
						 adapter->rx_ps_bsize0,
						 DMA_FROM_DEVICE);
			buffer_info->dma = 0;
		}

		if (buffer_info->page) {
			put_page(buffer_info->page);
			buffer_info->page = NULL;
		}

		if (buffer_info->skb) {
			dev_kfree_skb(buffer_info->skb);
			buffer_info->skb = NULL;
		}

		for (j = 0; j < PS_PAGE_BUFFERS; j++) {
			ps_page = &buffer_info->ps_pages[j];
			if (!ps_page->page)
				break;
			dma_unmap_page(&pdev->dev, ps_page->dma, PAGE_SIZE,
				       DMA_FROM_DEVICE);
			ps_page->dma = 0;
			put_page(ps_page->page);
			ps_page->page = NULL;
		}
	}

	/* there also may be some cached data from a chained receive */
	if (rx_ring->rx_skb_top) {
		dev_kfree_skb(rx_ring->rx_skb_top);
		rx_ring->rx_skb_top = NULL;
	}

	/* Zero out the descriptor ring */
	memset(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
	adapter->flags2 &= ~FLAG2_IS_DISCARDING;
}