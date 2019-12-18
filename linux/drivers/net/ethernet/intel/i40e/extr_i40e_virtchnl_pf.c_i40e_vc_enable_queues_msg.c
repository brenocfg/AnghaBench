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
struct virtchnl_queue_select {scalar_t__ rx_queues; scalar_t__ tx_queues; int /*<<< orphan*/  vsi_id; } ;
struct i40e_vf {size_t lan_vsi_idx; int num_tc; int queues_enabled; TYPE_1__* ch; scalar_t__ adq_enabled; int /*<<< orphan*/  vf_states; struct i40e_pf* pf; } ;
struct i40e_pf {int /*<<< orphan*/ * vsi; } ;
typedef  int /*<<< orphan*/  i40e_status ;
struct TYPE_2__ {size_t vsi_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int /*<<< orphan*/  I40E_ERR_TIMEOUT ; 
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  VIRTCHNL_OP_ENABLE_QUEUES ; 
 scalar_t__ i40e_ctrl_vf_rx_rings (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ i40e_ctrl_vf_tx_rings (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  i40e_vc_isvalid_vsi_id (struct i40e_vf*,int /*<<< orphan*/ ) ; 
 int i40e_vc_send_resp_to_vf (struct i40e_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_vsi_start_rings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_vc_enable_queues_msg(struct i40e_vf *vf, u8 *msg)
{
	struct virtchnl_queue_select *vqs =
	    (struct virtchnl_queue_select *)msg;
	struct i40e_pf *pf = vf->pf;
	i40e_status aq_ret = 0;
	int i;

	if (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) {
		aq_ret = I40E_ERR_PARAM;
		goto error_param;
	}

	if (!i40e_vc_isvalid_vsi_id(vf, vqs->vsi_id)) {
		aq_ret = I40E_ERR_PARAM;
		goto error_param;
	}

	if ((0 == vqs->rx_queues) && (0 == vqs->tx_queues)) {
		aq_ret = I40E_ERR_PARAM;
		goto error_param;
	}

	/* Use the queue bit map sent by the VF */
	if (i40e_ctrl_vf_rx_rings(pf->vsi[vf->lan_vsi_idx], vqs->rx_queues,
				  true)) {
		aq_ret = I40E_ERR_TIMEOUT;
		goto error_param;
	}
	if (i40e_ctrl_vf_tx_rings(pf->vsi[vf->lan_vsi_idx], vqs->tx_queues,
				  true)) {
		aq_ret = I40E_ERR_TIMEOUT;
		goto error_param;
	}

	/* need to start the rings for additional ADq VSI's as well */
	if (vf->adq_enabled) {
		/* zero belongs to LAN VSI */
		for (i = 1; i < vf->num_tc; i++) {
			if (i40e_vsi_start_rings(pf->vsi[vf->ch[i].vsi_idx]))
				aq_ret = I40E_ERR_TIMEOUT;
		}
	}

	vf->queues_enabled = true;

error_param:
	/* send the response to the VF */
	return i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_ENABLE_QUEUES,
				       aq_ret);
}