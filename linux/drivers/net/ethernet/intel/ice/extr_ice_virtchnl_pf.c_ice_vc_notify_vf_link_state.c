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
struct virtchnl_pf_event {int /*<<< orphan*/  severity; int /*<<< orphan*/  event; int /*<<< orphan*/  member_0; } ;
struct ice_vf {int /*<<< orphan*/  vf_id; int /*<<< orphan*/  link_up; scalar_t__ link_forced; int /*<<< orphan*/  num_qs_ena; struct ice_pf* pf; } ;
struct ice_hw {TYPE_2__* port_info; } ;
struct ice_pf {struct ice_hw hw; } ;
struct ice_link_status {int link_info; int /*<<< orphan*/  link_speed; } ;
typedef  int /*<<< orphan*/  pfe ;
struct TYPE_3__ {struct ice_link_status link_info; } ;
struct TYPE_4__ {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQ_LINK_SPEED_UNKNOWN ; 
 int ICE_AQ_LINK_UP ; 
 int /*<<< orphan*/  PF_EVENT_SEVERITY_INFO ; 
 int /*<<< orphan*/  VIRTCHNL_EVENT_LINK_CHANGE ; 
 int /*<<< orphan*/  VIRTCHNL_OP_EVENT ; 
 int /*<<< orphan*/  VIRTCHNL_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ice_aq_send_msg_to_vf (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_set_pfe_link (struct ice_vf*,struct virtchnl_pf_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ice_set_pfe_link_forced (struct ice_vf*,struct virtchnl_pf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_vc_notify_vf_link_state(struct ice_vf *vf)
{
	struct virtchnl_pf_event pfe = { 0 };
	struct ice_link_status *ls;
	struct ice_pf *pf = vf->pf;
	struct ice_hw *hw;

	hw = &pf->hw;
	ls = &hw->port_info->phy.link_info;

	pfe.event = VIRTCHNL_EVENT_LINK_CHANGE;
	pfe.severity = PF_EVENT_SEVERITY_INFO;

	/* Always report link is down if the VF queues aren't enabled */
	if (!vf->num_qs_ena)
		ice_set_pfe_link(vf, &pfe, ICE_AQ_LINK_SPEED_UNKNOWN, false);
	else if (vf->link_forced)
		ice_set_pfe_link_forced(vf, &pfe, vf->link_up);
	else
		ice_set_pfe_link(vf, &pfe, ls->link_speed, ls->link_info &
				 ICE_AQ_LINK_UP);

	ice_aq_send_msg_to_vf(hw, vf->vf_id, VIRTCHNL_OP_EVENT,
			      VIRTCHNL_STATUS_SUCCESS, (u8 *)&pfe,
			      sizeof(pfe), NULL);
}