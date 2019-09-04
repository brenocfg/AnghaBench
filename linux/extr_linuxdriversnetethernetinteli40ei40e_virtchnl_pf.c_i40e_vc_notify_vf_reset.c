#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct virtchnl_pf_event {int /*<<< orphan*/  severity; int /*<<< orphan*/  event; } ;
struct i40e_vf {int vf_id; TYPE_2__* pf; int /*<<< orphan*/  vf_states; } ;
struct TYPE_4__ {scalar_t__ vf_base_id; } ;
struct TYPE_6__ {TYPE_1__ func_caps; } ;
struct TYPE_5__ {int num_alloc_vfs; TYPE_3__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  I40E_VF_STATE_INIT ; 
 int /*<<< orphan*/  PF_EVENT_SEVERITY_CERTAIN_DOOM ; 
 int /*<<< orphan*/  VIRTCHNL_EVENT_RESET_IMPENDING ; 
 int /*<<< orphan*/  VIRTCHNL_OP_EVENT ; 
 int /*<<< orphan*/  i40e_aq_send_msg_to_vf (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void i40e_vc_notify_vf_reset(struct i40e_vf *vf)
{
	struct virtchnl_pf_event pfe;
	int abs_vf_id;

	/* validate the request */
	if (!vf || vf->vf_id >= vf->pf->num_alloc_vfs)
		return;

	/* verify if the VF is in either init or active before proceeding */
	if (!test_bit(I40E_VF_STATE_INIT, &vf->vf_states) &&
	    !test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states))
		return;

	abs_vf_id = vf->vf_id + (int)vf->pf->hw.func_caps.vf_base_id;

	pfe.event = VIRTCHNL_EVENT_RESET_IMPENDING;
	pfe.severity = PF_EVENT_SEVERITY_CERTAIN_DOOM;
	i40e_aq_send_msg_to_vf(&vf->pf->hw, abs_vf_id, VIRTCHNL_OP_EVENT,
			       0, (u8 *)&pfe,
			       sizeof(struct virtchnl_pf_event), NULL);
}