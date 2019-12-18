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
union myrs_sgl {TYPE_2__* sge; } ;
struct TYPE_7__ {int dma_ctrl_to_host; int no_autosense; } ;
struct TYPE_9__ {int dma_size; union myrs_sgl dma_addr; int /*<<< orphan*/  ioctl_opcode; scalar_t__ ctlr_num; TYPE_1__ control; int /*<<< orphan*/  opcode; int /*<<< orphan*/  id; } ;
union myrs_cmd_mbox {TYPE_3__ ctlr_info; } ;
struct myrs_cmdblk {unsigned char status; union myrs_cmd_mbox mbox; } ;
struct myrs_hba {int needs_update; TYPE_6__* ctlr_info; TYPE_5__* host; TYPE_4__* pdev; int /*<<< orphan*/  dcmd_mutex; struct myrs_cmdblk dcmd_blk; } ;
struct myrs_ctlr_info {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_12__ {unsigned short ldev_present; unsigned short ldev_critical; unsigned short ldev_offline; scalar_t__ bg_init_active; scalar_t__ ldev_init_active; scalar_t__ pdev_init_active; scalar_t__ cc_active; scalar_t__ rbld_active; scalar_t__ exp_active; } ;
struct TYPE_11__ {int /*<<< orphan*/  shost_gendev; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int sge_count; int /*<<< orphan*/  sge_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MYRS_CMD_OP_IOCTL ; 
 int /*<<< orphan*/  MYRS_DCMD_TAG ; 
 int /*<<< orphan*/  MYRS_IOCTL_GET_CTLR_INFO ; 
 unsigned char MYRS_STATUS_FAILED ; 
 unsigned char MYRS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  myrs_exec_cmd (struct myrs_hba*,struct myrs_cmdblk*) ; 
 int /*<<< orphan*/  myrs_reset_cmd (struct myrs_cmdblk*) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,TYPE_5__*,char*,unsigned short,unsigned short,unsigned short) ; 

__attribute__((used)) static unsigned char myrs_get_ctlr_info(struct myrs_hba *cs)
{
	struct myrs_cmdblk *cmd_blk = &cs->dcmd_blk;
	union myrs_cmd_mbox *mbox = &cmd_blk->mbox;
	dma_addr_t ctlr_info_addr;
	union myrs_sgl *sgl;
	unsigned char status;
	unsigned short ldev_present, ldev_critical, ldev_offline;

	ldev_present = cs->ctlr_info->ldev_present;
	ldev_critical = cs->ctlr_info->ldev_critical;
	ldev_offline = cs->ctlr_info->ldev_offline;

	ctlr_info_addr = dma_map_single(&cs->pdev->dev, cs->ctlr_info,
					sizeof(struct myrs_ctlr_info),
					DMA_FROM_DEVICE);
	if (dma_mapping_error(&cs->pdev->dev, ctlr_info_addr))
		return MYRS_STATUS_FAILED;

	mutex_lock(&cs->dcmd_mutex);
	myrs_reset_cmd(cmd_blk);
	mbox->ctlr_info.id = MYRS_DCMD_TAG;
	mbox->ctlr_info.opcode = MYRS_CMD_OP_IOCTL;
	mbox->ctlr_info.control.dma_ctrl_to_host = true;
	mbox->ctlr_info.control.no_autosense = true;
	mbox->ctlr_info.dma_size = sizeof(struct myrs_ctlr_info);
	mbox->ctlr_info.ctlr_num = 0;
	mbox->ctlr_info.ioctl_opcode = MYRS_IOCTL_GET_CTLR_INFO;
	sgl = &mbox->ctlr_info.dma_addr;
	sgl->sge[0].sge_addr = ctlr_info_addr;
	sgl->sge[0].sge_count = mbox->ctlr_info.dma_size;
	dev_dbg(&cs->host->shost_gendev, "Sending GetControllerInfo\n");
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	dma_unmap_single(&cs->pdev->dev, ctlr_info_addr,
			 sizeof(struct myrs_ctlr_info), DMA_FROM_DEVICE);
	if (status == MYRS_STATUS_SUCCESS) {
		if (cs->ctlr_info->bg_init_active +
		    cs->ctlr_info->ldev_init_active +
		    cs->ctlr_info->pdev_init_active +
		    cs->ctlr_info->cc_active +
		    cs->ctlr_info->rbld_active +
		    cs->ctlr_info->exp_active != 0)
			cs->needs_update = true;
		if (cs->ctlr_info->ldev_present != ldev_present ||
		    cs->ctlr_info->ldev_critical != ldev_critical ||
		    cs->ctlr_info->ldev_offline != ldev_offline)
			shost_printk(KERN_INFO, cs->host,
				     "Logical drive count changes (%d/%d/%d)\n",
				     cs->ctlr_info->ldev_critical,
				     cs->ctlr_info->ldev_offline,
				     cs->ctlr_info->ldev_present);
	}

	return status;
}