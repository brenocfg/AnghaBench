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
struct TYPE_3__ {int tx_zerocopy_sent; int /*<<< orphan*/  tx_frag_overflow; } ;
struct xenvif_queue {int /*<<< orphan*/  inflight_packets; TYPE_1__ stats; } ;
struct ubuf_info {int /*<<< orphan*/  (* callback ) (struct ubuf_info*,int) ;} ;
struct sk_buff {int truesize; unsigned int data_len; unsigned int len; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_4__ {int nr_frags; int /*<<< orphan*/  frags; struct ubuf_info* destructor_arg; struct sk_buff* frag_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_SKB_FRAGS ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  __skb_frag_set_page (int /*<<< orphan*/ *,struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skb_frag_off_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_size_set (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  skb_frag_unref (struct sk_buff*,int) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct ubuf_info*,int) ; 
 int /*<<< orphan*/  xenvif_fill_frags (struct xenvif_queue*,struct sk_buff*) ; 

__attribute__((used)) static int xenvif_handle_frag_list(struct xenvif_queue *queue, struct sk_buff *skb)
{
	unsigned int offset = skb_headlen(skb);
	skb_frag_t frags[MAX_SKB_FRAGS];
	int i, f;
	struct ubuf_info *uarg;
	struct sk_buff *nskb = skb_shinfo(skb)->frag_list;

	queue->stats.tx_zerocopy_sent += 2;
	queue->stats.tx_frag_overflow++;

	xenvif_fill_frags(queue, nskb);
	/* Subtract frags size, we will correct it later */
	skb->truesize -= skb->data_len;
	skb->len += nskb->len;
	skb->data_len += nskb->len;

	/* create a brand new frags array and coalesce there */
	for (i = 0; offset < skb->len; i++) {
		struct page *page;
		unsigned int len;

		BUG_ON(i >= MAX_SKB_FRAGS);
		page = alloc_page(GFP_ATOMIC);
		if (!page) {
			int j;
			skb->truesize += skb->data_len;
			for (j = 0; j < i; j++)
				put_page(skb_frag_page(&frags[j]));
			return -ENOMEM;
		}

		if (offset + PAGE_SIZE < skb->len)
			len = PAGE_SIZE;
		else
			len = skb->len - offset;
		if (skb_copy_bits(skb, offset, page_address(page), len))
			BUG();

		offset += len;
		__skb_frag_set_page(&frags[i], page);
		skb_frag_off_set(&frags[i], 0);
		skb_frag_size_set(&frags[i], len);
	}

	/* Release all the original (foreign) frags. */
	for (f = 0; f < skb_shinfo(skb)->nr_frags; f++)
		skb_frag_unref(skb, f);
	uarg = skb_shinfo(skb)->destructor_arg;
	/* increase inflight counter to offset decrement in callback */
	atomic_inc(&queue->inflight_packets);
	uarg->callback(uarg, true);
	skb_shinfo(skb)->destructor_arg = NULL;

	/* Fill the skb with the new (local) frags. */
	memcpy(skb_shinfo(skb)->frags, frags, i * sizeof(skb_frag_t));
	skb_shinfo(skb)->nr_frags = i;
	skb->truesize += i * PAGE_SIZE;

	return 0;
}