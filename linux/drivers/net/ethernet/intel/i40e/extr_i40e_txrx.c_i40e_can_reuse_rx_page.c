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
struct i40e_rx_buffer {unsigned int pagecnt_bias; scalar_t__ page_offset; struct page* page; } ;

/* Variables and functions */
 scalar_t__ I40E_LAST_OFFSET ; 
 int USHRT_MAX ; 
 int /*<<< orphan*/  i40e_page_is_reusable (struct page*) ; 
 unsigned int page_count (struct page*) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool i40e_can_reuse_rx_page(struct i40e_rx_buffer *rx_buffer)
{
	unsigned int pagecnt_bias = rx_buffer->pagecnt_bias;
	struct page *page = rx_buffer->page;

	/* Is any reuse possible? */
	if (unlikely(!i40e_page_is_reusable(page)))
		return false;

#if (PAGE_SIZE < 8192)
	/* if we are only owner of page we can reuse it */
	if (unlikely((page_count(page) - pagecnt_bias) > 1))
		return false;
#else
#define I40E_LAST_OFFSET \
	(SKB_WITH_OVERHEAD(PAGE_SIZE) - I40E_RXBUFFER_2048)
	if (rx_buffer->page_offset > I40E_LAST_OFFSET)
		return false;
#endif

	/* If we have drained the page fragment pool we need to update
	 * the pagecnt_bias and page count so that we fully restock the
	 * number of references the driver holds.
	 */
	if (unlikely(pagecnt_bias == 1)) {
		page_ref_add(page, USHRT_MAX - 1);
		rx_buffer->pagecnt_bias = USHRT_MAX;
	}

	return true;
}