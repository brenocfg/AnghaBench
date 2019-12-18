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
struct scsi_cmnd {int allowed; scalar_t__ jiffies_at_alloc; TYPE_1__* device; scalar_t__ result; int /*<<< orphan*/  eh_entry; } ;
struct request {int timeout; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioerr_cnt; int /*<<< orphan*/  iodone_cnt; } ;

/* Variables and functions */
#define  ADD_TO_MLQUEUE 130 
 unsigned long HZ ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_ERR ; 
#define  NEEDS_RETRY 129 
 int /*<<< orphan*/  SCSI_MLQUEUE_DEVICE_BUSY ; 
 int /*<<< orphan*/  SCSI_MLQUEUE_EH_RETRY ; 
#define  SUCCESS 128 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct scsi_cmnd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,unsigned long) ; 
 int scsi_decide_disposition (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_eh_scmd_add (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_finish_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_log_completion (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  scsi_queue_insert (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsi_softirq_done(struct request *rq)
{
	struct scsi_cmnd *cmd = blk_mq_rq_to_pdu(rq);
	unsigned long wait_for = (cmd->allowed + 1) * rq->timeout;
	int disposition;

	INIT_LIST_HEAD(&cmd->eh_entry);

	atomic_inc(&cmd->device->iodone_cnt);
	if (cmd->result)
		atomic_inc(&cmd->device->ioerr_cnt);

	disposition = scsi_decide_disposition(cmd);
	if (disposition != SUCCESS &&
	    time_before(cmd->jiffies_at_alloc + wait_for, jiffies)) {
		scmd_printk(KERN_ERR, cmd,
			    "timing out command, waited %lus\n",
			    wait_for/HZ);
		disposition = SUCCESS;
	}

	scsi_log_completion(cmd, disposition);

	switch (disposition) {
		case SUCCESS:
			scsi_finish_command(cmd);
			break;
		case NEEDS_RETRY:
			scsi_queue_insert(cmd, SCSI_MLQUEUE_EH_RETRY);
			break;
		case ADD_TO_MLQUEUE:
			scsi_queue_insert(cmd, SCSI_MLQUEUE_DEVICE_BUSY);
			break;
		default:
			scsi_eh_scmd_add(cmd);
			break;
	}
}