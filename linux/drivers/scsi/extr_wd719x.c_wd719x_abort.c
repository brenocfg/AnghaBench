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
struct wd719x_scb {int /*<<< orphan*/  phys; } ;
struct wd719x {TYPE_3__* sh; TYPE_1__* pdev; } ;
struct scsi_cmnd {int /*<<< orphan*/  tag; TYPE_2__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  host; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_ABORT ; 
 int FAILED ; 
 int SUCCESS ; 
 int WD719X_CMD_ABORT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct wd719x_scb* scsi_cmd_priv (struct scsi_cmnd*) ; 
 struct wd719x* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int wd719x_direct_cmd (struct wd719x*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wd719x_finish_cmd (struct wd719x_scb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wd719x_abort(struct scsi_cmnd *cmd)
{
	int action, result;
	unsigned long flags;
	struct wd719x_scb *scb = scsi_cmd_priv(cmd);
	struct wd719x *wd = shost_priv(cmd->device->host);

	dev_info(&wd->pdev->dev, "abort command, tag: %x\n", cmd->tag);

	action = /*cmd->tag ? WD719X_CMD_ABORT_TAG : */WD719X_CMD_ABORT;

	spin_lock_irqsave(wd->sh->host_lock, flags);
	result = wd719x_direct_cmd(wd, action, cmd->device->id,
				   cmd->device->lun, cmd->tag, scb->phys, 0);
	wd719x_finish_cmd(scb, DID_ABORT);
	spin_unlock_irqrestore(wd->sh->host_lock, flags);
	if (result)
		return FAILED;

	return SUCCESS;
}