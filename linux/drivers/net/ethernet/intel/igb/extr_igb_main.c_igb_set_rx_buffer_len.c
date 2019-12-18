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
struct igb_adapter {int flags; scalar_t__ max_frame_size; } ;

/* Variables and functions */
 int IGB_FLAG_RX_LEGACY ; 
 scalar_t__ IGB_MAX_FRAME_BUILD_SKB ; 
 int /*<<< orphan*/  clear_ring_build_skb_enabled (struct igb_ring*) ; 
 int /*<<< orphan*/  clear_ring_uses_large_buffer (struct igb_ring*) ; 
 int /*<<< orphan*/  set_ring_build_skb_enabled (struct igb_ring*) ; 
 int /*<<< orphan*/  set_ring_uses_large_buffer (struct igb_ring*) ; 

__attribute__((used)) static void igb_set_rx_buffer_len(struct igb_adapter *adapter,
				  struct igb_ring *rx_ring)
{
	/* set build_skb and buffer size flags */
	clear_ring_build_skb_enabled(rx_ring);
	clear_ring_uses_large_buffer(rx_ring);

	if (adapter->flags & IGB_FLAG_RX_LEGACY)
		return;

	set_ring_build_skb_enabled(rx_ring);

#if (PAGE_SIZE < 8192)
	if (adapter->max_frame_size <= IGB_MAX_FRAME_BUILD_SKB)
		return;

	set_ring_uses_large_buffer(rx_ring);
#endif
}