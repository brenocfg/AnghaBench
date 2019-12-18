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
struct sk_buff {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MT_DMA_HDR_LEN ; 
 scalar_t__ MT_SKB_HEAD_LEN ; 
 scalar_t__ SKB_WITH_OVERHEAD (int) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int) ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 struct sk_buff* build_skb (void*,int) ; 
 int page_address (struct page*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,struct page*,void*,scalar_t__,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 struct page* virt_to_head_page (void*) ; 

__attribute__((used)) static struct sk_buff *
mt76u_build_rx_skb(void *data, int len, int buf_size)
{
	struct sk_buff *skb;

	if (SKB_WITH_OVERHEAD(buf_size) < MT_DMA_HDR_LEN + len) {
		struct page *page;

		/* slow path, not enough space for data and
		 * skb_shared_info
		 */
		skb = alloc_skb(MT_SKB_HEAD_LEN, GFP_ATOMIC);
		if (!skb)
			return NULL;

		skb_put_data(skb, data + MT_DMA_HDR_LEN, MT_SKB_HEAD_LEN);
		data += (MT_DMA_HDR_LEN + MT_SKB_HEAD_LEN);
		page = virt_to_head_page(data);
		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
				page, data - page_address(page),
				len - MT_SKB_HEAD_LEN, buf_size);

		return skb;
	}

	/* fast path */
	skb = build_skb(data, buf_size);
	if (!skb)
		return NULL;

	skb_reserve(skb, MT_DMA_HDR_LEN);
	__skb_put(skb, len);

	return skb;
}