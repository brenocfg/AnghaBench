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
struct TYPE_2__ {int state; int /*<<< orphan*/  target; int /*<<< orphan*/  channel; int /*<<< orphan*/  id; int /*<<< orphan*/  opcode; } ;
union myrb_cmd_mbox {TYPE_1__ type3D; } ;
struct scsi_device {int /*<<< orphan*/  id; int /*<<< orphan*/  channel; } ;
struct myrb_cmdblk {union myrb_cmd_mbox mbox; } ;
struct myrb_hba {int /*<<< orphan*/  dcmd_mutex; struct myrb_cmdblk dcmd_blk; } ;
typedef  enum myrb_devstate { ____Placeholder_myrb_devstate } myrb_devstate ;

/* Variables and functions */
 int /*<<< orphan*/  MYRB_CMD_START_DEVICE ; 
 int /*<<< orphan*/  MYRB_DCMD_TAG ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned short myrb_exec_cmd (struct myrb_hba*,struct myrb_cmdblk*) ; 

__attribute__((used)) static unsigned short myrb_set_pdev_state(struct myrb_hba *cb,
		struct scsi_device *sdev, enum myrb_devstate state)
{
	struct myrb_cmdblk *cmd_blk = &cb->dcmd_blk;
	union myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	unsigned short status;

	mutex_lock(&cb->dcmd_mutex);
	mbox->type3D.opcode = MYRB_CMD_START_DEVICE;
	mbox->type3D.id = MYRB_DCMD_TAG;
	mbox->type3D.channel = sdev->channel;
	mbox->type3D.target = sdev->id;
	mbox->type3D.state = state & 0x1F;
	status = myrb_exec_cmd(cb, cmd_blk);
	mutex_unlock(&cb->dcmd_mutex);

	return status;
}