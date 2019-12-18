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
struct i40e_rx_buffer {unsigned int page_offset; } ;
struct i40e_ring {int dummy; } ;

/* Variables and functions */
 unsigned int SKB_DATA_ALIGN (scalar_t__) ; 
 scalar_t__ i40e_rx_offset (struct i40e_ring*) ; 
 int i40e_rx_pg_size (struct i40e_ring*) ; 

__attribute__((used)) static void i40e_rx_buffer_flip(struct i40e_ring *rx_ring,
				struct i40e_rx_buffer *rx_buffer,
				unsigned int size)
{
#if (PAGE_SIZE < 8192)
	unsigned int truesize = i40e_rx_pg_size(rx_ring) / 2;

	rx_buffer->page_offset ^= truesize;
#else
	unsigned int truesize = SKB_DATA_ALIGN(i40e_rx_offset(rx_ring) + size);

	rx_buffer->page_offset += truesize;
#endif
}