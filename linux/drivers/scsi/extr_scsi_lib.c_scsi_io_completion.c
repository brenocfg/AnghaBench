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
struct scsi_cmnd {int result; struct request* request; TYPE_1__* device; } ;
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_4__ {int result; } ;
struct TYPE_3__ {struct request_queue* request_queue; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_OK ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_LOG_HLCOMPLETE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 unsigned int blk_rq_bytes (struct request*) ; 
 int blk_rq_is_passthrough (struct request*) ; 
 int /*<<< orphan*/  blk_rq_sectors (struct request*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ scsi_end_request (struct request*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  scsi_io_completion_action (struct scsi_cmnd*,int) ; 
 int scsi_io_completion_nz_result (struct scsi_cmnd*,int,scalar_t__*) ; 
 int /*<<< orphan*/  scsi_io_completion_reprep (struct scsi_cmnd*,struct request_queue*) ; 
 scalar_t__ scsi_noretry_cmd (struct scsi_cmnd*) ; 
 TYPE_2__* scsi_req (struct request*) ; 
 scalar_t__ unlikely (int) ; 

void scsi_io_completion(struct scsi_cmnd *cmd, unsigned int good_bytes)
{
	int result = cmd->result;
	struct request_queue *q = cmd->device->request_queue;
	struct request *req = cmd->request;
	blk_status_t blk_stat = BLK_STS_OK;

	if (unlikely(result))	/* a nz result may or may not be an error */
		result = scsi_io_completion_nz_result(cmd, result, &blk_stat);

	if (unlikely(blk_rq_is_passthrough(req))) {
		/*
		 * scsi_result_to_blk_status may have reset the host_byte
		 */
		scsi_req(req)->result = cmd->result;
	}

	/*
	 * Next deal with any sectors which we were able to correctly
	 * handle.
	 */
	SCSI_LOG_HLCOMPLETE(1, scmd_printk(KERN_INFO, cmd,
		"%u sectors total, %d bytes done.\n",
		blk_rq_sectors(req), good_bytes));

	/*
	 * Next deal with any sectors which we were able to correctly
	 * handle. Failed, zero length commands always need to drop down
	 * to retry code. Fast path should return in this block.
	 */
	if (likely(blk_rq_bytes(req) > 0 || blk_stat == BLK_STS_OK)) {
		if (likely(!scsi_end_request(req, blk_stat, good_bytes)))
			return; /* no bytes remaining */
	}

	/* Kill remainder if no retries. */
	if (unlikely(blk_stat && scsi_noretry_cmd(cmd))) {
		if (scsi_end_request(req, blk_stat, blk_rq_bytes(req)))
			WARN_ONCE(true,
			    "Bytes remaining after failed, no-retry command");
		return;
	}

	/*
	 * If there had been no error, but we have leftover bytes in the
	 * requeues just queue the command up again.
	 */
	if (likely(result == 0))
		scsi_io_completion_reprep(cmd, q);
	else
		scsi_io_completion_action(cmd, result);
}