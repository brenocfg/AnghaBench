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
struct ice_rx_buf {unsigned int pagecnt_bias; unsigned int page_offset; struct page* page; } ;

/* Variables and functions */
 unsigned int ICE_RXBUF_2048 ; 
 unsigned int PAGE_SIZE ; 
 int USHRT_MAX ; 
 int ice_page_is_reserved (struct page*) ; 
 unsigned int page_count (struct page*) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool ice_can_reuse_rx_page(struct ice_rx_buf *rx_buf)
{
#if (PAGE_SIZE >= 8192)
	unsigned int last_offset = PAGE_SIZE - ICE_RXBUF_2048;
#endif
	unsigned int pagecnt_bias = rx_buf->pagecnt_bias;
	struct page *page = rx_buf->page;

	/* avoid re-using remote pages */
	if (unlikely(ice_page_is_reserved(page)))
		return false;

#if (PAGE_SIZE < 8192)
	/* if we are only owner of page we can reuse it */
	if (unlikely((page_count(page) - pagecnt_bias) > 1))
		return false;
#else
	if (rx_buf->page_offset > last_offset)
		return false;
#endif /* PAGE_SIZE < 8192) */

	/* If we have drained the page fragment pool we need to update
	 * the pagecnt_bias and page count so that we fully restock the
	 * number of references the driver holds.
	 */
	if (unlikely(pagecnt_bias == 1)) {
		page_ref_add(page, USHRT_MAX - 1);
		rx_buf->pagecnt_bias = USHRT_MAX;
	}

	return true;
}