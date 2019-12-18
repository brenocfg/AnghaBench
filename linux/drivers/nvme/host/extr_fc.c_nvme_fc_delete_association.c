#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int queue_count; int /*<<< orphan*/  admin_q; scalar_t__ tagset; } ;
struct nvme_fc_ctrl {int assoc_active; scalar_t__ iocnt; TYPE_1__ ctrl; int /*<<< orphan*/ * queues; scalar_t__ association_id; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  ioabort_wait; int /*<<< orphan*/  admin_tag_set; int /*<<< orphan*/  tag_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCCTRL_TERMIO ; 
 int /*<<< orphan*/  __nvme_fc_delete_hw_queue (struct nvme_fc_ctrl*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_quiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_tagset_busy_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  blk_mq_tagset_wait_completed_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_fc_abort_aen_ops (struct nvme_fc_ctrl*) ; 
 int /*<<< orphan*/  nvme_fc_ctlr_inactive_on_rport (struct nvme_fc_ctrl*) ; 
 int /*<<< orphan*/  nvme_fc_delete_hw_io_queues (struct nvme_fc_ctrl*) ; 
 int /*<<< orphan*/  nvme_fc_free_io_queues (struct nvme_fc_ctrl*) ; 
 int /*<<< orphan*/  nvme_fc_free_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_fc_term_aen_ops (struct nvme_fc_ctrl*) ; 
 int /*<<< orphan*/  nvme_fc_terminate_exchange ; 
 int /*<<< orphan*/  nvme_fc_xmt_disconnect_assoc (struct nvme_fc_ctrl*) ; 
 int /*<<< orphan*/  nvme_start_queues (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_stop_queues (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_lock_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_fc_delete_association(struct nvme_fc_ctrl *ctrl)
{
	unsigned long flags;

	if (!ctrl->assoc_active)
		return;
	ctrl->assoc_active = false;

	spin_lock_irqsave(&ctrl->lock, flags);
	ctrl->flags |= FCCTRL_TERMIO;
	ctrl->iocnt = 0;
	spin_unlock_irqrestore(&ctrl->lock, flags);

	/*
	 * If io queues are present, stop them and terminate all outstanding
	 * ios on them. As FC allocates FC exchange for each io, the
	 * transport must contact the LLDD to terminate the exchange,
	 * thus releasing the FC exchange. We use blk_mq_tagset_busy_itr()
	 * to tell us what io's are busy and invoke a transport routine
	 * to kill them with the LLDD.  After terminating the exchange
	 * the LLDD will call the transport's normal io done path, but it
	 * will have an aborted status. The done path will return the
	 * io requests back to the block layer as part of normal completions
	 * (but with error status).
	 */
	if (ctrl->ctrl.queue_count > 1) {
		nvme_stop_queues(&ctrl->ctrl);
		blk_mq_tagset_busy_iter(&ctrl->tag_set,
				nvme_fc_terminate_exchange, &ctrl->ctrl);
		blk_mq_tagset_wait_completed_request(&ctrl->tag_set);
	}

	/*
	 * Other transports, which don't have link-level contexts bound
	 * to sqe's, would try to gracefully shutdown the controller by
	 * writing the registers for shutdown and polling (call
	 * nvme_shutdown_ctrl()). Given a bunch of i/o was potentially
	 * just aborted and we will wait on those contexts, and given
	 * there was no indication of how live the controlelr is on the
	 * link, don't send more io to create more contexts for the
	 * shutdown. Let the controller fail via keepalive failure if
	 * its still present.
	 */

	/*
	 * clean up the admin queue. Same thing as above.
	 * use blk_mq_tagset_busy_itr() and the transport routine to
	 * terminate the exchanges.
	 */
	blk_mq_quiesce_queue(ctrl->ctrl.admin_q);
	blk_mq_tagset_busy_iter(&ctrl->admin_tag_set,
				nvme_fc_terminate_exchange, &ctrl->ctrl);
	blk_mq_tagset_wait_completed_request(&ctrl->admin_tag_set);

	/* kill the aens as they are a separate path */
	nvme_fc_abort_aen_ops(ctrl);

	/* wait for all io that had to be aborted */
	spin_lock_irq(&ctrl->lock);
	wait_event_lock_irq(ctrl->ioabort_wait, ctrl->iocnt == 0, ctrl->lock);
	ctrl->flags &= ~FCCTRL_TERMIO;
	spin_unlock_irq(&ctrl->lock);

	nvme_fc_term_aen_ops(ctrl);

	/*
	 * send a Disconnect(association) LS to fc-nvme target
	 * Note: could have been sent at top of process, but
	 * cleaner on link traffic if after the aborts complete.
	 * Note: if association doesn't exist, association_id will be 0
	 */
	if (ctrl->association_id)
		nvme_fc_xmt_disconnect_assoc(ctrl);

	if (ctrl->ctrl.tagset) {
		nvme_fc_delete_hw_io_queues(ctrl);
		nvme_fc_free_io_queues(ctrl);
	}

	__nvme_fc_delete_hw_queue(ctrl, &ctrl->queues[0], 0);
	nvme_fc_free_queue(&ctrl->queues[0]);

	/* re-enable the admin_q so anything new can fast fail */
	blk_mq_unquiesce_queue(ctrl->ctrl.admin_q);

	/* resume the io queues so that things will fast fail */
	nvme_start_queues(&ctrl->ctrl);

	nvme_fc_ctlr_inactive_on_rport(ctrl);
}