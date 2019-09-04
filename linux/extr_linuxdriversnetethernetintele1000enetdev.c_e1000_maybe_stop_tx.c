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
struct e1000_ring {int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int __e1000_maybe_stop_tx (struct e1000_ring*,int) ; 
 int e1000_desc_unused (struct e1000_ring*) ; 

__attribute__((used)) static int e1000_maybe_stop_tx(struct e1000_ring *tx_ring, int size)
{
	BUG_ON(size > tx_ring->count);

	if (e1000_desc_unused(tx_ring) >= size)
		return 0;
	return __e1000_maybe_stop_tx(tx_ring, size);
}