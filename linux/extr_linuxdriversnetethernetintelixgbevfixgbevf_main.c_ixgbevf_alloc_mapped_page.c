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
struct ixgbevf_rx_buffer {int pagecnt_bias; int /*<<< orphan*/  page_offset; struct page* page; int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  alloc_rx_page; int /*<<< orphan*/  alloc_rx_page_failed; } ;
struct ixgbevf_ring {TYPE_1__ rx_stats; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IXGBEVF_RX_DMA_ATTR ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* dev_alloc_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_page_attrs (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbevf_rx_offset (struct ixgbevf_ring*) ; 
 int /*<<< orphan*/  ixgbevf_rx_pg_order (struct ixgbevf_ring*) ; 
 int /*<<< orphan*/  ixgbevf_rx_pg_size (struct ixgbevf_ring*) ; 
 scalar_t__ likely (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool ixgbevf_alloc_mapped_page(struct ixgbevf_ring *rx_ring,
				      struct ixgbevf_rx_buffer *bi)
{
	struct page *page = bi->page;
	dma_addr_t dma;

	/* since we are recycling buffers we should seldom need to alloc */
	if (likely(page))
		return true;

	/* alloc new page for storage */
	page = dev_alloc_pages(ixgbevf_rx_pg_order(rx_ring));
	if (unlikely(!page)) {
		rx_ring->rx_stats.alloc_rx_page_failed++;
		return false;
	}

	/* map page for use */
	dma = dma_map_page_attrs(rx_ring->dev, page, 0,
				 ixgbevf_rx_pg_size(rx_ring),
				 DMA_FROM_DEVICE, IXGBEVF_RX_DMA_ATTR);

	/* if mapping failed free memory back to system since
	 * there isn't much point in holding memory we can't use
	 */
	if (dma_mapping_error(rx_ring->dev, dma)) {
		__free_pages(page, ixgbevf_rx_pg_order(rx_ring));

		rx_ring->rx_stats.alloc_rx_page_failed++;
		return false;
	}

	bi->dma = dma;
	bi->page = page;
	bi->page_offset = ixgbevf_rx_offset(rx_ring);
	bi->pagecnt_bias = 1;
	rx_ring->rx_stats.alloc_rx_page++;

	return true;
}