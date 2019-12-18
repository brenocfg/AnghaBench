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
struct ef4_rx_page_state {int /*<<< orphan*/  dma_addr; } ;
struct ef4_rx_buffer {struct page* page; } ;
struct ef4_nic {int rx_buffer_order; TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ef4_rx_page_state* page_address (struct page*) ; 

__attribute__((used)) static void ef4_unmap_rx_buffer(struct ef4_nic *efx,
				struct ef4_rx_buffer *rx_buf)
{
	struct page *page = rx_buf->page;

	if (page) {
		struct ef4_rx_page_state *state = page_address(page);
		dma_unmap_page(&efx->pci_dev->dev,
			       state->dma_addr,
			       PAGE_SIZE << efx->rx_buffer_order,
			       DMA_FROM_DEVICE);
	}
}