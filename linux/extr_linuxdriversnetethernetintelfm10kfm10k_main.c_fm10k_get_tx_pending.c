#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct fm10k_ring {scalar_t__ next_to_clean; scalar_t__ next_to_use; scalar_t__ count; int /*<<< orphan*/  reg_idx; TYPE_1__* q_vector; } ;
struct fm10k_hw {int dummy; } ;
struct fm10k_intfc {struct fm10k_hw hw; } ;
struct TYPE_2__ {struct fm10k_intfc* interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_TDH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM10K_TDT (int /*<<< orphan*/ ) ; 
 scalar_t__ fm10k_read_reg (struct fm10k_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

u64 fm10k_get_tx_pending(struct fm10k_ring *ring, bool in_sw)
{
	struct fm10k_intfc *interface = ring->q_vector->interface;
	struct fm10k_hw *hw = &interface->hw;
	u32 head, tail;

	if (likely(in_sw)) {
		head = ring->next_to_clean;
		tail = ring->next_to_use;
	} else {
		head = fm10k_read_reg(hw, FM10K_TDH(ring->reg_idx));
		tail = fm10k_read_reg(hw, FM10K_TDT(ring->reg_idx));
	}

	return ((head <= tail) ? tail : tail + ring->count) - head;
}