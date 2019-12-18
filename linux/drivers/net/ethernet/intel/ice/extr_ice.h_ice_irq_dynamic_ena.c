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
typedef  int u32 ;
struct ice_vsi {int /*<<< orphan*/  state; } ;
struct ice_q_vector {int reg_idx; } ;
struct ice_pf {int oicr_idx; } ;
struct ice_hw {scalar_t__ back; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLINT_DYN_CTL (int) ; 
 int GLINT_DYN_CTL_CLEARPBA_M ; 
 int GLINT_DYN_CTL_INTENA_M ; 
 int GLINT_DYN_CTL_ITR_INDX_S ; 
 int ICE_ITR_NONE ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
ice_irq_dynamic_ena(struct ice_hw *hw, struct ice_vsi *vsi,
		    struct ice_q_vector *q_vector)
{
	u32 vector = (vsi && q_vector) ? q_vector->reg_idx :
				((struct ice_pf *)hw->back)->oicr_idx;
	int itr = ICE_ITR_NONE;
	u32 val;

	/* clear the PBA here, as this function is meant to clean out all
	 * previous interrupts and enable the interrupt
	 */
	val = GLINT_DYN_CTL_INTENA_M | GLINT_DYN_CTL_CLEARPBA_M |
	      (itr << GLINT_DYN_CTL_ITR_INDX_S);
	if (vsi)
		if (test_bit(__ICE_DOWN, vsi->state))
			return;
	wr32(hw, GLINT_DYN_CTL(vector), val);
}