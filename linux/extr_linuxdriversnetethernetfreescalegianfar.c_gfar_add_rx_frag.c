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
typedef  int u32 ;
struct sk_buff {scalar_t__ len; } ;
struct page {int dummy; } ;
struct gfar_rx_buff {scalar_t__ page_offset; struct page* page; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int BD_LENGTH_MASK ; 
 int BD_LFLAG (int /*<<< orphan*/ ) ; 
 scalar_t__ GFAR_RXB_TRUESIZE ; 
 int /*<<< orphan*/  RXBD_LAST ; 
 scalar_t__ RXBUF_ALIGNMENT ; 
 scalar_t__ likely (int) ; 
 int page_count (struct page*) ; 
 scalar_t__ page_is_pfmemalloc (struct page*) ; 
 int /*<<< orphan*/  page_ref_inc (struct page*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,struct page*,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool gfar_add_rx_frag(struct gfar_rx_buff *rxb, u32 lstatus,
			     struct sk_buff *skb, bool first)
{
	int size = lstatus & BD_LENGTH_MASK;
	struct page *page = rxb->page;

	if (likely(first)) {
		skb_put(skb, size);
	} else {
		/* the last fragments' length contains the full frame length */
		if (lstatus & BD_LFLAG(RXBD_LAST))
			size -= skb->len;

		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page,
				rxb->page_offset + RXBUF_ALIGNMENT,
				size, GFAR_RXB_TRUESIZE);
	}

	/* try reuse page */
	if (unlikely(page_count(page) != 1 || page_is_pfmemalloc(page)))
		return false;

	/* change offset to the other half */
	rxb->page_offset ^= GFAR_RXB_TRUESIZE;

	page_ref_inc(page);

	return true;
}