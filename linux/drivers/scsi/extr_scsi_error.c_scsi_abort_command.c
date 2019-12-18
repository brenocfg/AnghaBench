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
struct scsi_device {struct Scsi_Host* host; } ;
struct scsi_cmnd {int eh_eflags; int /*<<< orphan*/  abort_work; struct scsi_device* device; } ;
struct Scsi_Host {int eh_deadline; int /*<<< orphan*/  tmf_work_q; int /*<<< orphan*/  host_lock; scalar_t__ last_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int FAILED ; 
 int HZ ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SCSI_EH_ABORT_SCHEDULED ; 
 int /*<<< orphan*/  SCSI_LOG_ERROR_RECOVERY (int,int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  delayed_work_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int
scsi_abort_command(struct scsi_cmnd *scmd)
{
	struct scsi_device *sdev = scmd->device;
	struct Scsi_Host *shost = sdev->host;
	unsigned long flags;

	if (scmd->eh_eflags & SCSI_EH_ABORT_SCHEDULED) {
		/*
		 * Retry after abort failed, escalate to next level.
		 */
		SCSI_LOG_ERROR_RECOVERY(3,
			scmd_printk(KERN_INFO, scmd,
				    "previous abort failed\n"));
		BUG_ON(delayed_work_pending(&scmd->abort_work));
		return FAILED;
	}

	spin_lock_irqsave(shost->host_lock, flags);
	if (shost->eh_deadline != -1 && !shost->last_reset)
		shost->last_reset = jiffies;
	spin_unlock_irqrestore(shost->host_lock, flags);

	scmd->eh_eflags |= SCSI_EH_ABORT_SCHEDULED;
	SCSI_LOG_ERROR_RECOVERY(3,
		scmd_printk(KERN_INFO, scmd, "abort scheduled\n"));
	queue_delayed_work(shost->tmf_work_q, &scmd->abort_work, HZ / 100);
	return SUCCESS;
}