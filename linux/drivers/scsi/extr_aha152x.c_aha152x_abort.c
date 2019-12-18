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
struct scsi_cmnd {int /*<<< orphan*/ * host_scribble; TYPE_1__* device; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  commands; } ;
struct TYPE_3__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DO_LOCK (unsigned long) ; 
 int /*<<< orphan*/  DO_UNLOCK (unsigned long) ; 
 int FAILED ; 
 TYPE_2__* HOSTDATA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  ISSUE_SC ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PORTA ; 
 int /*<<< orphan*/  SETPORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct scsi_cmnd* remove_SC (int /*<<< orphan*/ *,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*) ; 

__attribute__((used)) static int aha152x_abort(struct scsi_cmnd *SCpnt)
{
	struct Scsi_Host *shpnt = SCpnt->device->host;
	struct scsi_cmnd *ptr;
	unsigned long flags;

	DO_LOCK(flags);

	ptr=remove_SC(&ISSUE_SC, SCpnt);

	if(ptr) {
		HOSTDATA(shpnt)->commands--;
		if (!HOSTDATA(shpnt)->commands)
			SETPORT(PORTA, 0);
		DO_UNLOCK(flags);

		kfree(SCpnt->host_scribble);
		SCpnt->host_scribble=NULL;

		return SUCCESS;
	}

	DO_UNLOCK(flags);

	/*
	 * FIXME:
	 * for current command: queue ABORT for message out and raise ATN
	 * for disconnected command: pseudo SC with ABORT message or ABORT on reselection?
	 *
	 */

	scmd_printk(KERN_ERR, SCpnt,
		    "cannot abort running or disconnected command\n");

	return FAILED;
}