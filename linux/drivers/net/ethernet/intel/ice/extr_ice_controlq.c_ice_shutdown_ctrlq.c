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
struct ice_ctl_q_info {int dummy; } ;
struct ice_hw {struct ice_ctl_q_info mailboxq; struct ice_ctl_q_info adminq; } ;
typedef  enum ice_ctl_q { ____Placeholder_ice_ctl_q } ice_ctl_q ;

/* Variables and functions */
#define  ICE_CTL_Q_ADMIN 129 
#define  ICE_CTL_Q_MAILBOX 128 
 int /*<<< orphan*/  ice_aq_q_shutdown (struct ice_hw*,int) ; 
 int /*<<< orphan*/  ice_check_sq_alive (struct ice_hw*,struct ice_ctl_q_info*) ; 
 int /*<<< orphan*/  ice_shutdown_rq (struct ice_hw*,struct ice_ctl_q_info*) ; 
 int /*<<< orphan*/  ice_shutdown_sq (struct ice_hw*,struct ice_ctl_q_info*) ; 

__attribute__((used)) static void ice_shutdown_ctrlq(struct ice_hw *hw, enum ice_ctl_q q_type)
{
	struct ice_ctl_q_info *cq;

	switch (q_type) {
	case ICE_CTL_Q_ADMIN:
		cq = &hw->adminq;
		if (ice_check_sq_alive(hw, cq))
			ice_aq_q_shutdown(hw, true);
		break;
	case ICE_CTL_Q_MAILBOX:
		cq = &hw->mailboxq;
		break;
	default:
		return;
	}

	ice_shutdown_sq(hw, cq);
	ice_shutdown_rq(hw, cq);
}