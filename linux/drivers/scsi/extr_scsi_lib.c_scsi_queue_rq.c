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
struct scsi_device {scalar_t__ sdev_state; int /*<<< orphan*/  device_busy; scalar_t__ simple_tags; struct Scsi_Host* host; } ;
struct scsi_cmnd {int /*<<< orphan*/  scsi_done; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;
struct request_queue {struct scsi_device* queuedata; } ;
struct request {int rq_flags; struct request_queue* q; } ;
struct blk_mq_queue_data {scalar_t__ last; struct request* rq; } ;
struct blk_mq_hw_ctx {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int blk_status_t ;
struct TYPE_4__ {int result; } ;
struct TYPE_3__ {scalar_t__ can_queue; int /*<<< orphan*/  target_busy; } ;

/* Variables and functions */
 int BLK_STS_DEV_RESOURCE ; 
#define  BLK_STS_OK 129 
#define  BLK_STS_RESOURCE 128 
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int RQF_DONTPREP ; 
 int /*<<< orphan*/  SCMD_LAST ; 
 int /*<<< orphan*/  SCMD_PRESERVED_FLAGS ; 
 int /*<<< orphan*/  SCMD_STATE_COMPLETE ; 
 int /*<<< orphan*/  SCMD_TAGGED ; 
 scalar_t__ SDEV_RUNNING ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct scsi_cmnd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_dec_host_busy (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_device_blocked (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_device_online (struct scsi_device*) ; 
 int scsi_dispatch_cmd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_host_queue_ready (struct request_queue*,struct Scsi_Host*,struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_init_cmd_errh (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_mq_done ; 
 int scsi_mq_prep_fn (struct request*) ; 
 int /*<<< orphan*/  scsi_mq_put_budget (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  scsi_mq_uninit_cmd (struct scsi_cmnd*) ; 
 int scsi_prep_state_check (struct scsi_device*,struct request*) ; 
 TYPE_2__* scsi_req (struct request*) ; 
 int /*<<< orphan*/  scsi_set_blocked (struct scsi_cmnd*,int) ; 
 TYPE_1__* scsi_target (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_target_queue_ready (struct Scsi_Host*,struct scsi_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static blk_status_t scsi_queue_rq(struct blk_mq_hw_ctx *hctx,
			 const struct blk_mq_queue_data *bd)
{
	struct request *req = bd->rq;
	struct request_queue *q = req->q;
	struct scsi_device *sdev = q->queuedata;
	struct Scsi_Host *shost = sdev->host;
	struct scsi_cmnd *cmd = blk_mq_rq_to_pdu(req);
	blk_status_t ret;
	int reason;

	/*
	 * If the device is not in running state we will reject some or all
	 * commands.
	 */
	if (unlikely(sdev->sdev_state != SDEV_RUNNING)) {
		ret = scsi_prep_state_check(sdev, req);
		if (ret != BLK_STS_OK)
			goto out_put_budget;
	}

	ret = BLK_STS_RESOURCE;
	if (!scsi_target_queue_ready(shost, sdev))
		goto out_put_budget;
	if (!scsi_host_queue_ready(q, shost, sdev))
		goto out_dec_target_busy;

	if (!(req->rq_flags & RQF_DONTPREP)) {
		ret = scsi_mq_prep_fn(req);
		if (ret != BLK_STS_OK)
			goto out_dec_host_busy;
		req->rq_flags |= RQF_DONTPREP;
	} else {
		clear_bit(SCMD_STATE_COMPLETE, &cmd->state);
		blk_mq_start_request(req);
	}

	cmd->flags &= SCMD_PRESERVED_FLAGS;
	if (sdev->simple_tags)
		cmd->flags |= SCMD_TAGGED;
	if (bd->last)
		cmd->flags |= SCMD_LAST;

	scsi_init_cmd_errh(cmd);
	cmd->scsi_done = scsi_mq_done;

	reason = scsi_dispatch_cmd(cmd);
	if (reason) {
		scsi_set_blocked(cmd, reason);
		ret = BLK_STS_RESOURCE;
		goto out_dec_host_busy;
	}

	return BLK_STS_OK;

out_dec_host_busy:
	scsi_dec_host_busy(shost);
out_dec_target_busy:
	if (scsi_target(sdev)->can_queue > 0)
		atomic_dec(&scsi_target(sdev)->target_busy);
out_put_budget:
	scsi_mq_put_budget(hctx);
	switch (ret) {
	case BLK_STS_OK:
		break;
	case BLK_STS_RESOURCE:
		if (atomic_read(&sdev->device_busy) ||
		    scsi_device_blocked(sdev))
			ret = BLK_STS_DEV_RESOURCE;
		break;
	default:
		if (unlikely(!scsi_device_online(sdev)))
			scsi_req(req)->result = DID_NO_CONNECT << 16;
		else
			scsi_req(req)->result = DID_ERROR << 16;
		/*
		 * Make sure to release all allocated resources when
		 * we hit an error, as we will never see this command
		 * again.
		 */
		if (req->rq_flags & RQF_DONTPREP)
			scsi_mq_uninit_cmd(cmd);
		break;
	}
	return ret;
}