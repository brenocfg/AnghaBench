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
struct igc_rx_buffer {unsigned int pagecnt_bias; scalar_t__ page_offset; struct page* page; } ;

/* Variables and functions */
 scalar_t__ IGC_LAST_OFFSET ; 
 unsigned int USHRT_MAX ; 
 int igc_page_is_reserved (struct page*) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,unsigned int) ; 
 unsigned int page_ref_count (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool igc_can_reuse_rx_page(struct igc_rx_buffer *rx_buffer)
{
	unsigned int pagecnt_bias = rx_buffer->pagecnt_bias;
	struct page *page = rx_buffer->page;

	/* avoid re-using remote pages */
	if (unlikely(igc_page_is_reserved(page)))
		return false;

#if (PAGE_SIZE < 8192)
	/* if we are only owner of page we can reuse it */
	if (unlikely((page_ref_count(page) - pagecnt_bias) > 1))
		return false;
#else
#define IGC_LAST_OFFSET \
	(SKB_WITH_OVERHEAD(PAGE_SIZE) - IGC_RXBUFFER_2048)

	if (rx_buffer->page_offset > IGC_LAST_OFFSET)
		return false;
#endif

	/* If we have drained the page fragment pool we need to update
	 * the pagecnt_bias and page count so that we fully restock the
	 * number of references the driver holds.
	 */
	if (unlikely(!pagecnt_bias)) {
		page_ref_add(page, USHRT_MAX);
		rx_buffer->pagecnt_bias = USHRT_MAX;
	}

	return true;
}