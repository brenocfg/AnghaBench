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
typedef  int /*<<< orphan*/  u32 ;
struct ice_vsi {TYPE_1__* back; int /*<<< orphan*/  state; } ;
struct ice_ring_container {int target_itr; int itr_setting; int current_itr; int /*<<< orphan*/  itr_idx; } ;
struct ice_q_vector {scalar_t__ itr_countdown; int /*<<< orphan*/  reg_idx; struct ice_vsi* vsi; struct ice_ring_container rx; struct ice_ring_container tx; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLINT_DYN_CTL (int /*<<< orphan*/ ) ; 
 scalar_t__ ICE_IN_WB_ON_ITR_MODE ; 
 int ICE_ITR_DYNAMIC ; 
 int /*<<< orphan*/  ICE_ITR_NONE ; 
 int ICE_WB_ON_ITR_USECS ; 
 void* ITR_COUNTDOWN_START ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  ice_buildreg_itr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ice_update_itr (struct ice_q_vector*,struct ice_ring_container*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_update_ena_itr(struct ice_q_vector *q_vector)
{
	struct ice_ring_container *tx = &q_vector->tx;
	struct ice_ring_container *rx = &q_vector->rx;
	struct ice_vsi *vsi = q_vector->vsi;
	u32 itr_val;

	/* when exiting WB_ON_ITR lets set a low ITR value and trigger
	 * interrupts to expire right away in case we have more work ready to go
	 * already
	 */
	if (q_vector->itr_countdown == ICE_IN_WB_ON_ITR_MODE) {
		itr_val = ice_buildreg_itr(rx->itr_idx, ICE_WB_ON_ITR_USECS);
		wr32(&vsi->back->hw, GLINT_DYN_CTL(q_vector->reg_idx), itr_val);
		/* set target back to last user set value */
		rx->target_itr = rx->itr_setting;
		/* set current to what we just wrote and dynamic if needed */
		rx->current_itr = ICE_WB_ON_ITR_USECS |
			(rx->itr_setting & ICE_ITR_DYNAMIC);
		/* allow normal interrupt flow to start */
		q_vector->itr_countdown = 0;
		return;
	}

	/* This will do nothing if dynamic updates are not enabled */
	ice_update_itr(q_vector, tx);
	ice_update_itr(q_vector, rx);

	/* This block of logic allows us to get away with only updating
	 * one ITR value with each interrupt. The idea is to perform a
	 * pseudo-lazy update with the following criteria.
	 *
	 * 1. Rx is given higher priority than Tx if both are in same state
	 * 2. If we must reduce an ITR that is given highest priority.
	 * 3. We then give priority to increasing ITR based on amount.
	 */
	if (rx->target_itr < rx->current_itr) {
		/* Rx ITR needs to be reduced, this is highest priority */
		itr_val = ice_buildreg_itr(rx->itr_idx, rx->target_itr);
		rx->current_itr = rx->target_itr;
		q_vector->itr_countdown = ITR_COUNTDOWN_START;
	} else if ((tx->target_itr < tx->current_itr) ||
		   ((rx->target_itr - rx->current_itr) <
		    (tx->target_itr - tx->current_itr))) {
		/* Tx ITR needs to be reduced, this is second priority
		 * Tx ITR needs to be increased more than Rx, fourth priority
		 */
		itr_val = ice_buildreg_itr(tx->itr_idx, tx->target_itr);
		tx->current_itr = tx->target_itr;
		q_vector->itr_countdown = ITR_COUNTDOWN_START;
	} else if (rx->current_itr != rx->target_itr) {
		/* Rx ITR needs to be increased, third priority */
		itr_val = ice_buildreg_itr(rx->itr_idx, rx->target_itr);
		rx->current_itr = rx->target_itr;
		q_vector->itr_countdown = ITR_COUNTDOWN_START;
	} else {
		/* Still have to re-enable the interrupts */
		itr_val = ice_buildreg_itr(ICE_ITR_NONE, 0);
		if (q_vector->itr_countdown)
			q_vector->itr_countdown--;
	}

	if (!test_bit(__ICE_DOWN, q_vector->vsi->state))
		wr32(&q_vector->vsi->back->hw,
		     GLINT_DYN_CTL(q_vector->reg_idx),
		     itr_val);
}