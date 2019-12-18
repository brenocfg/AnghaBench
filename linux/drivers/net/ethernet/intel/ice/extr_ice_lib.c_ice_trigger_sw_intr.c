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
struct ice_q_vector {int /*<<< orphan*/  reg_idx; } ;
struct ice_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLINT_DYN_CTL (int /*<<< orphan*/ ) ; 
 int GLINT_DYN_CTL_INTENA_M ; 
 int GLINT_DYN_CTL_ITR_INDX_S ; 
 int GLINT_DYN_CTL_SWINT_TRIG_M ; 
 int ICE_ITR_NONE ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int) ; 

void ice_trigger_sw_intr(struct ice_hw *hw, struct ice_q_vector *q_vector)
{
	wr32(hw, GLINT_DYN_CTL(q_vector->reg_idx),
	     (ICE_ITR_NONE << GLINT_DYN_CTL_ITR_INDX_S) |
	     GLINT_DYN_CTL_SWINT_TRIG_M |
	     GLINT_DYN_CTL_INTENA_M);
}