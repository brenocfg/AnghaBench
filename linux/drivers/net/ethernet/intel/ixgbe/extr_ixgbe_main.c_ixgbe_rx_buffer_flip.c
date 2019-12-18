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
struct ixgbe_rx_buffer {unsigned int page_offset; } ;
struct ixgbe_ring {int dummy; } ;

/* Variables and functions */
 unsigned int IXGBE_SKB_PAD ; 
 unsigned int SKB_DATA_ALIGN (unsigned int) ; 
 int ixgbe_rx_pg_size (struct ixgbe_ring*) ; 
 scalar_t__ ring_uses_build_skb (struct ixgbe_ring*) ; 

__attribute__((used)) static void ixgbe_rx_buffer_flip(struct ixgbe_ring *rx_ring,
				 struct ixgbe_rx_buffer *rx_buffer,
				 unsigned int size)
{
#if (PAGE_SIZE < 8192)
	unsigned int truesize = ixgbe_rx_pg_size(rx_ring) / 2;

	rx_buffer->page_offset ^= truesize;
#else
	unsigned int truesize = ring_uses_build_skb(rx_ring) ?
				SKB_DATA_ALIGN(IXGBE_SKB_PAD + size) :
				SKB_DATA_ALIGN(size);

	rx_buffer->page_offset += truesize;
#endif
}