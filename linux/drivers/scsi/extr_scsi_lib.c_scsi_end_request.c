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
struct scsi_device {int /*<<< orphan*/  requeue_work; TYPE_1__* host; struct request_queue* request_queue; } ;
struct scsi_cmnd {int flags; int /*<<< orphan*/  rcu; struct scsi_device* device; } ;
struct request_queue {int /*<<< orphan*/  q_usage_counter; } ;
struct request {int /*<<< orphan*/  rq_disk; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_4__ {scalar_t__ single_lun; } ;
struct TYPE_3__ {int /*<<< orphan*/  starved_list; } ;

/* Variables and functions */
 int SCMD_INITIALIZED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_disk_randomness (int /*<<< orphan*/ ) ; 
 struct scsi_cmnd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_mq_run_hw_queues (struct request_queue*,int) ; 
 scalar_t__ blk_queue_add_random (struct request_queue*) ; 
 int /*<<< orphan*/  blk_rq_is_scsi (struct request*) ; 
 scalar_t__ blk_update_request (struct request*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  destroy_rcu_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kblockd_schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_mq_uninit_cmd (struct scsi_cmnd*) ; 
 TYPE_2__* scsi_target (struct scsi_device*) ; 

__attribute__((used)) static bool scsi_end_request(struct request *req, blk_status_t error,
		unsigned int bytes)
{
	struct scsi_cmnd *cmd = blk_mq_rq_to_pdu(req);
	struct scsi_device *sdev = cmd->device;
	struct request_queue *q = sdev->request_queue;

	if (blk_update_request(req, error, bytes))
		return true;

	if (blk_queue_add_random(q))
		add_disk_randomness(req->rq_disk);

	if (!blk_rq_is_scsi(req)) {
		WARN_ON_ONCE(!(cmd->flags & SCMD_INITIALIZED));
		cmd->flags &= ~SCMD_INITIALIZED;
	}

	/*
	 * Calling rcu_barrier() is not necessary here because the
	 * SCSI error handler guarantees that the function called by
	 * call_rcu() has been called before scsi_end_request() is
	 * called.
	 */
	destroy_rcu_head(&cmd->rcu);

	/*
	 * In the MQ case the command gets freed by __blk_mq_end_request,
	 * so we have to do all cleanup that depends on it earlier.
	 *
	 * We also can't kick the queues from irq context, so we
	 * will have to defer it to a workqueue.
	 */
	scsi_mq_uninit_cmd(cmd);

	/*
	 * queue is still alive, so grab the ref for preventing it
	 * from being cleaned up during running queue.
	 */
	percpu_ref_get(&q->q_usage_counter);

	__blk_mq_end_request(req, error);

	if (scsi_target(sdev)->single_lun ||
	    !list_empty(&sdev->host->starved_list))
		kblockd_schedule_work(&sdev->requeue_work);
	else
		blk_mq_run_hw_queues(q, true);

	percpu_ref_put(&q->q_usage_counter);
	return false;
}