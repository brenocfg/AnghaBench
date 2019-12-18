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
struct ice_vsi {int dummy; } ;
struct ice_vf {size_t lan_vsi_idx; int /*<<< orphan*/  vf_states; struct ice_pf* pf; } ;
struct ice_pf {struct ice_vsi** vsi; } ;
typedef  enum virtchnl_status_code { ____Placeholder_virtchnl_status_code } virtchnl_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  VIRTCHNL_OP_DISABLE_VLAN_STRIPPING ; 
 int VIRTCHNL_STATUS_ERR_PARAM ; 
 int VIRTCHNL_STATUS_SUCCESS ; 
 int ice_vc_send_msg_to_vf (struct ice_vf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ice_vsi_manage_vlan_stripping (struct ice_vsi*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_vc_dis_vlan_stripping(struct ice_vf *vf)
{
	enum virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	struct ice_pf *pf = vf->pf;
	struct ice_vsi *vsi;

	if (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) {
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		goto error_param;
	}

	vsi = pf->vsi[vf->lan_vsi_idx];
	if (!vsi) {
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		goto error_param;
	}

	if (ice_vsi_manage_vlan_stripping(vsi, false))
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;

error_param:
	return ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_DISABLE_VLAN_STRIPPING,
				     v_ret, NULL, 0);
}