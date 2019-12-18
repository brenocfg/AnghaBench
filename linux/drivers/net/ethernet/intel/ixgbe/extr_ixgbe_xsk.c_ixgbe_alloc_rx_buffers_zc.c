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
struct ixgbe_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ixgbe_alloc_rx_buffers_zc (struct ixgbe_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_alloc_buffer_slow_zc ; 

void ixgbe_alloc_rx_buffers_zc(struct ixgbe_ring *rx_ring, u16 count)
{
	__ixgbe_alloc_rx_buffers_zc(rx_ring, count,
				    ixgbe_alloc_buffer_slow_zc);
}