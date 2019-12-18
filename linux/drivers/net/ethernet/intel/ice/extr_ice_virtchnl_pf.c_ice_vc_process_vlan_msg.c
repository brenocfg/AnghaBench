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
typedef  int u8 ;
typedef  char* u16 ;
struct virtchnl_vlan_filter_list {int num_elements; scalar_t__* vlan_id; int /*<<< orphan*/  vsi_id; } ;
struct TYPE_3__ {scalar_t__ pvid; } ;
struct ice_vsi {int vsi_num; int /*<<< orphan*/  idx; TYPE_1__ info; } ;
struct ice_vf {scalar_t__ num_vlan; size_t lan_vsi_idx; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  vf_states; struct ice_pf* pf; } ;
struct ice_hw {int dummy; } ;
struct ice_pf {TYPE_2__* pdev; struct ice_vsi** vsi; struct ice_hw hw; } ;
typedef  enum virtchnl_status_code { ____Placeholder_virtchnl_status_code } virtchnl_status_code ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ICE_MAX_VLANID ; 
 scalar_t__ ICE_MAX_VLAN_PER_VF ; 
 int ICE_PROMISC_VLAN_RX ; 
 int ICE_PROMISC_VLAN_TX ; 
 int /*<<< orphan*/  ICE_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  ICE_VF_STATE_MC_PROMISC ; 
 int /*<<< orphan*/  ICE_VF_STATE_UC_PROMISC ; 
 int /*<<< orphan*/  VIRTCHNL_OP_ADD_VLAN ; 
 int /*<<< orphan*/  VIRTCHNL_OP_DEL_VLAN ; 
 int VIRTCHNL_STATUS_ERR_PARAM ; 
 int VIRTCHNL_STATUS_SUCCESS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int ice_cfg_vlan_pruning (struct ice_vsi*,int,int) ; 
 int /*<<< orphan*/  ice_clear_vsi_promisc (struct ice_hw*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  ice_is_vf_trusted (struct ice_vf*) ; 
 int ice_set_vsi_promisc (struct ice_hw*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  ice_vc_isvalid_vsi_id (struct ice_vf*,int /*<<< orphan*/ ) ; 
 int ice_vc_send_msg_to_vf (struct ice_vf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ice_vsi_add_vlan (struct ice_vsi*,char*) ; 
 scalar_t__ ice_vsi_kill_vlan (struct ice_vsi*,char*) ; 
 scalar_t__ ice_vsi_manage_vlan_stripping (struct ice_vsi*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_vc_process_vlan_msg(struct ice_vf *vf, u8 *msg, bool add_v)
{
	enum virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	struct virtchnl_vlan_filter_list *vfl =
	    (struct virtchnl_vlan_filter_list *)msg;
	struct ice_pf *pf = vf->pf;
	bool vlan_promisc = false;
	struct ice_vsi *vsi;
	struct ice_hw *hw;
	int status = 0;
	u8 promisc_m;
	int i;

	if (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) {
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		goto error_param;
	}

	if (!ice_vc_isvalid_vsi_id(vf, vfl->vsi_id)) {
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		goto error_param;
	}

	if (add_v && !ice_is_vf_trusted(vf) &&
	    vf->num_vlan >= ICE_MAX_VLAN_PER_VF) {
		dev_info(&pf->pdev->dev,
			 "VF-%d is not trusted, switch the VF to trusted mode, in order to add more VLAN addresses\n",
			 vf->vf_id);
		/* There is no need to let VF know about being not trusted,
		 * so we can just return success message here
		 */
		goto error_param;
	}

	for (i = 0; i < vfl->num_elements; i++) {
		if (vfl->vlan_id[i] > ICE_MAX_VLANID) {
			v_ret = VIRTCHNL_STATUS_ERR_PARAM;
			dev_err(&pf->pdev->dev,
				"invalid VF VLAN id %d\n", vfl->vlan_id[i]);
			goto error_param;
		}
	}

	hw = &pf->hw;
	vsi = pf->vsi[vf->lan_vsi_idx];
	if (!vsi) {
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		goto error_param;
	}

	if (vsi->info.pvid) {
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		goto error_param;
	}

	if (ice_vsi_manage_vlan_stripping(vsi, add_v)) {
		dev_err(&pf->pdev->dev,
			"%sable VLAN stripping failed for VSI %i\n",
			 add_v ? "en" : "dis", vsi->vsi_num);
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		goto error_param;
	}

	if (test_bit(ICE_VF_STATE_UC_PROMISC, vf->vf_states) ||
	    test_bit(ICE_VF_STATE_MC_PROMISC, vf->vf_states))
		vlan_promisc = true;

	if (add_v) {
		for (i = 0; i < vfl->num_elements; i++) {
			u16 vid = vfl->vlan_id[i];

			if (!ice_is_vf_trusted(vf) &&
			    vf->num_vlan >= ICE_MAX_VLAN_PER_VF) {
				dev_info(&pf->pdev->dev,
					 "VF-%d is not trusted, switch the VF to trusted mode, in order to add more VLAN addresses\n",
					 vf->vf_id);
				/* There is no need to let VF know about being
				 * not trusted, so we can just return success
				 * message here as well.
				 */
				goto error_param;
			}

			if (ice_vsi_add_vlan(vsi, vid)) {
				v_ret = VIRTCHNL_STATUS_ERR_PARAM;
				goto error_param;
			}

			vf->num_vlan++;
			/* Enable VLAN pruning when VLAN is added */
			if (!vlan_promisc) {
				status = ice_cfg_vlan_pruning(vsi, true, false);
				if (status) {
					v_ret = VIRTCHNL_STATUS_ERR_PARAM;
					dev_err(&pf->pdev->dev,
						"Enable VLAN pruning on VLAN ID: %d failed error-%d\n",
						vid, status);
					goto error_param;
				}
			} else {
				/* Enable Ucast/Mcast VLAN promiscuous mode */
				promisc_m = ICE_PROMISC_VLAN_TX |
					    ICE_PROMISC_VLAN_RX;

				status = ice_set_vsi_promisc(hw, vsi->idx,
							     promisc_m, vid);
				if (status) {
					v_ret = VIRTCHNL_STATUS_ERR_PARAM;
					dev_err(&pf->pdev->dev,
						"Enable Unicast/multicast promiscuous mode on VLAN ID:%d failed error-%d\n",
						vid, status);
				}
			}
		}
	} else {
		/* In case of non_trusted VF, number of VLAN elements passed
		 * to PF for removal might be greater than number of VLANs
		 * filter programmed for that VF - So, use actual number of
		 * VLANS added earlier with add VLAN opcode. In order to avoid
		 * removing VLAN that doesn't exist, which result to sending
		 * erroneous failed message back to the VF
		 */
		int num_vf_vlan;

		num_vf_vlan = vf->num_vlan;
		for (i = 0; i < vfl->num_elements && i < num_vf_vlan; i++) {
			u16 vid = vfl->vlan_id[i];

			/* Make sure ice_vsi_kill_vlan is successful before
			 * updating VLAN information
			 */
			if (ice_vsi_kill_vlan(vsi, vid)) {
				v_ret = VIRTCHNL_STATUS_ERR_PARAM;
				goto error_param;
			}

			vf->num_vlan--;
			/* Disable VLAN pruning when the last VLAN is removed */
			if (!vf->num_vlan)
				ice_cfg_vlan_pruning(vsi, false, false);

			/* Disable Unicast/Multicast VLAN promiscuous mode */
			if (vlan_promisc) {
				promisc_m = ICE_PROMISC_VLAN_TX |
					    ICE_PROMISC_VLAN_RX;

				ice_clear_vsi_promisc(hw, vsi->idx,
						      promisc_m, vid);
			}
		}
	}

error_param:
	/* send the response to the VF */
	if (add_v)
		return ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_ADD_VLAN, v_ret,
					     NULL, 0);
	else
		return ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_DEL_VLAN, v_ret,
					     NULL, 0);
}