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
struct scsi_cmnd {void (* scsi_done ) (struct scsi_cmnd*) ;TYPE_2__* device; } ;
struct orc_scb {int dummy; } ;
struct orc_host {int dummy; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int SCSI_MLQUEUE_HOST_BUSY ; 
 scalar_t__ inia100_build_scb (struct orc_host*,struct orc_scb*,struct scsi_cmnd*) ; 
 struct orc_scb* orc_alloc_scb (struct orc_host*) ; 
 int /*<<< orphan*/  orc_exec_scb (struct orc_host*,struct orc_scb*) ; 
 int /*<<< orphan*/  orc_release_scb (struct orc_host*,struct orc_scb*) ; 

__attribute__((used)) static int inia100_queue_lck(struct scsi_cmnd * cmd, void (*done) (struct scsi_cmnd *))
{
	struct orc_scb *scb;
	struct orc_host *host;		/* Point to Host adapter control block */

	host = (struct orc_host *) cmd->device->host->hostdata;
	cmd->scsi_done = done;
	/* Get free SCSI control block  */
	if ((scb = orc_alloc_scb(host)) == NULL)
		return SCSI_MLQUEUE_HOST_BUSY;

	if (inia100_build_scb(host, scb, cmd)) {
		orc_release_scb(host, scb);
		return SCSI_MLQUEUE_HOST_BUSY;
	}
	orc_exec_scb(host, scb);	/* Start execute SCB            */
	return 0;
}