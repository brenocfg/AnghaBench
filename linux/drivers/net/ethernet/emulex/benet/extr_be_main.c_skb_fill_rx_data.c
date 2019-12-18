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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ data_len; int /*<<< orphan*/  truesize; scalar_t__ len; int /*<<< orphan*/  tail; int /*<<< orphan*/  data; } ;
struct be_rx_page_info {scalar_t__ page_offset; int /*<<< orphan*/ * page; } ;
struct be_rx_obj {int dummy; } ;
struct be_rx_compl_info {scalar_t__ pkt_size; int num_rcvd; } ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 scalar_t__ BE_HDR_LEN ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ ETH_HLEN ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 struct be_rx_page_info* get_rx_page_info (struct be_rx_obj*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * page_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 scalar_t__ rx_frag_size ; 
 int /*<<< orphan*/  skb_frag_off_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  skb_frag_set_page (struct sk_buff*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_size_add (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  skb_frag_size_set (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void skb_fill_rx_data(struct be_rx_obj *rxo, struct sk_buff *skb,
			     struct be_rx_compl_info *rxcp)
{
	struct be_rx_page_info *page_info;
	u16 i, j;
	u16 hdr_len, curr_frag_len, remaining;
	u8 *start;

	page_info = get_rx_page_info(rxo);
	start = page_address(page_info->page) + page_info->page_offset;
	prefetch(start);

	/* Copy data in the first descriptor of this completion */
	curr_frag_len = min(rxcp->pkt_size, rx_frag_size);

	skb->len = curr_frag_len;
	if (curr_frag_len <= BE_HDR_LEN) { /* tiny packet */
		memcpy(skb->data, start, curr_frag_len);
		/* Complete packet has now been moved to data */
		put_page(page_info->page);
		skb->data_len = 0;
		skb->tail += curr_frag_len;
	} else {
		hdr_len = ETH_HLEN;
		memcpy(skb->data, start, hdr_len);
		skb_shinfo(skb)->nr_frags = 1;
		skb_frag_set_page(skb, 0, page_info->page);
		skb_frag_off_set(&skb_shinfo(skb)->frags[0],
				 page_info->page_offset + hdr_len);
		skb_frag_size_set(&skb_shinfo(skb)->frags[0],
				  curr_frag_len - hdr_len);
		skb->data_len = curr_frag_len - hdr_len;
		skb->truesize += rx_frag_size;
		skb->tail += hdr_len;
	}
	page_info->page = NULL;

	if (rxcp->pkt_size <= rx_frag_size) {
		BUG_ON(rxcp->num_rcvd != 1);
		return;
	}

	/* More frags present for this completion */
	remaining = rxcp->pkt_size - curr_frag_len;
	for (i = 1, j = 0; i < rxcp->num_rcvd; i++) {
		page_info = get_rx_page_info(rxo);
		curr_frag_len = min(remaining, rx_frag_size);

		/* Coalesce all frags from the same physical page in one slot */
		if (page_info->page_offset == 0) {
			/* Fresh page */
			j++;
			skb_frag_set_page(skb, j, page_info->page);
			skb_frag_off_set(&skb_shinfo(skb)->frags[j],
					 page_info->page_offset);
			skb_frag_size_set(&skb_shinfo(skb)->frags[j], 0);
			skb_shinfo(skb)->nr_frags++;
		} else {
			put_page(page_info->page);
		}

		skb_frag_size_add(&skb_shinfo(skb)->frags[j], curr_frag_len);
		skb->len += curr_frag_len;
		skb->data_len += curr_frag_len;
		skb->truesize += rx_frag_size;
		remaining -= curr_frag_len;
		page_info->page = NULL;
	}
	BUG_ON(j > MAX_SKB_FRAGS);
}