#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int phase; } ;
struct scsi_cmnd {unsigned char cmd_len; int /*<<< orphan*/ * host_scribble; TYPE_2__ SCp; TYPE_1__* device; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  commands; } ;
struct TYPE_4__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 struct scsi_cmnd* CURRENT_SC ; 
 int /*<<< orphan*/  DECLARE_COMPLETION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISCONNECTED_SC ; 
 int /*<<< orphan*/  DO_LOCK (unsigned long) ; 
 int /*<<< orphan*/  DO_UNLOCK (unsigned long) ; 
 int FAILED ; 
 TYPE_3__* HOSTDATA (struct Scsi_Host*) ; 
 int HZ ; 
 int /*<<< orphan*/  ISSUE_SC ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PORTA ; 
 int /*<<< orphan*/  SETPORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  aha152x_internal_queue (struct scsi_cmnd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_SC (int /*<<< orphan*/ *,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * remove_SC (int /*<<< orphan*/ *,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  reset_done ; 
 int resetted ; 
 int /*<<< orphan*/  resetting ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int aha152x_device_reset(struct scsi_cmnd * SCpnt)
{
	struct Scsi_Host *shpnt = SCpnt->device->host;
	DECLARE_COMPLETION(done);
	int ret, issued, disconnected;
	unsigned char old_cmd_len = SCpnt->cmd_len;
	unsigned long flags;
	unsigned long timeleft;

	if(CURRENT_SC==SCpnt) {
		scmd_printk(KERN_ERR, SCpnt, "cannot reset current device\n");
		return FAILED;
	}

	DO_LOCK(flags);
	issued       = remove_SC(&ISSUE_SC, SCpnt) == NULL;
	disconnected = issued && remove_SC(&DISCONNECTED_SC, SCpnt);
	DO_UNLOCK(flags);

	SCpnt->cmd_len         = 0;

	aha152x_internal_queue(SCpnt, &done, resetting, reset_done);

	timeleft = wait_for_completion_timeout(&done, 100*HZ);
	if (!timeleft) {
		/* remove command from issue queue */
		DO_LOCK(flags);
		remove_SC(&ISSUE_SC, SCpnt);
		DO_UNLOCK(flags);
	}

	SCpnt->cmd_len         = old_cmd_len;

	DO_LOCK(flags);

	if(SCpnt->SCp.phase & resetted) {
		HOSTDATA(shpnt)->commands--;
		if (!HOSTDATA(shpnt)->commands)
			SETPORT(PORTA, 0);
		kfree(SCpnt->host_scribble);
		SCpnt->host_scribble=NULL;

		ret = SUCCESS;
	} else {
		/* requeue */
		if(!issued) {
			append_SC(&ISSUE_SC, SCpnt);
		} else if(disconnected) {
			append_SC(&DISCONNECTED_SC, SCpnt);
		}

		ret = FAILED;
	}

	DO_UNLOCK(flags);
	return ret;
}