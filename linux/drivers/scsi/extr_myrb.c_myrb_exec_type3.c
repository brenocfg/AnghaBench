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
struct TYPE_2__ {int opcode; int /*<<< orphan*/  addr; int /*<<< orphan*/  id; } ;
union myrb_cmd_mbox {TYPE_1__ type3; } ;
struct myrb_cmdblk {union myrb_cmd_mbox mbox; } ;
struct myrb_hba {int /*<<< orphan*/  dcmd_mutex; struct myrb_cmdblk dcmd_blk; } ;
typedef  enum myrb_cmd_opcode { ____Placeholder_myrb_cmd_opcode } myrb_cmd_opcode ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MYRB_DCMD_TAG ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned short myrb_exec_cmd (struct myrb_hba*,struct myrb_cmdblk*) ; 
 int /*<<< orphan*/  myrb_reset_cmd (struct myrb_cmdblk*) ; 

__attribute__((used)) static unsigned short myrb_exec_type3(struct myrb_hba *cb,
		enum myrb_cmd_opcode op, dma_addr_t addr)
{
	struct myrb_cmdblk *cmd_blk = &cb->dcmd_blk;
	union myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	unsigned short status;

	mutex_lock(&cb->dcmd_mutex);
	myrb_reset_cmd(cmd_blk);
	mbox->type3.id = MYRB_DCMD_TAG;
	mbox->type3.opcode = op;
	mbox->type3.addr = addr;
	status = myrb_exec_cmd(cb, cmd_blk);
	mutex_unlock(&cb->dcmd_mutex);
	return status;
}