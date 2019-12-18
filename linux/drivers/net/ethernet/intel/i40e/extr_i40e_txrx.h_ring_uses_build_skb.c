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
struct i40e_ring {int flags; } ;

/* Variables and functions */
 int I40E_RXR_FLAGS_BUILD_SKB_ENABLED ; 

__attribute__((used)) static inline bool ring_uses_build_skb(struct i40e_ring *ring)
{
	return !!(ring->flags & I40E_RXR_FLAGS_BUILD_SKB_ENABLED);
}