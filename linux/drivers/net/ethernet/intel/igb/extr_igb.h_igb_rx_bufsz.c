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
 unsigned int IGB_MAX_FRAME_BUILD_SKB ; 
 unsigned int IGB_RXBUFFER_2048 ; 
 unsigned int IGB_RXBUFFER_3072 ; 
 unsigned int IGB_TS_HDR_LEN ; 
 scalar_t__ ring_uses_build_skb (struct igb_ring*) ; 
 scalar_t__ ring_uses_large_buffer (struct igb_ring*) ; 

__attribute__((used)) static inline unsigned int igb_rx_bufsz(struct igb_ring *ring)
{
#if (PAGE_SIZE < 8192)
	if (ring_uses_large_buffer(ring))
		return IGB_RXBUFFER_3072;

	if (ring_uses_build_skb(ring))
		return IGB_MAX_FRAME_BUILD_SKB + IGB_TS_HDR_LEN;
#endif
	return IGB_RXBUFFER_2048;
}