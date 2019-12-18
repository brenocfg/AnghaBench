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
typedef  int u8 ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct mailbox {scalar_t__ status; int /*<<< orphan*/  ccbptr; } ;
struct ccb {int op; int idlun; scalar_t__ commlinkid; scalar_t__* linkptr; } ;
struct aha1542_hostdata {int aha1542_last_mbo_used; scalar_t__ ccb_handle; struct scsi_cmnd** int_cmds; struct ccb* ccb; struct mailbox* mb; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; int /*<<< orphan*/  io_port; } ;
struct TYPE_2__ {int id; int lun; struct Scsi_Host* host; } ;

/* Variables and functions */
 int AHA1542_MAILBOXES ; 
 int /*<<< orphan*/  CMD_START_SCSI ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int SUCCESS ; 
 int /*<<< orphan*/  aha1542_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  any2scsi (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ccb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*) ; 
 struct aha1542_hostdata* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int aha1542_dev_reset(struct scsi_cmnd *cmd)
{
	struct Scsi_Host *sh = cmd->device->host;
	struct aha1542_hostdata *aha1542 = shost_priv(sh);
	unsigned long flags;
	struct mailbox *mb = aha1542->mb;
	u8 target = cmd->device->id;
	u8 lun = cmd->device->lun;
	int mbo;
	struct ccb *ccb = aha1542->ccb;

	spin_lock_irqsave(sh->host_lock, flags);
	mbo = aha1542->aha1542_last_mbo_used + 1;
	if (mbo >= AHA1542_MAILBOXES)
		mbo = 0;

	do {
		if (mb[mbo].status == 0 && aha1542->int_cmds[mbo] == NULL)
			break;
		mbo++;
		if (mbo >= AHA1542_MAILBOXES)
			mbo = 0;
	} while (mbo != aha1542->aha1542_last_mbo_used);

	if (mb[mbo].status || aha1542->int_cmds[mbo])
		panic("Unable to find empty mailbox for aha1542.\n");

	aha1542->int_cmds[mbo] = cmd;	/* This will effectively
					   prevent someone else from
					   screwing with this cdb. */

	aha1542->aha1542_last_mbo_used = mbo;

	/* This gets trashed for some reason */
	any2scsi(mb[mbo].ccbptr, aha1542->ccb_handle + mbo * sizeof(*ccb));

	memset(&ccb[mbo], 0, sizeof(struct ccb));

	ccb[mbo].op = 0x81;	/* BUS DEVICE RESET */

	ccb[mbo].idlun = (target & 7) << 5 | (lun & 7);		/*SCSI Target Id */

	ccb[mbo].linkptr[0] = ccb[mbo].linkptr[1] = ccb[mbo].linkptr[2] = 0;
	ccb[mbo].commlinkid = 0;

	/* 
	 * Now tell the 1542 to flush all pending commands for this 
	 * target 
	 */
	aha1542_outb(sh->io_port, CMD_START_SCSI);
	spin_unlock_irqrestore(sh->host_lock, flags);

	scmd_printk(KERN_WARNING, cmd,
		"Trying device reset for target\n");

	return SUCCESS;
}