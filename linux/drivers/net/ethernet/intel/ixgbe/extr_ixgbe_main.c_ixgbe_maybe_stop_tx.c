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
typedef  scalar_t__ u16 ;
struct ixgbe_ring {int dummy; } ;

/* Variables and functions */
 int __ixgbe_maybe_stop_tx (struct ixgbe_ring*,scalar_t__) ; 
 scalar_t__ ixgbe_desc_unused (struct ixgbe_ring*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline int ixgbe_maybe_stop_tx(struct ixgbe_ring *tx_ring, u16 size)
{
	if (likely(ixgbe_desc_unused(tx_ring) >= size))
		return 0;

	return __ixgbe_maybe_stop_tx(tx_ring, size);
}