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
typedef  int u32 ;
struct i40e_vf {int dummy; } ;
struct TYPE_2__ {int vf_base_id; } ;
struct i40e_hw {TYPE_1__ func_caps; } ;
struct i40e_pf {int num_alloc_vfs; struct i40e_vf* vf; int /*<<< orphan*/  state; struct i40e_hw hw; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  I40E_GLGEN_VFLRSTAT (int) ; 
 int /*<<< orphan*/  I40E_PFINT_ICR0_ENA ; 
 int I40E_PFINT_ICR0_ENA_VFLR_MASK ; 
 int /*<<< orphan*/  __I40E_VFLR_EVENT_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_reset_vf (struct i40e_vf*,int) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

int i40e_vc_process_vflr_event(struct i40e_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	u32 reg, reg_idx, bit_idx;
	struct i40e_vf *vf;
	int vf_id;

	if (!test_bit(__I40E_VFLR_EVENT_PENDING, pf->state))
		return 0;

	/* Re-enable the VFLR interrupt cause here, before looking for which
	 * VF got reset. Otherwise, if another VF gets a reset while the
	 * first one is being processed, that interrupt will be lost, and
	 * that VF will be stuck in reset forever.
	 */
	reg = rd32(hw, I40E_PFINT_ICR0_ENA);
	reg |= I40E_PFINT_ICR0_ENA_VFLR_MASK;
	wr32(hw, I40E_PFINT_ICR0_ENA, reg);
	i40e_flush(hw);

	clear_bit(__I40E_VFLR_EVENT_PENDING, pf->state);
	for (vf_id = 0; vf_id < pf->num_alloc_vfs; vf_id++) {
		reg_idx = (hw->func_caps.vf_base_id + vf_id) / 32;
		bit_idx = (hw->func_caps.vf_base_id + vf_id) % 32;
		/* read GLGEN_VFLRSTAT register to find out the flr VFs */
		vf = &pf->vf[vf_id];
		reg = rd32(hw, I40E_GLGEN_VFLRSTAT(reg_idx));
		if (reg & BIT(bit_idx))
			/* i40e_reset_vf will clear the bit in GLGEN_VFLRSTAT */
			i40e_reset_vf(vf, true);
	}

	return 0;
}