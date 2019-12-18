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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct virtchnl_rss_lut {scalar_t__ lut_entries; scalar_t__* lut; int /*<<< orphan*/  vsi_id; } ;
struct i40e_vsi {int dummy; } ;
struct i40e_vf {scalar_t__ num_queue_pairs; size_t lan_vsi_idx; int /*<<< orphan*/  vf_states; struct i40e_pf* pf; } ;
struct i40e_pf {struct i40e_vsi** vsi; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 scalar_t__ I40E_VF_HLUT_ARRAY_SIZE ; 
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  VIRTCHNL_OP_CONFIG_RSS_LUT ; 
 int /*<<< orphan*/  i40e_config_rss (struct i40e_vsi*,int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  i40e_vc_isvalid_vsi_id (struct i40e_vf*,int /*<<< orphan*/ ) ; 
 int i40e_vc_send_resp_to_vf (struct i40e_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_vc_config_rss_lut(struct i40e_vf *vf, u8 *msg)
{
	struct virtchnl_rss_lut *vrl =
		(struct virtchnl_rss_lut *)msg;
	struct i40e_pf *pf = vf->pf;
	struct i40e_vsi *vsi = NULL;
	i40e_status aq_ret = 0;
	u16 i;

	if (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states) ||
	    !i40e_vc_isvalid_vsi_id(vf, vrl->vsi_id) ||
	    (vrl->lut_entries != I40E_VF_HLUT_ARRAY_SIZE)) {
		aq_ret = I40E_ERR_PARAM;
		goto err;
	}

	for (i = 0; i < vrl->lut_entries; i++)
		if (vrl->lut[i] >= vf->num_queue_pairs) {
			aq_ret = I40E_ERR_PARAM;
			goto err;
		}

	vsi = pf->vsi[vf->lan_vsi_idx];
	aq_ret = i40e_config_rss(vsi, NULL, vrl->lut, I40E_VF_HLUT_ARRAY_SIZE);
	/* send the response to the VF */
err:
	return i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_CONFIG_RSS_LUT,
				       aq_ret);
}