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
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;scalar_t__ request; int /*<<< orphan*/ * host_scribble; } ;
struct gdth_cmndinfo {int internal_command; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE2 (char*) ; 
 int /*<<< orphan*/  complete (struct completion*) ; 
 struct gdth_cmndinfo* gdth_cmnd_priv (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  gdth_put_cmndinfo (struct gdth_cmndinfo*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void gdth_scsi_done(struct scsi_cmnd *scp)
{
	struct gdth_cmndinfo *cmndinfo = gdth_cmnd_priv(scp);
	int internal_command = cmndinfo->internal_command;

	TRACE2(("gdth_scsi_done()\n"));

	gdth_put_cmndinfo(cmndinfo);
	scp->host_scribble = NULL;

	if (internal_command)
		complete((struct completion *)scp->request);
	else
		scp->scsi_done(scp);
}