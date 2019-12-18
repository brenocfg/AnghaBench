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
struct ixgbevf_rx_buffer {unsigned int page_offset; } ;
struct ixgbevf_ring {int dummy; } ;

/* Variables and functions */
 unsigned int IXGBEVF_SKB_PAD ; 
 unsigned int SKB_DATA_ALIGN (unsigned int) ; 
 int ixgbevf_rx_pg_size (struct ixgbevf_ring*) ; 
 scalar_t__ ring_uses_build_skb (struct ixgbevf_ring*) ; 

__attribute__((used)) static void ixgbevf_rx_buffer_flip(struct ixgbevf_ring *rx_ring,
				   struct ixgbevf_rx_buffer *rx_buffer,
				   unsigned int size)
{
#if (PAGE_SIZE < 8192)
	unsigned int truesize = ixgbevf_rx_pg_size(rx_ring) / 2;

	rx_buffer->page_offset ^= truesize;
#else
	unsigned int truesize = ring_uses_build_skb(rx_ring) ?
				SKB_DATA_ALIGN(IXGBEVF_SKB_PAD + size) :
				SKB_DATA_ALIGN(size);

	rx_buffer->page_offset += truesize;
#endif
}