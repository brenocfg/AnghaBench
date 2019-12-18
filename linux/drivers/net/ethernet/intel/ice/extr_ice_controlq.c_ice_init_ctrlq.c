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
struct ice_ctl_q_info {int qtype; int /*<<< orphan*/  sq_cmd_timeout; int /*<<< orphan*/  sq_buf_size; int /*<<< orphan*/  rq_buf_size; int /*<<< orphan*/  num_sq_entries; int /*<<< orphan*/  num_rq_entries; } ;
struct ice_hw {struct ice_ctl_q_info mailboxq; struct ice_ctl_q_info adminq; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_ctl_q { ____Placeholder_ice_ctl_q } ice_ctl_q ;

/* Variables and functions */
#define  ICE_CTL_Q_ADMIN 129 
#define  ICE_CTL_Q_MAILBOX 128 
 int /*<<< orphan*/  ICE_CTL_Q_SQ_CMD_TIMEOUT ; 
 int ICE_ERR_CFG ; 
 int ICE_ERR_PARAM ; 
 int /*<<< orphan*/  ice_adminq_init_regs (struct ice_hw*) ; 
 int ice_init_rq (struct ice_hw*,struct ice_ctl_q_info*) ; 
 int ice_init_sq (struct ice_hw*,struct ice_ctl_q_info*) ; 
 int /*<<< orphan*/  ice_mailbox_init_regs (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_shutdown_sq (struct ice_hw*,struct ice_ctl_q_info*) ; 

__attribute__((used)) static enum ice_status ice_init_ctrlq(struct ice_hw *hw, enum ice_ctl_q q_type)
{
	struct ice_ctl_q_info *cq;
	enum ice_status ret_code;

	switch (q_type) {
	case ICE_CTL_Q_ADMIN:
		ice_adminq_init_regs(hw);
		cq = &hw->adminq;
		break;
	case ICE_CTL_Q_MAILBOX:
		ice_mailbox_init_regs(hw);
		cq = &hw->mailboxq;
		break;
	default:
		return ICE_ERR_PARAM;
	}
	cq->qtype = q_type;

	/* verify input for valid configuration */
	if (!cq->num_rq_entries || !cq->num_sq_entries ||
	    !cq->rq_buf_size || !cq->sq_buf_size) {
		return ICE_ERR_CFG;
	}

	/* setup SQ command write back timeout */
	cq->sq_cmd_timeout = ICE_CTL_Q_SQ_CMD_TIMEOUT;

	/* allocate the ATQ */
	ret_code = ice_init_sq(hw, cq);
	if (ret_code)
		return ret_code;

	/* allocate the ARQ */
	ret_code = ice_init_rq(hw, cq);
	if (ret_code)
		goto init_ctrlq_free_sq;

	/* success! */
	return 0;

init_ctrlq_free_sq:
	ice_shutdown_sq(hw, cq);
	return ret_code;
}