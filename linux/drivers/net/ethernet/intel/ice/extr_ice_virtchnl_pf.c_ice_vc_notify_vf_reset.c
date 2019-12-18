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
struct virtchnl_pf_event {int /*<<< orphan*/  severity; int /*<<< orphan*/  event; } ;
struct ice_vf {scalar_t__ vf_id; TYPE_1__* pf; int /*<<< orphan*/  vf_states; } ;
typedef  int /*<<< orphan*/  pfe ;
struct TYPE_2__ {scalar_t__ num_alloc_vfs; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  ICE_VF_STATE_INIT ; 
 int /*<<< orphan*/  PF_EVENT_SEVERITY_CERTAIN_DOOM ; 
 int /*<<< orphan*/  VIRTCHNL_EVENT_RESET_IMPENDING ; 
 int /*<<< orphan*/  VIRTCHNL_OP_EVENT ; 
 int /*<<< orphan*/  VIRTCHNL_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ice_aq_send_msg_to_vf (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_vc_notify_vf_reset(struct ice_vf *vf)
{
	struct virtchnl_pf_event pfe;

	/* validate the request */
	if (!vf || vf->vf_id >= vf->pf->num_alloc_vfs)
		return;

	/* verify if the VF is in either init or active before proceeding */
	if (!test_bit(ICE_VF_STATE_INIT, vf->vf_states) &&
	    !test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states))
		return;

	pfe.event = VIRTCHNL_EVENT_RESET_IMPENDING;
	pfe.severity = PF_EVENT_SEVERITY_CERTAIN_DOOM;
	ice_aq_send_msg_to_vf(&vf->pf->hw, vf->vf_id, VIRTCHNL_OP_EVENT,
			      VIRTCHNL_STATUS_SUCCESS, (u8 *)&pfe, sizeof(pfe),
			      NULL);
}