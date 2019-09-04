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
typedef  int /*<<< orphan*/  u16 ;
struct sw_rx_data {int page_offset; int /*<<< orphan*/  data; } ;
struct sk_buff {int dummy; } ;
struct qede_rx_queue {int /*<<< orphan*/  rx_buf_seg_size; } ;

/* Variables and functions */
 struct sk_buff* build_skb (void*,int /*<<< orphan*/ ) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct sk_buff *
qede_build_skb(struct qede_rx_queue *rxq,
	       struct sw_rx_data *bd, u16 len, u16 pad)
{
	struct sk_buff *skb;
	void *buf;

	buf = page_address(bd->data) + bd->page_offset;
	skb = build_skb(buf, rxq->rx_buf_seg_size);

	skb_reserve(skb, pad);
	skb_put(skb, len);

	return skb;
}