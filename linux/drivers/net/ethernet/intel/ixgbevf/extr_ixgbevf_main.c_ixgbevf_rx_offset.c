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
struct ixgbevf_ring {int dummy; } ;

/* Variables and functions */
 unsigned int IXGBEVF_SKB_PAD ; 
 scalar_t__ ring_uses_build_skb (struct ixgbevf_ring*) ; 

__attribute__((used)) static inline unsigned int ixgbevf_rx_offset(struct ixgbevf_ring *rx_ring)
{
	return ring_uses_build_skb(rx_ring) ? IXGBEVF_SKB_PAD : 0;
}