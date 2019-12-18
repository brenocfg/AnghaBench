#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* ring; } ;
struct TYPE_7__ {TYPE_1__* ring; } ;
struct igc_q_vector {int set_itr; int /*<<< orphan*/  eims_value; TYPE_4__ tx; TYPE_2__ rx; struct igc_adapter* adapter; } ;
struct TYPE_10__ {int type; } ;
struct igc_hw {TYPE_5__ mac; } ;
struct igc_adapter {int /*<<< orphan*/  eims_enable_mask; struct igc_hw hw; } ;
struct TYPE_8__ {int reg_idx; } ;
struct TYPE_6__ {int reg_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int IGC_N0_QUEUE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
#define  igc_i225 128 
 int /*<<< orphan*/  igc_write_ivar (struct igc_hw*,int,int,int) ; 

__attribute__((used)) static void igc_assign_vector(struct igc_q_vector *q_vector, int msix_vector)
{
	struct igc_adapter *adapter = q_vector->adapter;
	struct igc_hw *hw = &adapter->hw;
	int rx_queue = IGC_N0_QUEUE;
	int tx_queue = IGC_N0_QUEUE;

	if (q_vector->rx.ring)
		rx_queue = q_vector->rx.ring->reg_idx;
	if (q_vector->tx.ring)
		tx_queue = q_vector->tx.ring->reg_idx;

	switch (hw->mac.type) {
	case igc_i225:
		if (rx_queue > IGC_N0_QUEUE)
			igc_write_ivar(hw, msix_vector,
				       rx_queue >> 1,
				       (rx_queue & 0x1) << 4);
		if (tx_queue > IGC_N0_QUEUE)
			igc_write_ivar(hw, msix_vector,
				       tx_queue >> 1,
				       ((tx_queue & 0x1) << 4) + 8);
		q_vector->eims_value = BIT(msix_vector);
		break;
	default:
		WARN_ONCE(hw->mac.type != igc_i225, "Wrong MAC type\n");
		break;
	}

	/* add q_vector eims value to global eims_enable_mask */
	adapter->eims_enable_mask |= q_vector->eims_value;

	/* configure q_vector to set itr on first interrupt */
	q_vector->set_itr = 1;
}