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
struct virtchnl_rss_key {scalar_t__ key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  vsi_id; } ;
struct i40e_vsi {int dummy; } ;
struct i40e_vf {size_t lan_vsi_idx; int /*<<< orphan*/  vf_states; struct i40e_pf* pf; } ;
struct i40e_pf {struct i40e_vsi** vsi; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 scalar_t__ I40E_HKEY_ARRAY_SIZE ; 
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  VIRTCHNL_OP_CONFIG_RSS_KEY ; 
 int /*<<< orphan*/  i40e_config_rss (struct i40e_vsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_vc_isvalid_vsi_id (struct i40e_vf*,int /*<<< orphan*/ ) ; 
 int i40e_vc_send_resp_to_vf (struct i40e_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_vc_config_rss_key(struct i40e_vf *vf, u8 *msg)
{
	struct virtchnl_rss_key *vrk =
		(struct virtchnl_rss_key *)msg;
	struct i40e_pf *pf = vf->pf;
	struct i40e_vsi *vsi = NULL;
	i40e_status aq_ret = 0;

	if (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states) ||
	    !i40e_vc_isvalid_vsi_id(vf, vrk->vsi_id) ||
	    (vrk->key_len != I40E_HKEY_ARRAY_SIZE)) {
		aq_ret = I40E_ERR_PARAM;
		goto err;
	}

	vsi = pf->vsi[vf->lan_vsi_idx];
	aq_ret = i40e_config_rss(vsi, vrk->key, NULL, 0);
err:
	/* send the response to the VF */
	return i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_CONFIG_RSS_KEY,
				       aq_ret);
}