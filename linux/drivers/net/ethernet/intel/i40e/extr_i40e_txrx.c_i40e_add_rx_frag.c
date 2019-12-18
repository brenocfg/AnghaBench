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
struct i40e_rx_buffer {unsigned int page_offset; int /*<<< orphan*/  page; } ;
struct i40e_ring {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 unsigned int SKB_DATA_ALIGN (scalar_t__) ; 
 scalar_t__ i40e_rx_offset (struct i40e_ring*) ; 
 int i40e_rx_pg_size (struct i40e_ring*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void i40e_add_rx_frag(struct i40e_ring *rx_ring,
			     struct i40e_rx_buffer *rx_buffer,
			     struct sk_buff *skb,
			     unsigned int size)
{
#if (PAGE_SIZE < 8192)
	unsigned int truesize = i40e_rx_pg_size(rx_ring) / 2;
#else
	unsigned int truesize = SKB_DATA_ALIGN(size + i40e_rx_offset(rx_ring));
#endif

	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, rx_buffer->page,
			rx_buffer->page_offset, size, truesize);

	/* page is being used so we must update the page offset */
#if (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#else
	rx_buffer->page_offset += truesize;
#endif
}