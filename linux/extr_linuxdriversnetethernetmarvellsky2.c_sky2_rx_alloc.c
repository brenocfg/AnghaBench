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
struct sky2_port {int rx_nfrags; TYPE_1__* hw; scalar_t__ rx_data_size; int /*<<< orphan*/  netdev; } ;
struct sk_buff {int data; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 unsigned char* NET_IP_ALIGN ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned char* PTR_ALIGN (int,int) ; 
 int SKY2_HW_RAM_BUFFER ; 
 struct sk_buff* __netdev_alloc_skb (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned char*) ; 
 scalar_t__ sky2_rx_pad (TYPE_1__*) ; 

__attribute__((used)) static struct sk_buff *sky2_rx_alloc(struct sky2_port *sky2, gfp_t gfp)
{
	struct sk_buff *skb;
	int i;

	skb = __netdev_alloc_skb(sky2->netdev,
				 sky2->rx_data_size + sky2_rx_pad(sky2->hw),
				 gfp);
	if (!skb)
		goto nomem;

	if (sky2->hw->flags & SKY2_HW_RAM_BUFFER) {
		unsigned char *start;
		/*
		 * Workaround for a bug in FIFO that cause hang
		 * if the FIFO if the receive buffer is not 64 byte aligned.
		 * The buffer returned from netdev_alloc_skb is
		 * aligned except if slab debugging is enabled.
		 */
		start = PTR_ALIGN(skb->data, 8);
		skb_reserve(skb, start - skb->data);
	} else
		skb_reserve(skb, NET_IP_ALIGN);

	for (i = 0; i < sky2->rx_nfrags; i++) {
		struct page *page = alloc_page(gfp);

		if (!page)
			goto free_partial;
		skb_fill_page_desc(skb, i, page, 0, PAGE_SIZE);
	}

	return skb;
free_partial:
	kfree_skb(skb);
nomem:
	return NULL;
}