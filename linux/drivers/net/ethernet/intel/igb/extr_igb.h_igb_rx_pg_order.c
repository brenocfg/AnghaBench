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
struct igb_ring {int dummy; } ;

/* Variables and functions */
 scalar_t__ ring_uses_large_buffer (struct igb_ring*) ; 

__attribute__((used)) static inline unsigned int igb_rx_pg_order(struct igb_ring *ring)
{
#if (PAGE_SIZE < 8192)
	if (ring_uses_large_buffer(ring))
		return 1;
#endif
	return 0;
}