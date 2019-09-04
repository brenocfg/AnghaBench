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
struct i40e_rx_buffer {scalar_t__ pagecnt_bias; int /*<<< orphan*/  page_offset; struct page* page; int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  alloc_page_failed; int /*<<< orphan*/  page_reuse_count; } ;
struct i40e_ring {TYPE_1__ rx_stats; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  I40E_RX_DMA_ATTR ; 
 scalar_t__ USHRT_MAX ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* dev_alloc_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_page_attrs (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_rx_offset (struct i40e_ring*) ; 
 int /*<<< orphan*/  i40e_rx_pg_order (struct i40e_ring*) ; 
 int /*<<< orphan*/  i40e_rx_pg_size (struct i40e_ring*) ; 
 scalar_t__ likely (struct page*) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool i40e_alloc_mapped_page(struct i40e_ring *rx_ring,
				   struct i40e_rx_buffer *bi)
{
	struct page *page = bi->page;
	dma_addr_t dma;

	/* since we are recycling buffers we should seldom need to alloc */
	if (likely(page)) {
		rx_ring->rx_stats.page_reuse_count++;
		return true;
	}

	/* alloc new page for storage */
	page = dev_alloc_pages(i40e_rx_pg_order(rx_ring));
	if (unlikely(!page)) {
		rx_ring->rx_stats.alloc_page_failed++;
		return false;
	}

	/* map page for use */
	dma = dma_map_page_attrs(rx_ring->dev, page, 0,
				 i40e_rx_pg_size(rx_ring),
				 DMA_FROM_DEVICE,
				 I40E_RX_DMA_ATTR);

	/* if mapping failed free memory back to system since
	 * there isn't much point in holding memory we can't use
	 */
	if (dma_mapping_error(rx_ring->dev, dma)) {
		__free_pages(page, i40e_rx_pg_order(rx_ring));
		rx_ring->rx_stats.alloc_page_failed++;
		return false;
	}

	bi->dma = dma;
	bi->page = page;
	bi->page_offset = i40e_rx_offset(rx_ring);
	page_ref_add(page, USHRT_MAX - 1);
	bi->pagecnt_bias = USHRT_MAX;

	return true;
}