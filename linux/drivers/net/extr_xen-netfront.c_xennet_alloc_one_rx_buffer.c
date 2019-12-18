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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct page {int dummy; } ;
struct netfront_queue {TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ RX_COPY_THRESHOLD ; 
 int __GFP_NOWARN ; 
 struct sk_buff* __netdev_alloc_skb (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *xennet_alloc_one_rx_buffer(struct netfront_queue *queue)
{
	struct sk_buff *skb;
	struct page *page;

	skb = __netdev_alloc_skb(queue->info->netdev,
				 RX_COPY_THRESHOLD + NET_IP_ALIGN,
				 GFP_ATOMIC | __GFP_NOWARN);
	if (unlikely(!skb))
		return NULL;

	page = alloc_page(GFP_ATOMIC | __GFP_NOWARN);
	if (!page) {
		kfree_skb(skb);
		return NULL;
	}
	skb_add_rx_frag(skb, 0, page, 0, 0, PAGE_SIZE);

	/* Align ip header to a 16 bytes boundary */
	skb_reserve(skb, NET_IP_ALIGN);
	skb->dev = queue->info->netdev;

	return skb;
}