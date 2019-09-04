#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pkt_len; } ;
union ice_32b_rx_flex_desc {TYPE_1__ wb; } ;
struct sk_buff {int dummy; } ;
struct page {int dummy; } ;
struct ice_rx_buf {int page_offset; struct page* page; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (unsigned int,int) ; 
 unsigned int ICE_RXBUF_2048 ; 
 unsigned int ICE_RX_FLX_DESC_PKT_LEN_M ; 
 unsigned int ICE_RX_HDR_SIZE ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int ice_page_is_reserved (struct page*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* page_address (struct page*) ; 
 int page_count (struct page*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,struct page*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  skb_is_nonlinear (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool ice_add_rx_frag(struct ice_rx_buf *rx_buf,
			    union ice_32b_rx_flex_desc *rx_desc,
			    struct sk_buff *skb)
{
#if (PAGE_SIZE < 8192)
	unsigned int truesize = ICE_RXBUF_2048;
#else
	unsigned int last_offset = PAGE_SIZE - ICE_RXBUF_2048;
	unsigned int truesize;
#endif /* PAGE_SIZE < 8192) */

	struct page *page;
	unsigned int size;

	size = le16_to_cpu(rx_desc->wb.pkt_len) &
		ICE_RX_FLX_DESC_PKT_LEN_M;

	page = rx_buf->page;

#if (PAGE_SIZE >= 8192)
	truesize = ALIGN(size, L1_CACHE_BYTES);
#endif /* PAGE_SIZE >= 8192) */

	/* will the data fit in the skb we allocated? if so, just
	 * copy it as it is pretty small anyway
	 */
	if (size <= ICE_RX_HDR_SIZE && !skb_is_nonlinear(skb)) {
		unsigned char *va = page_address(page) + rx_buf->page_offset;

		memcpy(__skb_put(skb, size), va, ALIGN(size, sizeof(long)));

		/* page is not reserved, we can reuse buffer as-is */
		if (likely(!ice_page_is_reserved(page)))
			return true;

		/* this page cannot be reused so discard it */
		__free_pages(page, 0);
		return false;
	}

	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page,
			rx_buf->page_offset, size, truesize);

	/* avoid re-using remote pages */
	if (unlikely(ice_page_is_reserved(page)))
		return false;

#if (PAGE_SIZE < 8192)
	/* if we are only owner of page we can reuse it */
	if (unlikely(page_count(page) != 1))
		return false;

	/* flip page offset to other buffer */
	rx_buf->page_offset ^= truesize;
#else
	/* move offset up to the next cache line */
	rx_buf->page_offset += truesize;

	if (rx_buf->page_offset > last_offset)
		return false;
#endif /* PAGE_SIZE < 8192) */

	/* Even if we own the page, we are not allowed to use atomic_set()
	 * This would break get_page_unless_zero() users.
	 */
	get_page(rx_buf->page);

	return true;
}