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
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  result; } ;
struct Scsi_Host {int dummy; } ;
struct NCR5380_hostdata {struct scsi_cmnd* sensing; int /*<<< orphan*/  ses; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_SENSE ; 
 scalar_t__ GOOD ; 
 int /*<<< orphan*/  NDEBUG_QUEUES ; 
 int /*<<< orphan*/  dsprintk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_eh_restore_cmnd (struct scsi_cmnd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_driver_byte (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 struct NCR5380_hostdata* shost_priv (struct Scsi_Host*) ; 
 scalar_t__ status_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void complete_cmd(struct Scsi_Host *instance,
                         struct scsi_cmnd *cmd)
{
	struct NCR5380_hostdata *hostdata = shost_priv(instance);

	dsprintk(NDEBUG_QUEUES, instance, "complete_cmd: cmd %p\n", cmd);

	if (hostdata->sensing == cmd) {
		/* Autosense processing ends here */
		if (status_byte(cmd->result) != GOOD) {
			scsi_eh_restore_cmnd(cmd, &hostdata->ses);
		} else {
			scsi_eh_restore_cmnd(cmd, &hostdata->ses);
			set_driver_byte(cmd, DRIVER_SENSE);
		}
		hostdata->sensing = NULL;
	}

	cmd->scsi_done(cmd);
}