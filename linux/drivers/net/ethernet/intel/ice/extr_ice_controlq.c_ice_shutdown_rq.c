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
struct ice_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ count; int /*<<< orphan*/  bah; int /*<<< orphan*/  bal; int /*<<< orphan*/  len; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct ice_ctl_q_info {int /*<<< orphan*/  rq_lock; TYPE_1__ rq; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_NOT_READY ; 
 int /*<<< orphan*/  ICE_FREE_CQ_BUFS (struct ice_hw*,struct ice_ctl_q_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_free_cq_ring (struct ice_hw*,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rq ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_shutdown_rq(struct ice_hw *hw, struct ice_ctl_q_info *cq)
{
	enum ice_status ret_code = 0;

	mutex_lock(&cq->rq_lock);

	if (!cq->rq.count) {
		ret_code = ICE_ERR_NOT_READY;
		goto shutdown_rq_out;
	}

	/* Stop Control Queue processing */
	wr32(hw, cq->rq.head, 0);
	wr32(hw, cq->rq.tail, 0);
	wr32(hw, cq->rq.len, 0);
	wr32(hw, cq->rq.bal, 0);
	wr32(hw, cq->rq.bah, 0);

	/* set rq.count to 0 to indicate uninitialized queue */
	cq->rq.count = 0;

	/* free ring buffers and the ring itself */
	ICE_FREE_CQ_BUFS(hw, cq, rq);
	ice_free_cq_ring(hw, &cq->rq);

shutdown_rq_out:
	mutex_unlock(&cq->rq_lock);
	return ret_code;
}