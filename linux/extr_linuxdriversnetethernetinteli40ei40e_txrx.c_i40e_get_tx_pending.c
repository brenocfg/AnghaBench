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
typedef  scalar_t__ u32 ;
struct i40e_ring {scalar_t__ next_to_clean; scalar_t__ next_to_use; scalar_t__ count; int /*<<< orphan*/  tail; } ;

/* Variables and functions */
 scalar_t__ i40e_get_head (struct i40e_ring*) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 

u32 i40e_get_tx_pending(struct i40e_ring *ring, bool in_sw)
{
	u32 head, tail;

	if (!in_sw) {
		head = i40e_get_head(ring);
		tail = readl(ring->tail);
	} else {
		head = ring->next_to_clean;
		tail = ring->next_to_use;
	}

	if (head != tail)
		return (head < tail) ?
			tail - head : (tail + ring->count - head);

	return 0;
}