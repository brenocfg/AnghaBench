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
struct i40e_vsi {scalar_t__ base_vector; struct i40e_pf* back; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 int I40E_ITR_NONE ; 
 int /*<<< orphan*/  I40E_PFINT_DYN_CTLN (scalar_t__) ; 
 int I40E_PFINT_DYN_CTLN_CLEARPBA_MASK ; 
 int I40E_PFINT_DYN_CTLN_INTENA_MASK ; 
 int I40E_PFINT_DYN_CTLN_ITR_INDX_SHIFT ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void i40e_irq_dynamic_enable(struct i40e_vsi *vsi, int vector)
{
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;
	u32 val;

	val = I40E_PFINT_DYN_CTLN_INTENA_MASK |
	      I40E_PFINT_DYN_CTLN_CLEARPBA_MASK |
	      (I40E_ITR_NONE << I40E_PFINT_DYN_CTLN_ITR_INDX_SHIFT);
	wr32(hw, I40E_PFINT_DYN_CTLN(vector + vsi->base_vector - 1), val);
	/* skip the flush */
}