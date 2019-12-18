#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
union myrs_sgl {TYPE_3__* sge; } ;
struct TYPE_8__ {unsigned char lun; unsigned char target; unsigned char channel; } ;
struct TYPE_7__ {int dma_ctrl_to_host; int no_autosense; } ;
struct TYPE_10__ {int dma_size; union myrs_sgl dma_addr; int /*<<< orphan*/  ioctl_opcode; TYPE_2__ pdev; TYPE_1__ control; int /*<<< orphan*/  id; int /*<<< orphan*/  opcode; } ;
union myrs_cmd_mbox {TYPE_4__ pdev_info; } ;
struct myrs_pdev_info {int dummy; } ;
struct myrs_cmdblk {unsigned char status; union myrs_cmd_mbox mbox; } ;
struct myrs_hba {TYPE_6__* pdev; int /*<<< orphan*/  dcmd_mutex; TYPE_5__* host; struct myrs_cmdblk dcmd_blk; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  shost_gendev; } ;
struct TYPE_9__ {int sge_count; int /*<<< orphan*/  sge_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  MYRS_CMD_OP_IOCTL ; 
 int /*<<< orphan*/  MYRS_DCMD_TAG ; 
 int /*<<< orphan*/  MYRS_IOCTL_GET_PDEV_INFO_VALID ; 
 unsigned char MYRS_STATUS_FAILED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,struct myrs_pdev_info*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  myrs_exec_cmd (struct myrs_hba*,struct myrs_cmdblk*) ; 
 int /*<<< orphan*/  myrs_reset_cmd (struct myrs_cmdblk*) ; 

__attribute__((used)) static unsigned char myrs_get_pdev_info(struct myrs_hba *cs,
		unsigned char channel, unsigned char target, unsigned char lun,
		struct myrs_pdev_info *pdev_info)
{
	struct myrs_cmdblk *cmd_blk = &cs->dcmd_blk;
	union myrs_cmd_mbox *mbox = &cmd_blk->mbox;
	dma_addr_t pdev_info_addr;
	union myrs_sgl *sgl;
	unsigned char status;

	pdev_info_addr = dma_map_single(&cs->pdev->dev, pdev_info,
					sizeof(struct myrs_pdev_info),
					DMA_FROM_DEVICE);
	if (dma_mapping_error(&cs->pdev->dev, pdev_info_addr))
		return MYRS_STATUS_FAILED;

	mutex_lock(&cs->dcmd_mutex);
	myrs_reset_cmd(cmd_blk);
	mbox->pdev_info.opcode = MYRS_CMD_OP_IOCTL;
	mbox->pdev_info.id = MYRS_DCMD_TAG;
	mbox->pdev_info.control.dma_ctrl_to_host = true;
	mbox->pdev_info.control.no_autosense = true;
	mbox->pdev_info.dma_size = sizeof(struct myrs_pdev_info);
	mbox->pdev_info.pdev.lun = lun;
	mbox->pdev_info.pdev.target = target;
	mbox->pdev_info.pdev.channel = channel;
	mbox->pdev_info.ioctl_opcode = MYRS_IOCTL_GET_PDEV_INFO_VALID;
	sgl = &mbox->pdev_info.dma_addr;
	sgl->sge[0].sge_addr = pdev_info_addr;
	sgl->sge[0].sge_count = mbox->pdev_info.dma_size;
	dev_dbg(&cs->host->shost_gendev,
		"Sending GetPhysicalDeviceInfoValid for pdev %d:%d:%d\n",
		channel, target, lun);
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	dma_unmap_single(&cs->pdev->dev, pdev_info_addr,
			 sizeof(struct myrs_pdev_info), DMA_FROM_DEVICE);
	return status;
}