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
struct virtchnl_promisc_info {int flags; int /*<<< orphan*/  vsi_id; } ;
struct i40e_vf {int /*<<< orphan*/  vf_id; int /*<<< orphan*/  vf_states; int /*<<< orphan*/  vf_caps; struct i40e_pf* pf; } ;
struct i40e_pf {TYPE_1__* pdev; } ;
typedef  scalar_t__ i40e_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FLAG_VF_MULTICAST_PROMISC ; 
 int FLAG_VF_UNICAST_PROMISC ; 
 scalar_t__ I40E_ERR_PARAM ; 
 int I40E_MAX_VF_PROMISC_FLAGS ; 
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  I40E_VF_STATE_MC_PROMISC ; 
 int /*<<< orphan*/  I40E_VF_STATE_UC_PROMISC ; 
 int /*<<< orphan*/  I40E_VIRTCHNL_VF_CAP_PRIVILEGE ; 
 int /*<<< orphan*/  VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_config_vf_promiscuous_mode (struct i40e_vf*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  i40e_vc_isvalid_vsi_id (struct i40e_vf*,int /*<<< orphan*/ ) ; 
 int i40e_vc_send_resp_to_vf (struct i40e_vf*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_vc_config_promiscuous_mode_msg(struct i40e_vf *vf, u8 *msg)
{
	struct virtchnl_promisc_info *info =
	    (struct virtchnl_promisc_info *)msg;
	struct i40e_pf *pf = vf->pf;
	i40e_status aq_ret = 0;
	bool allmulti = false;
	bool alluni = false;

	if (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) {
		aq_ret = I40E_ERR_PARAM;
		goto err_out;
	}
	if (!test_bit(I40E_VIRTCHNL_VF_CAP_PRIVILEGE, &vf->vf_caps)) {
		dev_err(&pf->pdev->dev,
			"Unprivileged VF %d is attempting to configure promiscuous mode\n",
			vf->vf_id);

		/* Lie to the VF on purpose, because this is an error we can
		 * ignore. Unprivileged VF is not a virtual channel error.
		 */
		aq_ret = 0;
		goto err_out;
	}

	if (info->flags > I40E_MAX_VF_PROMISC_FLAGS) {
		aq_ret = I40E_ERR_PARAM;
		goto err_out;
	}

	if (!i40e_vc_isvalid_vsi_id(vf, info->vsi_id)) {
		aq_ret = I40E_ERR_PARAM;
		goto err_out;
	}

	/* Multicast promiscuous handling*/
	if (info->flags & FLAG_VF_MULTICAST_PROMISC)
		allmulti = true;

	if (info->flags & FLAG_VF_UNICAST_PROMISC)
		alluni = true;
	aq_ret = i40e_config_vf_promiscuous_mode(vf, info->vsi_id, allmulti,
						 alluni);
	if (aq_ret)
		goto err_out;

	if (allmulti) {
		if (!test_and_set_bit(I40E_VF_STATE_MC_PROMISC,
				      &vf->vf_states))
			dev_info(&pf->pdev->dev,
				 "VF %d successfully set multicast promiscuous mode\n",
				 vf->vf_id);
	} else if (test_and_clear_bit(I40E_VF_STATE_MC_PROMISC,
				      &vf->vf_states))
		dev_info(&pf->pdev->dev,
			 "VF %d successfully unset multicast promiscuous mode\n",
			 vf->vf_id);

	if (alluni) {
		if (!test_and_set_bit(I40E_VF_STATE_UC_PROMISC,
				      &vf->vf_states))
			dev_info(&pf->pdev->dev,
				 "VF %d successfully set unicast promiscuous mode\n",
				 vf->vf_id);
	} else if (test_and_clear_bit(I40E_VF_STATE_UC_PROMISC,
				      &vf->vf_states))
		dev_info(&pf->pdev->dev,
			 "VF %d successfully unset unicast promiscuous mode\n",
			 vf->vf_id);

err_out:
	/* send the response to the VF */
	return i40e_vc_send_resp_to_vf(vf,
				       VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE,
				       aq_ret);
}