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
struct TYPE_3__ {scalar_t__ head; } ;
struct TYPE_4__ {scalar_t__ head; } ;
struct ice_ctl_q_info {int /*<<< orphan*/  sq_lock; TYPE_1__ sq; int /*<<< orphan*/  rq_lock; TYPE_2__ rq; } ;
struct ice_hw {struct ice_ctl_q_info adminq; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_FW_API_VER ; 
 int ice_aq_get_fw_ver (struct ice_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_aq_ver_check (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_shutdown_rq (struct ice_hw*,struct ice_ctl_q_info*) ; 
 int /*<<< orphan*/  ice_shutdown_sq (struct ice_hw*,struct ice_ctl_q_info*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum ice_status ice_init_check_adminq(struct ice_hw *hw)
{
	struct ice_ctl_q_info *cq = &hw->adminq;
	enum ice_status status;

	status = ice_aq_get_fw_ver(hw, NULL);
	if (status)
		goto init_ctrlq_free_rq;

	if (!ice_aq_ver_check(hw)) {
		status = ICE_ERR_FW_API_VER;
		goto init_ctrlq_free_rq;
	}

	return 0;

init_ctrlq_free_rq:
	if (cq->rq.head) {
		ice_shutdown_rq(hw, cq);
		mutex_destroy(&cq->rq_lock);
	}
	if (cq->sq.head) {
		ice_shutdown_sq(hw, cq);
		mutex_destroy(&cq->sq_lock);
	}
	return status;
}