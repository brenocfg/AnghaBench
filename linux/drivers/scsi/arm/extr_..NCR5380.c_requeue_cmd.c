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
struct scsi_cmnd {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct NCR5380_hostdata {int /*<<< orphan*/  unissued; struct scsi_cmnd* sensing; int /*<<< orphan*/  autosense; int /*<<< orphan*/  ses; } ;
struct NCR5380_cmd {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct NCR5380_cmd* scsi_cmd_priv (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_eh_restore_cmnd (struct scsi_cmnd*,int /*<<< orphan*/ *) ; 
 struct NCR5380_hostdata* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static void requeue_cmd(struct Scsi_Host *instance, struct scsi_cmnd *cmd)
{
	struct NCR5380_hostdata *hostdata = shost_priv(instance);
	struct NCR5380_cmd *ncmd = scsi_cmd_priv(cmd);

	if (hostdata->sensing == cmd) {
		scsi_eh_restore_cmnd(cmd, &hostdata->ses);
		list_add(&ncmd->list, &hostdata->autosense);
		hostdata->sensing = NULL;
	} else
		list_add(&ncmd->list, &hostdata->unissued);
}