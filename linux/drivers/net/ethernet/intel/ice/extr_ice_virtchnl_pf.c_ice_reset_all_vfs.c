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
struct ice_vsi {int /*<<< orphan*/  idx; int /*<<< orphan*/  port_info; } ;
struct ice_vf {size_t lan_vsi_idx; scalar_t__ num_vf_qs; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  vf_states; } ;
struct ice_hw {int dummy; } ;
struct ice_pf {int num_alloc_vfs; TYPE_1__* pdev; struct ice_vf* vf; struct ice_vsi** vsi; int /*<<< orphan*/  state; struct ice_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_VF_RESET ; 
 int /*<<< orphan*/  ICE_VF_STATE_QS_ENA ; 
 int /*<<< orphan*/  VPGEN_VFRSTAT (int /*<<< orphan*/ ) ; 
 int VPGEN_VFRSTAT_VFRD_M ; 
 int /*<<< orphan*/  __ICE_VF_DIS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ice_config_res_vfs (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_dis_vf_qs (struct ice_vf*) ; 
 int /*<<< orphan*/  ice_dis_vsi_txq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_free_vf_res (struct ice_vf*) ; 
 scalar_t__ ice_sriov_free_msix_res (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_trigger_vf_reset (struct ice_vf*,int,int) ; 
 int rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

bool ice_reset_all_vfs(struct ice_pf *pf, bool is_vflr)
{
	struct ice_hw *hw = &pf->hw;
	struct ice_vf *vf;
	int v, i;

	/* If we don't have any VFs, then there is nothing to reset */
	if (!pf->num_alloc_vfs)
		return false;

	/* If VFs have been disabled, there is no need to reset */
	if (test_and_set_bit(__ICE_VF_DIS, pf->state))
		return false;

	/* Begin reset on all VFs at once */
	for (v = 0; v < pf->num_alloc_vfs; v++)
		ice_trigger_vf_reset(&pf->vf[v], is_vflr, true);

	for (v = 0; v < pf->num_alloc_vfs; v++) {
		struct ice_vsi *vsi;

		vf = &pf->vf[v];
		vsi = pf->vsi[vf->lan_vsi_idx];
		if (test_bit(ICE_VF_STATE_QS_ENA, vf->vf_states))
			ice_dis_vf_qs(vf);
		ice_dis_vsi_txq(vsi->port_info, vsi->idx, 0, 0, NULL, NULL,
				NULL, ICE_VF_RESET, vf->vf_id, NULL);
	}

	/* HW requires some time to make sure it can flush the FIFO for a VF
	 * when it resets it. Poll the VPGEN_VFRSTAT register for each VF in
	 * sequence to make sure that it has completed. We'll keep track of
	 * the VFs using a simple iterator that increments once that VF has
	 * finished resetting.
	 */
	for (i = 0, v = 0; i < 10 && v < pf->num_alloc_vfs; i++) {

		/* Check each VF in sequence */
		while (v < pf->num_alloc_vfs) {
			u32 reg;

			vf = &pf->vf[v];
			reg = rd32(hw, VPGEN_VFRSTAT(vf->vf_id));
			if (!(reg & VPGEN_VFRSTAT_VFRD_M)) {
				/* only delay if the check failed */
				usleep_range(10, 20);
				break;
			}

			/* If the current VF has finished resetting, move on
			 * to the next VF in sequence.
			 */
			v++;
		}
	}

	/* Display a warning if at least one VF didn't manage to reset in
	 * time, but continue on with the operation.
	 */
	if (v < pf->num_alloc_vfs)
		dev_warn(&pf->pdev->dev, "VF reset check timeout\n");

	/* free VF resources to begin resetting the VSI state */
	for (v = 0; v < pf->num_alloc_vfs; v++) {
		vf = &pf->vf[v];

		ice_free_vf_res(vf);

		/* Free VF queues as well, and reallocate later.
		 * If a given VF has different number of queues
		 * configured, the request for update will come
		 * via mailbox communication.
		 */
		vf->num_vf_qs = 0;
	}

	if (ice_sriov_free_msix_res(pf))
		dev_err(&pf->pdev->dev,
			"Failed to free MSIX resources used by SR-IOV\n");

	if (!ice_config_res_vfs(pf))
		return false;

	return true;
}