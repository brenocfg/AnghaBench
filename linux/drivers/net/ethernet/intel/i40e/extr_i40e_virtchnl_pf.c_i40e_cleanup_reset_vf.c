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
struct i40e_vf {int vf_id; scalar_t__ num_vlan; int /*<<< orphan*/  vf_states; int /*<<< orphan*/  lan_vsi_id; struct i40e_pf* pf; } ;
struct TYPE_2__ {int vf_base_id; } ;
struct i40e_hw {TYPE_1__ func_caps; } ;
struct i40e_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VFGEN_RSTAT1 (int) ; 
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  I40E_VF_STATE_DISABLED ; 
 int /*<<< orphan*/  I40E_VF_STATE_PRE_ENABLE ; 
 int /*<<< orphan*/  I40E_VPGEN_VFRTRIG (int) ; 
 int /*<<< orphan*/  I40E_VPGEN_VFRTRIG_VFSWR_MASK ; 
 int /*<<< orphan*/  VIRTCHNL_VFR_VFACTIVE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_alloc_vf_res (struct i40e_vf*) ; 
 int /*<<< orphan*/  i40e_config_vf_promiscuous_mode (struct i40e_vf*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  i40e_enable_vf_mappings (struct i40e_vf*) ; 
 int /*<<< orphan*/  i40e_free_vf_res (struct i40e_vf*) ; 
 int /*<<< orphan*/  i40e_notify_client_of_vf_reset (struct i40e_pf*,int) ; 
 int /*<<< orphan*/  rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_cleanup_reset_vf(struct i40e_vf *vf)
{
	struct i40e_pf *pf = vf->pf;
	struct i40e_hw *hw = &pf->hw;
	u32 reg;

	/* disable promisc modes in case they were enabled */
	i40e_config_vf_promiscuous_mode(vf, vf->lan_vsi_id, false, false);

	/* free VF resources to begin resetting the VSI state */
	i40e_free_vf_res(vf);

	/* Enable hardware by clearing the reset bit in the VPGEN_VFRTRIG reg.
	 * By doing this we allow HW to access VF memory at any point. If we
	 * did it any sooner, HW could access memory while it was being freed
	 * in i40e_free_vf_res(), causing an IOMMU fault.
	 *
	 * On the other hand, this needs to be done ASAP, because the VF driver
	 * is waiting for this to happen and may report a timeout. It's
	 * harmless, but it gets logged into Guest OS kernel log, so best avoid
	 * it.
	 */
	reg = rd32(hw, I40E_VPGEN_VFRTRIG(vf->vf_id));
	reg &= ~I40E_VPGEN_VFRTRIG_VFSWR_MASK;
	wr32(hw, I40E_VPGEN_VFRTRIG(vf->vf_id), reg);

	/* reallocate VF resources to finish resetting the VSI state */
	if (!i40e_alloc_vf_res(vf)) {
		int abs_vf_id = vf->vf_id + hw->func_caps.vf_base_id;
		i40e_enable_vf_mappings(vf);
		set_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states);
		clear_bit(I40E_VF_STATE_DISABLED, &vf->vf_states);
		/* Do not notify the client during VF init */
		if (!test_and_clear_bit(I40E_VF_STATE_PRE_ENABLE,
					&vf->vf_states))
			i40e_notify_client_of_vf_reset(pf, abs_vf_id);
		vf->num_vlan = 0;
	}

	/* Tell the VF driver the reset is done. This needs to be done only
	 * after VF has been fully initialized, because the VF driver may
	 * request resources immediately after setting this flag.
	 */
	wr32(hw, I40E_VFGEN_RSTAT1(vf->vf_id), VIRTCHNL_VFR_VFACTIVE);
}