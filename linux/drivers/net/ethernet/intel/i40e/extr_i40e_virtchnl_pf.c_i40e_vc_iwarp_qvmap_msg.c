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
struct virtchnl_iwarp_qvlist_info {int dummy; } ;
struct i40e_vf {int /*<<< orphan*/  vf_states; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  I40E_VF_STATE_IWARPENA ; 
 int /*<<< orphan*/  VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP ; 
 int /*<<< orphan*/  VIRTCHNL_OP_RELEASE_IWARP_IRQ_MAP ; 
 scalar_t__ i40e_config_iwarp_qvlist (struct i40e_vf*,struct virtchnl_iwarp_qvlist_info*) ; 
 int /*<<< orphan*/  i40e_release_iwarp_qvlist (struct i40e_vf*) ; 
 int i40e_vc_send_resp_to_vf (struct i40e_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_vc_iwarp_qvmap_msg(struct i40e_vf *vf, u8 *msg, bool config)
{
	struct virtchnl_iwarp_qvlist_info *qvlist_info =
				(struct virtchnl_iwarp_qvlist_info *)msg;
	i40e_status aq_ret = 0;

	if (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states) ||
	    !test_bit(I40E_VF_STATE_IWARPENA, &vf->vf_states)) {
		aq_ret = I40E_ERR_PARAM;
		goto error_param;
	}

	if (config) {
		if (i40e_config_iwarp_qvlist(vf, qvlist_info))
			aq_ret = I40E_ERR_PARAM;
	} else {
		i40e_release_iwarp_qvlist(vf);
	}

error_param:
	/* send the response to the VF */
	return i40e_vc_send_resp_to_vf(vf,
			       config ? VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP :
			       VIRTCHNL_OP_RELEASE_IWARP_IRQ_MAP,
			       aq_ret);
}