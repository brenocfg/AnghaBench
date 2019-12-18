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
struct TYPE_3__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  opcode; int /*<<< orphan*/  id; } ;
union myrb_cmd_mbox {TYPE_1__ type3; } ;
struct myrb_rbld_progress {int dummy; } ;
struct myrb_cmdblk {union myrb_cmd_mbox mbox; } ;
struct myrb_hba {TYPE_2__* pdev; struct myrb_cmdblk mcmd_blk; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MYRB_CMD_GET_REBUILD_PROGRESS ; 
 int /*<<< orphan*/  MYRB_MCMD_TAG ; 
 unsigned short MYRB_STATUS_RBLD_NOT_CHECKED ; 
 struct myrb_rbld_progress* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct myrb_rbld_progress*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct myrb_rbld_progress*,struct myrb_rbld_progress*,int) ; 
 unsigned short myrb_exec_cmd (struct myrb_hba*,struct myrb_cmdblk*) ; 
 int /*<<< orphan*/  myrb_reset_cmd (struct myrb_cmdblk*) ; 

__attribute__((used)) static unsigned short myrb_get_rbld_progress(struct myrb_hba *cb,
		struct myrb_rbld_progress *rbld)
{
	struct myrb_cmdblk *cmd_blk = &cb->mcmd_blk;
	union myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	struct myrb_rbld_progress *rbld_buf;
	dma_addr_t rbld_addr;
	unsigned short status;

	rbld_buf = dma_alloc_coherent(&cb->pdev->dev,
				      sizeof(struct myrb_rbld_progress),
				      &rbld_addr, GFP_KERNEL);
	if (!rbld_buf)
		return MYRB_STATUS_RBLD_NOT_CHECKED;

	myrb_reset_cmd(cmd_blk);
	mbox->type3.id = MYRB_MCMD_TAG;
	mbox->type3.opcode = MYRB_CMD_GET_REBUILD_PROGRESS;
	mbox->type3.addr = rbld_addr;
	status = myrb_exec_cmd(cb, cmd_blk);
	if (rbld)
		memcpy(rbld, rbld_buf, sizeof(struct myrb_rbld_progress));
	dma_free_coherent(&cb->pdev->dev, sizeof(struct myrb_rbld_progress),
			  rbld_buf, rbld_addr);
	return status;
}