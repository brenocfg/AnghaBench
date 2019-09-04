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
struct TYPE_4__ {scalar_t__ head; } ;
struct TYPE_3__ {scalar_t__ head; } ;
struct ice_ctl_q_info {int /*<<< orphan*/  rq_lock; TYPE_2__ rq; int /*<<< orphan*/  sq_lock; TYPE_1__ sq; } ;
struct ice_hw {struct ice_ctl_q_info adminq; } ;
typedef  enum ice_ctl_q { ____Placeholder_ice_ctl_q } ice_ctl_q ;

/* Variables and functions */
#define  ICE_CTL_Q_ADMIN 128 
 int /*<<< orphan*/  ice_aq_q_shutdown (struct ice_hw*,int) ; 
 int /*<<< orphan*/  ice_check_sq_alive (struct ice_hw*,struct ice_ctl_q_info*) ; 
 int /*<<< orphan*/  ice_shutdown_rq (struct ice_hw*,struct ice_ctl_q_info*) ; 
 int /*<<< orphan*/  ice_shutdown_sq (struct ice_hw*,struct ice_ctl_q_info*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ice_shutdown_ctrlq(struct ice_hw *hw, enum ice_ctl_q q_type)
{
	struct ice_ctl_q_info *cq;

	switch (q_type) {
	case ICE_CTL_Q_ADMIN:
		cq = &hw->adminq;
		if (ice_check_sq_alive(hw, cq))
			ice_aq_q_shutdown(hw, true);
		break;
	default:
		return;
	}

	if (cq->sq.head) {
		ice_shutdown_sq(hw, cq);
		mutex_destroy(&cq->sq_lock);
	}
	if (cq->rq.head) {
		ice_shutdown_rq(hw, cq);
		mutex_destroy(&cq->rq_lock);
	}
}