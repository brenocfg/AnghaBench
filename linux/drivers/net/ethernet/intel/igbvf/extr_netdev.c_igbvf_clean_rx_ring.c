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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct igbvf_ring {unsigned int count; unsigned long size; scalar_t__ tail; scalar_t__ head; scalar_t__ next_to_use; scalar_t__ next_to_clean; struct igbvf_buffer* desc; struct igbvf_buffer* buffer_info; struct igbvf_adapter* adapter; } ;
struct igbvf_buffer {scalar_t__ page_offset; scalar_t__ page_dma; int /*<<< orphan*/ * page; int /*<<< orphan*/ * skb; scalar_t__ dma; } ;
struct TYPE_2__ {scalar_t__ hw_addr; } ;
struct igbvf_adapter {TYPE_1__ hw; scalar_t__ rx_buffer_len; scalar_t__ rx_ps_hdr_size; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct igbvf_buffer*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void igbvf_clean_rx_ring(struct igbvf_ring *rx_ring)
{
	struct igbvf_adapter *adapter = rx_ring->adapter;
	struct igbvf_buffer *buffer_info;
	struct pci_dev *pdev = adapter->pdev;
	unsigned long size;
	unsigned int i;

	if (!rx_ring->buffer_info)
		return;

	/* Free all the Rx ring sk_buffs */
	for (i = 0; i < rx_ring->count; i++) {
		buffer_info = &rx_ring->buffer_info[i];
		if (buffer_info->dma) {
			if (adapter->rx_ps_hdr_size) {
				dma_unmap_single(&pdev->dev, buffer_info->dma,
						 adapter->rx_ps_hdr_size,
						 DMA_FROM_DEVICE);
			} else {
				dma_unmap_single(&pdev->dev, buffer_info->dma,
						 adapter->rx_buffer_len,
						 DMA_FROM_DEVICE);
			}
			buffer_info->dma = 0;
		}

		if (buffer_info->skb) {
			dev_kfree_skb(buffer_info->skb);
			buffer_info->skb = NULL;
		}

		if (buffer_info->page) {
			if (buffer_info->page_dma)
				dma_unmap_page(&pdev->dev,
					       buffer_info->page_dma,
					       PAGE_SIZE / 2,
					       DMA_FROM_DEVICE);
			put_page(buffer_info->page);
			buffer_info->page = NULL;
			buffer_info->page_dma = 0;
			buffer_info->page_offset = 0;
		}
	}

	size = sizeof(struct igbvf_buffer) * rx_ring->count;
	memset(rx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */
	memset(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	writel(0, adapter->hw.hw_addr + rx_ring->head);
	writel(0, adapter->hw.hw_addr + rx_ring->tail);
}