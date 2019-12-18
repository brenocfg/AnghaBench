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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ice_vsi {int /*<<< orphan*/  idx; int /*<<< orphan*/  port_info; } ;
struct ice_vf {size_t lan_vsi_idx; scalar_t__ num_vlan; scalar_t__ port_vlan_id; int /*<<< orphan*/  vf_states; int /*<<< orphan*/  vf_id; struct ice_pf* pf; } ;
struct ice_hw {int dummy; } ;
struct ice_pf {TYPE_1__* pdev; struct ice_vsi** vsi; struct ice_hw hw; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_UCAST_PROMISC_BITS ; 
 int /*<<< orphan*/  ICE_UCAST_VLAN_PROMISC_BITS ; 
 int /*<<< orphan*/  ICE_VF_RESET ; 
 int /*<<< orphan*/  ICE_VF_STATE_DIS ; 
 int /*<<< orphan*/  ICE_VF_STATE_MC_PROMISC ; 
 int /*<<< orphan*/  ICE_VF_STATE_QS_ENA ; 
 int /*<<< orphan*/  ICE_VF_STATE_UC_PROMISC ; 
 int /*<<< orphan*/  VPGEN_VFRSTAT (int /*<<< orphan*/ ) ; 
 int VPGEN_VFRSTAT_VFRD_M ; 
 int /*<<< orphan*/  __ICE_VF_DIS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_cleanup_and_realloc_vf (struct ice_vf*) ; 
 int /*<<< orphan*/  ice_dis_vf_qs (struct ice_vf*) ; 
 int /*<<< orphan*/  ice_dis_vsi_txq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_flush (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_free_vf_res (struct ice_vf*) ; 
 int /*<<< orphan*/  ice_trigger_vf_reset (struct ice_vf*,int,int) ; 
 scalar_t__ ice_vf_set_vsi_promisc (struct ice_vf*,struct ice_vsi*,int /*<<< orphan*/ ,int) ; 
 int rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static bool ice_reset_vf(struct ice_vf *vf, bool is_vflr)
{
	struct ice_pf *pf = vf->pf;
	struct ice_vsi *vsi;
	struct ice_hw *hw;
	bool rsd = false;
	u8 promisc_m;
	u32 reg;
	int i;

	/* If the PF has been disabled, there is no need resetting VF until
	 * PF is active again.
	 */
	if (test_bit(__ICE_VF_DIS, pf->state))
		return false;

	/* If the VF has been disabled, this means something else is
	 * resetting the VF, so we shouldn't continue. Otherwise, set
	 * disable VF state bit for actual reset, and continue.
	 */
	if (test_and_set_bit(ICE_VF_STATE_DIS, vf->vf_states))
		return false;

	ice_trigger_vf_reset(vf, is_vflr, false);

	vsi = pf->vsi[vf->lan_vsi_idx];

	if (test_bit(ICE_VF_STATE_QS_ENA, vf->vf_states))
		ice_dis_vf_qs(vf);

	/* Call Disable LAN Tx queue AQ whether or not queues are
	 * enabled. This is needed for successful completion of VFR.
	 */
	ice_dis_vsi_txq(vsi->port_info, vsi->idx, 0, 0, NULL, NULL,
			NULL, ICE_VF_RESET, vf->vf_id, NULL);

	hw = &pf->hw;
	/* poll VPGEN_VFRSTAT reg to make sure
	 * that reset is complete
	 */
	for (i = 0; i < 10; i++) {
		/* VF reset requires driver to first reset the VF and then
		 * poll the status register to make sure that the reset
		 * completed successfully.
		 */
		reg = rd32(hw, VPGEN_VFRSTAT(vf->vf_id));
		if (reg & VPGEN_VFRSTAT_VFRD_M) {
			rsd = true;
			break;
		}

		/* only sleep if the reset is not done */
		usleep_range(10, 20);
	}

	/* Display a warning if VF didn't manage to reset in time, but need to
	 * continue on with the operation.
	 */
	if (!rsd)
		dev_warn(&pf->pdev->dev, "VF reset check timeout on VF %d\n",
			 vf->vf_id);

	/* disable promiscuous modes in case they were enabled
	 * ignore any error if disabling process failed
	 */
	if (test_bit(ICE_VF_STATE_UC_PROMISC, vf->vf_states) ||
	    test_bit(ICE_VF_STATE_MC_PROMISC, vf->vf_states)) {
		if (vf->port_vlan_id ||  vf->num_vlan)
			promisc_m = ICE_UCAST_VLAN_PROMISC_BITS;
		else
			promisc_m = ICE_UCAST_PROMISC_BITS;

		vsi = pf->vsi[vf->lan_vsi_idx];
		if (ice_vf_set_vsi_promisc(vf, vsi, promisc_m, true))
			dev_err(&pf->pdev->dev, "disabling promiscuous mode failed\n");
	}

	/* free VF resources to begin resetting the VSI state */
	ice_free_vf_res(vf);

	ice_cleanup_and_realloc_vf(vf);

	ice_flush(hw);

	return true;
}