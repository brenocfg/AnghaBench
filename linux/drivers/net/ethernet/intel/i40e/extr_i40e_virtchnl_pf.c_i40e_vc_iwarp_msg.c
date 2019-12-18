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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40e_vf {int vf_id; int /*<<< orphan*/  vf_states; struct i40e_pf* pf; } ;
struct TYPE_3__ {int vf_base_id; } ;
struct TYPE_4__ {TYPE_1__ func_caps; } ;
struct i40e_pf {size_t lan_vsi; int /*<<< orphan*/ * vsi; TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  I40E_VF_STATE_IWARPENA ; 
 int /*<<< orphan*/  VIRTCHNL_OP_IWARP ; 
 int /*<<< orphan*/  i40e_notify_client_of_vf_msg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int i40e_vc_send_resp_to_vf (struct i40e_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_vc_iwarp_msg(struct i40e_vf *vf, u8 *msg, u16 msglen)
{
	struct i40e_pf *pf = vf->pf;
	int abs_vf_id = vf->vf_id + pf->hw.func_caps.vf_base_id;
	i40e_status aq_ret = 0;

	if (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states) ||
	    !test_bit(I40E_VF_STATE_IWARPENA, &vf->vf_states)) {
		aq_ret = I40E_ERR_PARAM;
		goto error_param;
	}

	i40e_notify_client_of_vf_msg(pf->vsi[pf->lan_vsi], abs_vf_id,
				     msg, msglen);

error_param:
	/* send the response to the VF */
	return i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_IWARP,
				       aq_ret);
}