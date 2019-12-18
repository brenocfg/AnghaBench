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
struct TYPE_4__ {int opcode; int /*<<< orphan*/  addr; int /*<<< orphan*/  target; int /*<<< orphan*/  channel; int /*<<< orphan*/  id; } ;
union myrb_cmd_mbox {TYPE_2__ type3D; } ;
struct scsi_device {int /*<<< orphan*/  id; int /*<<< orphan*/  channel; } ;
struct myrb_pdev_state {int dummy; } ;
struct myrb_cmdblk {union myrb_cmd_mbox mbox; } ;
struct myrb_hba {TYPE_1__* pdev; int /*<<< orphan*/  dcmd_mutex; struct myrb_cmdblk dcmd_blk; } ;
typedef  enum myrb_cmd_opcode { ____Placeholder_myrb_cmd_opcode } myrb_cmd_opcode ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ MYRB_CMD_GET_DEVICE_STATE_OLD ; 
 int /*<<< orphan*/  MYRB_DCMD_TAG ; 
 unsigned short MYRB_STATUS_SUBSYS_FAILED ; 
 unsigned short MYRB_STATUS_SUCCESS ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,struct myrb_pdev_state*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned short myrb_exec_cmd (struct myrb_hba*,struct myrb_cmdblk*) ; 
 int /*<<< orphan*/  myrb_reset_cmd (struct myrb_cmdblk*) ; 
 int /*<<< orphan*/  myrb_translate_devstate (struct myrb_pdev_state*) ; 

__attribute__((used)) static unsigned short myrb_exec_type3D(struct myrb_hba *cb,
		enum myrb_cmd_opcode op, struct scsi_device *sdev,
		struct myrb_pdev_state *pdev_info)
{
	struct myrb_cmdblk *cmd_blk = &cb->dcmd_blk;
	union myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	unsigned short status;
	dma_addr_t pdev_info_addr;

	pdev_info_addr = dma_map_single(&cb->pdev->dev, pdev_info,
					sizeof(struct myrb_pdev_state),
					DMA_FROM_DEVICE);
	if (dma_mapping_error(&cb->pdev->dev, pdev_info_addr))
		return MYRB_STATUS_SUBSYS_FAILED;

	mutex_lock(&cb->dcmd_mutex);
	myrb_reset_cmd(cmd_blk);
	mbox->type3D.id = MYRB_DCMD_TAG;
	mbox->type3D.opcode = op;
	mbox->type3D.channel = sdev->channel;
	mbox->type3D.target = sdev->id;
	mbox->type3D.addr = pdev_info_addr;
	status = myrb_exec_cmd(cb, cmd_blk);
	mutex_unlock(&cb->dcmd_mutex);
	dma_unmap_single(&cb->pdev->dev, pdev_info_addr,
			 sizeof(struct myrb_pdev_state), DMA_FROM_DEVICE);
	if (status == MYRB_STATUS_SUCCESS &&
	    mbox->type3D.opcode == MYRB_CMD_GET_DEVICE_STATE_OLD)
		myrb_translate_devstate(pdev_info);

	return status;
}