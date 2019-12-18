#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int vf_base_id; } ;
struct i40e_hw {TYPE_1__ func_caps; } ;
struct i40e_pf {int num_alloc_vfs; int /*<<< orphan*/  state; TYPE_2__* pdev; TYPE_4__* vf; int /*<<< orphan*/ * vsi; struct i40e_hw hw; } ;
struct TYPE_9__ {size_t lan_vsi_idx; int /*<<< orphan*/  vf_states; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  I40E_GLGEN_VFLRSTAT (int) ; 
 int /*<<< orphan*/  I40E_VF_STATE_INIT ; 
 int /*<<< orphan*/  __I40E_VF_DISABLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i40e_disable_vf_mappings (TYPE_4__*) ; 
 int /*<<< orphan*/  i40e_free_vf_res (TYPE_4__*) ; 
 int /*<<< orphan*/  i40e_notify_client_of_vf_enable (struct i40e_pf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_vsi_stop_rings_no_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_vsi_wait_queues_disabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 int /*<<< orphan*/  pci_disable_sriov (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_vfs_assigned (TYPE_2__*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i40e_free_vfs(struct i40e_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	u32 reg_idx, bit_idx;
	int i, tmp, vf_id;

	if (!pf->vf)
		return;
	while (test_and_set_bit(__I40E_VF_DISABLE, pf->state))
		usleep_range(1000, 2000);

	i40e_notify_client_of_vf_enable(pf, 0);

	/* Amortize wait time by stopping all VFs at the same time */
	for (i = 0; i < pf->num_alloc_vfs; i++) {
		if (test_bit(I40E_VF_STATE_INIT, &pf->vf[i].vf_states))
			continue;

		i40e_vsi_stop_rings_no_wait(pf->vsi[pf->vf[i].lan_vsi_idx]);
	}

	for (i = 0; i < pf->num_alloc_vfs; i++) {
		if (test_bit(I40E_VF_STATE_INIT, &pf->vf[i].vf_states))
			continue;

		i40e_vsi_wait_queues_disabled(pf->vsi[pf->vf[i].lan_vsi_idx]);
	}

	/* Disable IOV before freeing resources. This lets any VF drivers
	 * running in the host get themselves cleaned up before we yank
	 * the carpet out from underneath their feet.
	 */
	if (!pci_vfs_assigned(pf->pdev))
		pci_disable_sriov(pf->pdev);
	else
		dev_warn(&pf->pdev->dev, "VFs are assigned - not disabling SR-IOV\n");

	/* free up VF resources */
	tmp = pf->num_alloc_vfs;
	pf->num_alloc_vfs = 0;
	for (i = 0; i < tmp; i++) {
		if (test_bit(I40E_VF_STATE_INIT, &pf->vf[i].vf_states))
			i40e_free_vf_res(&pf->vf[i]);
		/* disable qp mappings */
		i40e_disable_vf_mappings(&pf->vf[i]);
	}

	kfree(pf->vf);
	pf->vf = NULL;

	/* This check is for when the driver is unloaded while VFs are
	 * assigned. Setting the number of VFs to 0 through sysfs is caught
	 * before this function ever gets called.
	 */
	if (!pci_vfs_assigned(pf->pdev)) {
		/* Acknowledge VFLR for all VFS. Without this, VFs will fail to
		 * work correctly when SR-IOV gets re-enabled.
		 */
		for (vf_id = 0; vf_id < tmp; vf_id++) {
			reg_idx = (hw->func_caps.vf_base_id + vf_id) / 32;
			bit_idx = (hw->func_caps.vf_base_id + vf_id) % 32;
			wr32(hw, I40E_GLGEN_VFLRSTAT(reg_idx), BIT(bit_idx));
		}
	}
	clear_bit(__I40E_VF_DISABLE, pf->state);
}