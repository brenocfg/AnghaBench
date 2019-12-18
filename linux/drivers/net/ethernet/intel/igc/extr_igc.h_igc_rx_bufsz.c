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
struct igc_ring {int dummy; } ;

/* Variables and functions */
 unsigned int IGC_MAX_FRAME_BUILD_SKB ; 
 unsigned int IGC_RXBUFFER_2048 ; 
 unsigned int IGC_RXBUFFER_3072 ; 
 unsigned int IGC_TS_HDR_LEN ; 
 scalar_t__ ring_uses_build_skb (struct igc_ring*) ; 
 scalar_t__ ring_uses_large_buffer (struct igc_ring*) ; 

__attribute__((used)) static inline unsigned int igc_rx_bufsz(struct igc_ring *ring)
{
#if (PAGE_SIZE < 8192)
	if (ring_uses_large_buffer(ring))
		return IGC_RXBUFFER_3072;

	if (ring_uses_build_skb(ring))
		return IGC_MAX_FRAME_BUILD_SKB + IGC_TS_HDR_LEN;
#endif
	return IGC_RXBUFFER_2048;
}