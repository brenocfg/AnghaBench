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
struct page {int dummy; } ;
struct ena_com_buf {int /*<<< orphan*/  paddr; } ;
struct ena_rx_buffer {struct page* page; struct ena_com_buf ena_buf; } ;
struct ena_ring {int /*<<< orphan*/  dev; int /*<<< orphan*/  netdev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ENA_PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rx_err ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ena_free_rx_page(struct ena_ring *rx_ring,
			     struct ena_rx_buffer *rx_info)
{
	struct page *page = rx_info->page;
	struct ena_com_buf *ena_buf = &rx_info->ena_buf;

	if (unlikely(!page)) {
		netif_warn(rx_ring->adapter, rx_err, rx_ring->netdev,
			   "Trying to free unallocated buffer\n");
		return;
	}

	dma_unmap_page(rx_ring->dev, ena_buf->paddr, ENA_PAGE_SIZE,
		       DMA_FROM_DEVICE);

	__free_page(page);
	rx_info->page = NULL;
}