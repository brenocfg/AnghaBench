#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct i40e_vsi {int /*<<< orphan*/  state; TYPE_2__* back; } ;
struct TYPE_3__ {scalar_t__ target_itr; scalar_t__ current_itr; } ;
struct i40e_q_vector {int /*<<< orphan*/  reg_idx; void* itr_countdown; TYPE_1__ rx; TYPE_1__ tx; } ;
struct i40e_hw {int dummy; } ;
struct TYPE_4__ {int flags; struct i40e_hw hw; } ;

/* Variables and functions */
 int I40E_FLAG_MSIX_ENABLED ; 
 int /*<<< orphan*/  I40E_ITR_NONE ; 
 int /*<<< orphan*/  I40E_RX_ITR ; 
 int /*<<< orphan*/  I40E_TX_ITR ; 
 int /*<<< orphan*/  INTREG (int /*<<< orphan*/ ) ; 
 void* ITR_COUNTDOWN_START ; 
 int /*<<< orphan*/  __I40E_VSI_DOWN ; 
 int /*<<< orphan*/  i40e_buildreg_itr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  i40e_irq_dynamic_enable_icr0 (TYPE_2__*) ; 
 int /*<<< orphan*/  i40e_update_itr (struct i40e_q_vector*,TYPE_1__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void i40e_update_enable_itr(struct i40e_vsi *vsi,
					  struct i40e_q_vector *q_vector)
{
	struct i40e_hw *hw = &vsi->back->hw;
	u32 intval;

	/* If we don't have MSIX, then we only need to re-enable icr0 */
	if (!(vsi->back->flags & I40E_FLAG_MSIX_ENABLED)) {
		i40e_irq_dynamic_enable_icr0(vsi->back);
		return;
	}

	/* These will do nothing if dynamic updates are not enabled */
	i40e_update_itr(q_vector, &q_vector->tx);
	i40e_update_itr(q_vector, &q_vector->rx);

	/* This block of logic allows us to get away with only updating
	 * one ITR value with each interrupt. The idea is to perform a
	 * pseudo-lazy update with the following criteria.
	 *
	 * 1. Rx is given higher priority than Tx if both are in same state
	 * 2. If we must reduce an ITR that is given highest priority.
	 * 3. We then give priority to increasing ITR based on amount.
	 */
	if (q_vector->rx.target_itr < q_vector->rx.current_itr) {
		/* Rx ITR needs to be reduced, this is highest priority */
		intval = i40e_buildreg_itr(I40E_RX_ITR,
					   q_vector->rx.target_itr);
		q_vector->rx.current_itr = q_vector->rx.target_itr;
		q_vector->itr_countdown = ITR_COUNTDOWN_START;
	} else if ((q_vector->tx.target_itr < q_vector->tx.current_itr) ||
		   ((q_vector->rx.target_itr - q_vector->rx.current_itr) <
		    (q_vector->tx.target_itr - q_vector->tx.current_itr))) {
		/* Tx ITR needs to be reduced, this is second priority
		 * Tx ITR needs to be increased more than Rx, fourth priority
		 */
		intval = i40e_buildreg_itr(I40E_TX_ITR,
					   q_vector->tx.target_itr);
		q_vector->tx.current_itr = q_vector->tx.target_itr;
		q_vector->itr_countdown = ITR_COUNTDOWN_START;
	} else if (q_vector->rx.current_itr != q_vector->rx.target_itr) {
		/* Rx ITR needs to be increased, third priority */
		intval = i40e_buildreg_itr(I40E_RX_ITR,
					   q_vector->rx.target_itr);
		q_vector->rx.current_itr = q_vector->rx.target_itr;
		q_vector->itr_countdown = ITR_COUNTDOWN_START;
	} else {
		/* No ITR update, lowest priority */
		intval = i40e_buildreg_itr(I40E_ITR_NONE, 0);
		if (q_vector->itr_countdown)
			q_vector->itr_countdown--;
	}

	if (!test_bit(__I40E_VSI_DOWN, vsi->state))
		wr32(hw, INTREG(q_vector->reg_idx), intval);
}