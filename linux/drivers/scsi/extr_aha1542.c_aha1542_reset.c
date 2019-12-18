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
typedef  int u8 ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct aha1542_hostdata {TYPE_2__* mb; struct scsi_cmnd** int_cmds; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; int /*<<< orphan*/  host_no; int /*<<< orphan*/  io_port; } ;
struct TYPE_4__ {scalar_t__ status; } ;
struct TYPE_3__ {scalar_t__ soft_reset; struct Scsi_Host* host; } ;

/* Variables and functions */
 int AHA1542_MAILBOXES ; 
 int CDF ; 
 int /*<<< orphan*/  CONTROL (int /*<<< orphan*/ ) ; 
 int DF ; 
 int DIAGF ; 
 int FAILED ; 
 int HRST ; 
 int /*<<< orphan*/  IDLE ; 
 int INVDCMD ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  STATMASK ; 
 int /*<<< orphan*/  STATUS (int /*<<< orphan*/ ) ; 
 int STST ; 
 int SUCCESS ; 
 int /*<<< orphan*/  aha1542_free_cmd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_mailboxes (struct Scsi_Host*) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,int /*<<< orphan*/ ) ; 
 struct aha1542_hostdata* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aha1542_reset(struct scsi_cmnd *cmd, u8 reset_cmd)
{
	struct Scsi_Host *sh = cmd->device->host;
	struct aha1542_hostdata *aha1542 = shost_priv(sh);
	unsigned long flags;
	int i;

	spin_lock_irqsave(sh->host_lock, flags);
	/* 
	 * This does a scsi reset for all devices on the bus.
	 * In principle, we could also reset the 1542 - should
	 * we do this?  Try this first, and we can add that later
	 * if it turns out to be useful.
	 */
	outb(reset_cmd, CONTROL(cmd->device->host->io_port));

	if (!wait_mask(STATUS(cmd->device->host->io_port),
	     STATMASK, IDLE, STST | DIAGF | INVDCMD | DF | CDF, 0)) {
		spin_unlock_irqrestore(sh->host_lock, flags);
		return FAILED;
	}

	/*
	 * We need to do this too before the 1542 can interact with
	 * us again after host reset.
	 */
	if (reset_cmd & HRST)
		setup_mailboxes(cmd->device->host);

	/*
	 * Now try to pick up the pieces.  For all pending commands,
	 * free any internal data structures, and basically clear things
	 * out.  We do not try and restart any commands or anything - 
	 * the strategy handler takes care of that crap.
	 */
	shost_printk(KERN_WARNING, cmd->device->host, "Sent BUS RESET to scsi host %d\n", cmd->device->host->host_no);

	for (i = 0; i < AHA1542_MAILBOXES; i++) {
		if (aha1542->int_cmds[i] != NULL) {
			struct scsi_cmnd *tmp_cmd;
			tmp_cmd = aha1542->int_cmds[i];

			if (tmp_cmd->device->soft_reset) {
				/*
				 * If this device implements the soft reset option,
				 * then it is still holding onto the command, and
				 * may yet complete it.  In this case, we don't
				 * flush the data.
				 */
				continue;
			}
			aha1542_free_cmd(tmp_cmd);
			aha1542->int_cmds[i] = NULL;
			aha1542->mb[i].status = 0;
		}
	}

	spin_unlock_irqrestore(sh->host_lock, flags);
	return SUCCESS;
}