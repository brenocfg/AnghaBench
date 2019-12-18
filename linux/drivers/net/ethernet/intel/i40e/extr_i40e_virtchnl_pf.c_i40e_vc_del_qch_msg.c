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
struct i40e_vf {int adq_enabled; int /*<<< orphan*/  vf_id; scalar_t__ num_tc; int /*<<< orphan*/  vf_states; struct i40e_pf* pf; } ;
struct i40e_pf {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  i40e_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int I40E_SUCCESS ; 
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  VIRTCHNL_OP_DISABLE_CHANNELS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_del_all_cloud_filters (struct i40e_vf*) ; 
 int /*<<< orphan*/  i40e_del_qch (struct i40e_vf*) ; 
 int /*<<< orphan*/  i40e_reset_vf (struct i40e_vf*,int) ; 
 int /*<<< orphan*/  i40e_vc_notify_vf_reset (struct i40e_vf*) ; 
 int i40e_vc_send_resp_to_vf (struct i40e_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_vc_del_qch_msg(struct i40e_vf *vf, u8 *msg)
{
	struct i40e_pf *pf = vf->pf;
	i40e_status aq_ret = 0;

	if (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) {
		aq_ret = I40E_ERR_PARAM;
		goto err;
	}

	if (vf->adq_enabled) {
		i40e_del_all_cloud_filters(vf);
		i40e_del_qch(vf);
		vf->adq_enabled = false;
		vf->num_tc = 0;
		dev_info(&pf->pdev->dev,
			 "Deleting Queue Channels and cloud filters for ADq on VF %d\n",
			 vf->vf_id);
	} else {
		dev_info(&pf->pdev->dev, "VF %d trying to delete queue channels but ADq isn't enabled\n",
			 vf->vf_id);
		aq_ret = I40E_ERR_PARAM;
	}

	/* reset the VF in order to allocate resources */
	i40e_vc_notify_vf_reset(vf);
	i40e_reset_vf(vf, false);

	return I40E_SUCCESS;

err:
	return i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_DISABLE_CHANNELS,
				       aq_ret);
}