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
struct page {int dummy; } ;
struct efx_rx_queue {int removed_count; int added_count; int ptr_mask; int page_ptr_mask; struct page** page_ring; scalar_t__ buffer; int /*<<< orphan*/  slow_fill; struct efx_nic* efx; } ;
struct efx_rx_page_state {int /*<<< orphan*/  dma_addr; } ;
struct efx_rx_buffer {int dummy; } ;
struct efx_nic {int rx_buffer_order; TYPE_1__* pci_dev; int /*<<< orphan*/  net_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_fini_rx_buffer (struct efx_rx_queue*,struct efx_rx_buffer*) ; 
 struct efx_rx_buffer* efx_rx_buffer (struct efx_rx_queue*,unsigned int) ; 
 int /*<<< orphan*/  efx_rx_queue_index (struct efx_rx_queue*) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct efx_rx_page_state* page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

void efx_fini_rx_queue(struct efx_rx_queue *rx_queue)
{
	int i;
	struct efx_nic *efx = rx_queue->efx;
	struct efx_rx_buffer *rx_buf;

	netif_dbg(rx_queue->efx, drv, rx_queue->efx->net_dev,
		  "shutting down RX queue %d\n", efx_rx_queue_index(rx_queue));

	del_timer_sync(&rx_queue->slow_fill);

	/* Release RX buffers from the current read ptr to the write ptr */
	if (rx_queue->buffer) {
		for (i = rx_queue->removed_count; i < rx_queue->added_count;
		     i++) {
			unsigned index = i & rx_queue->ptr_mask;
			rx_buf = efx_rx_buffer(rx_queue, index);
			efx_fini_rx_buffer(rx_queue, rx_buf);
		}
	}

	/* Unmap and release the pages in the recycle ring. Remove the ring. */
	for (i = 0; i <= rx_queue->page_ptr_mask; i++) {
		struct page *page = rx_queue->page_ring[i];
		struct efx_rx_page_state *state;

		if (page == NULL)
			continue;

		state = page_address(page);
		dma_unmap_page(&efx->pci_dev->dev, state->dma_addr,
			       PAGE_SIZE << efx->rx_buffer_order,
			       DMA_FROM_DEVICE);
		put_page(page);
	}
	kfree(rx_queue->page_ring);
	rx_queue->page_ring = NULL;
}