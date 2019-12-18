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
struct i40e_vsi {int /*<<< orphan*/  state; } ;
struct i40e_ring {int flags; scalar_t__ count; int arm_wb; } ;

/* Variables and functions */
 scalar_t__ I40E_DESC_UNUSED (struct i40e_ring*) ; 
 int I40E_TXR_FLAGS_WB_ON_ITR ; 
 unsigned int WB_STRIDE ; 
 int /*<<< orphan*/  __I40E_VSI_DOWN ; 
 unsigned int i40e_get_tx_pending (struct i40e_ring*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void i40e_arm_wb(struct i40e_ring *tx_ring,
			       struct i40e_vsi *vsi,
			       int budget)
{
	if (tx_ring->flags & I40E_TXR_FLAGS_WB_ON_ITR) {
		/* check to see if there are < 4 descriptors
		 * waiting to be written back, then kick the hardware to force
		 * them to be written back in case we stay in NAPI.
		 * In this mode on X722 we do not enable Interrupt.
		 */
		unsigned int j = i40e_get_tx_pending(tx_ring, false);

		if (budget &&
		    ((j / WB_STRIDE) == 0) && j > 0 &&
		    !test_bit(__I40E_VSI_DOWN, vsi->state) &&
		    (I40E_DESC_UNUSED(tx_ring) != tx_ring->count))
			tx_ring->arm_wb = true;
	}
}