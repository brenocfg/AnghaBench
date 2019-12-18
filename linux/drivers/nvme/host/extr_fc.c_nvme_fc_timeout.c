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
struct nvme_fc_fcp_op {struct nvme_fc_ctrl* ctrl; } ;
struct nvme_fc_ctrl {int dummy; } ;
typedef  enum blk_eh_timer_return { ____Placeholder_blk_eh_timer_return } blk_eh_timer_return ;

/* Variables and functions */
 int BLK_EH_RESET_TIMER ; 
 struct nvme_fc_fcp_op* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  nvme_fc_error_recovery (struct nvme_fc_ctrl*,char*) ; 

__attribute__((used)) static enum blk_eh_timer_return
nvme_fc_timeout(struct request *rq, bool reserved)
{
	struct nvme_fc_fcp_op *op = blk_mq_rq_to_pdu(rq);
	struct nvme_fc_ctrl *ctrl = op->ctrl;

	/*
	 * we can't individually ABTS an io without affecting the queue,
	 * thus killing the queue, and thus the association.
	 * So resolve by performing a controller reset, which will stop
	 * the host/io stack, terminate the association on the link,
	 * and recreate an association on the link.
	 */
	nvme_fc_error_recovery(ctrl, "io timeout error");

	/*
	 * the io abort has been initiated. Have the reset timer
	 * restarted and the abort completion will complete the io
	 * shortly. Avoids a synchronous wait while the abort finishes.
	 */
	return BLK_EH_RESET_TIMER;
}