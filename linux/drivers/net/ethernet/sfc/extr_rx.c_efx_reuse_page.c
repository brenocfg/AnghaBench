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
struct efx_rx_queue {unsigned int page_remove; unsigned int page_ptr_mask; unsigned int page_add; int /*<<< orphan*/  page_recycle_failed; int /*<<< orphan*/  page_recycle_count; struct page** page_ring; struct efx_nic* efx; } ;
struct efx_rx_page_state {int /*<<< orphan*/  dma_addr; } ;
struct efx_nic {int rx_buffer_order; TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct efx_rx_page_state* page_address (struct page*) ; 
 int page_count (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static struct page *efx_reuse_page(struct efx_rx_queue *rx_queue)
{
	struct efx_nic *efx = rx_queue->efx;
	struct page *page;
	struct efx_rx_page_state *state;
	unsigned index;

	index = rx_queue->page_remove & rx_queue->page_ptr_mask;
	page = rx_queue->page_ring[index];
	if (page == NULL)
		return NULL;

	rx_queue->page_ring[index] = NULL;
	/* page_remove cannot exceed page_add. */
	if (rx_queue->page_remove != rx_queue->page_add)
		++rx_queue->page_remove;

	/* If page_count is 1 then we hold the only reference to this page. */
	if (page_count(page) == 1) {
		++rx_queue->page_recycle_count;
		return page;
	} else {
		state = page_address(page);
		dma_unmap_page(&efx->pci_dev->dev, state->dma_addr,
			       PAGE_SIZE << efx->rx_buffer_order,
			       DMA_FROM_DEVICE);
		put_page(page);
		++rx_queue->page_recycle_failed;
	}

	return NULL;
}