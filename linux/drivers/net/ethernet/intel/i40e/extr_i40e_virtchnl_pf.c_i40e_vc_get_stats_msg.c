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
struct virtchnl_queue_select {int /*<<< orphan*/  vsi_id; } ;
struct i40e_eth_stats {int dummy; } ;
struct i40e_vsi {struct i40e_eth_stats eth_stats; } ;
struct i40e_vf {size_t lan_vsi_idx; int /*<<< orphan*/  vf_states; struct i40e_pf* pf; } ;
struct i40e_pf {struct i40e_vsi** vsi; } ;
typedef  int /*<<< orphan*/  stats ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  VIRTCHNL_OP_GET_STATS ; 
 int /*<<< orphan*/  i40e_update_eth_stats (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vc_isvalid_vsi_id (struct i40e_vf*,int /*<<< orphan*/ ) ; 
 int i40e_vc_send_msg_to_vf (struct i40e_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct i40e_eth_stats*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_vc_get_stats_msg(struct i40e_vf *vf, u8 *msg)
{
	struct virtchnl_queue_select *vqs =
	    (struct virtchnl_queue_select *)msg;
	struct i40e_pf *pf = vf->pf;
	struct i40e_eth_stats stats;
	i40e_status aq_ret = 0;
	struct i40e_vsi *vsi;

	memset(&stats, 0, sizeof(struct i40e_eth_stats));

	if (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) {
		aq_ret = I40E_ERR_PARAM;
		goto error_param;
	}

	if (!i40e_vc_isvalid_vsi_id(vf, vqs->vsi_id)) {
		aq_ret = I40E_ERR_PARAM;
		goto error_param;
	}

	vsi = pf->vsi[vf->lan_vsi_idx];
	if (!vsi) {
		aq_ret = I40E_ERR_PARAM;
		goto error_param;
	}
	i40e_update_eth_stats(vsi);
	stats = vsi->eth_stats;

error_param:
	/* send the response back to the VF */
	return i40e_vc_send_msg_to_vf(vf, VIRTCHNL_OP_GET_STATS, aq_ret,
				      (u8 *)&stats, sizeof(stats));
}