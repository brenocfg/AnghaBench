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
typedef  unsigned int u64 ;
struct ixgbe_ring {unsigned int next_to_clean; unsigned int next_to_use; unsigned int count; } ;

/* Variables and functions */

__attribute__((used)) static u64 ixgbe_get_tx_pending(struct ixgbe_ring *ring)
{
	unsigned int head, tail;

	head = ring->next_to_clean;
	tail = ring->next_to_use;

	return ((head <= tail) ? tail : tail + ring->count) - head;
}