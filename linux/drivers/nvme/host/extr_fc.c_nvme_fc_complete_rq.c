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
struct request {int dummy; } ;
struct nvme_fc_fcp_op {int /*<<< orphan*/  state; struct nvme_fc_ctrl* ctrl; } ;
struct nvme_fc_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCPOP_STATE_IDLE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nvme_fc_fcp_op* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  nvme_complete_rq (struct request*) ; 
 int /*<<< orphan*/  nvme_fc_ctrl_put (struct nvme_fc_ctrl*) ; 
 int /*<<< orphan*/  nvme_fc_unmap_data (struct nvme_fc_ctrl*,struct request*,struct nvme_fc_fcp_op*) ; 

__attribute__((used)) static void
nvme_fc_complete_rq(struct request *rq)
{
	struct nvme_fc_fcp_op *op = blk_mq_rq_to_pdu(rq);
	struct nvme_fc_ctrl *ctrl = op->ctrl;

	atomic_set(&op->state, FCPOP_STATE_IDLE);

	nvme_fc_unmap_data(ctrl, rq, op);
	nvme_complete_rq(rq);
	nvme_fc_ctrl_put(ctrl);
}