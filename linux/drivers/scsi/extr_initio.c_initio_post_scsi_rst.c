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
struct target_control {int flags; int /*<<< orphan*/  sconfig0; scalar_t__ js_period; } ;
struct scsi_ctrl_blk {int /*<<< orphan*/  hastat; } ;
struct initio_host {int max_tar; struct target_control* targets; scalar_t__* act_tags; int /*<<< orphan*/  sconf1; scalar_t__ flags; int /*<<< orphan*/ * active_tc; int /*<<< orphan*/ * active; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_BAD_PHAS ; 
 int TCF_BUSY ; 
 int TCF_SYNC_DONE ; 
 int TCF_WDTR_DONE ; 
 int /*<<< orphan*/  initio_append_done_scb (struct initio_host*,struct scsi_ctrl_blk*) ; 
 struct scsi_ctrl_blk* initio_pop_busy_scb (struct initio_host*) ; 

__attribute__((used)) static int initio_post_scsi_rst(struct initio_host * host)
{
	struct scsi_ctrl_blk *scb;
	struct target_control *active_tc;
	int i;

	host->active = NULL;
	host->active_tc = NULL;
	host->flags = 0;

	while ((scb = initio_pop_busy_scb(host)) != NULL) {
		scb->hastat = HOST_BAD_PHAS;
		initio_append_done_scb(host, scb);
	}
	/* clear sync done flag         */
	active_tc = &host->targets[0];
	for (i = 0; i < host->max_tar; active_tc++, i++) {
		active_tc->flags &= ~(TCF_SYNC_DONE | TCF_WDTR_DONE);
		/* Initialize the sync. xfer register values to an asyn xfer */
		active_tc->js_period = 0;
		active_tc->sconfig0 = host->sconf1;
		host->act_tags[0] = 0;	/* 07/22/98 */
		host->targets[i].flags &= ~TCF_BUSY;	/* 07/22/98 */
	}			/* for */

	return -1;
}