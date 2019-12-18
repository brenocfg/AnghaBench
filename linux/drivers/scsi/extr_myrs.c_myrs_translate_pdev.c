#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union myrs_sgl {TYPE_3__* sge; } ;
struct TYPE_6__ {unsigned char target; unsigned char channel; unsigned char lun; } ;
struct TYPE_5__ {int dma_ctrl_to_host; int no_autosense; } ;
struct TYPE_8__ {int dma_size; union myrs_sgl dma_addr; int /*<<< orphan*/  ioctl_opcode; TYPE_2__ pdev; TYPE_1__ control; int /*<<< orphan*/  opcode; } ;
union myrs_cmd_mbox {TYPE_4__ pdev_info; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct myrs_cmdblk {unsigned char status; union myrs_cmd_mbox mbox; } ;
struct myrs_hba {int /*<<< orphan*/  dcmd_mutex; struct myrs_cmdblk dcmd_blk; struct pci_dev* pdev; } ;
struct myrs_devmap {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_7__ {int sge_count; int /*<<< orphan*/  sge_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  MYRS_CMD_OP_IOCTL ; 
 int /*<<< orphan*/  MYRS_IOCTL_XLATE_PDEV_TO_LDEV ; 
 unsigned char MYRS_STATUS_FAILED ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,struct myrs_devmap*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct myrs_devmap*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  myrs_exec_cmd (struct myrs_hba*,struct myrs_cmdblk*) ; 

__attribute__((used)) static unsigned char myrs_translate_pdev(struct myrs_hba *cs,
		unsigned char channel, unsigned char target, unsigned char lun,
		struct myrs_devmap *devmap)
{
	struct pci_dev *pdev = cs->pdev;
	dma_addr_t devmap_addr;
	struct myrs_cmdblk *cmd_blk;
	union myrs_cmd_mbox *mbox;
	union myrs_sgl *sgl;
	unsigned char status;

	memset(devmap, 0x0, sizeof(struct myrs_devmap));
	devmap_addr = dma_map_single(&pdev->dev, devmap,
				     sizeof(struct myrs_devmap),
				     DMA_FROM_DEVICE);
	if (dma_mapping_error(&pdev->dev, devmap_addr))
		return MYRS_STATUS_FAILED;

	mutex_lock(&cs->dcmd_mutex);
	cmd_blk = &cs->dcmd_blk;
	mbox = &cmd_blk->mbox;
	mbox->pdev_info.opcode = MYRS_CMD_OP_IOCTL;
	mbox->pdev_info.control.dma_ctrl_to_host = true;
	mbox->pdev_info.control.no_autosense = true;
	mbox->pdev_info.dma_size = sizeof(struct myrs_devmap);
	mbox->pdev_info.pdev.target = target;
	mbox->pdev_info.pdev.channel = channel;
	mbox->pdev_info.pdev.lun = lun;
	mbox->pdev_info.ioctl_opcode = MYRS_IOCTL_XLATE_PDEV_TO_LDEV;
	sgl = &mbox->pdev_info.dma_addr;
	sgl->sge[0].sge_addr = devmap_addr;
	sgl->sge[0].sge_count = mbox->pdev_info.dma_size;

	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	dma_unmap_single(&pdev->dev, devmap_addr,
			 sizeof(struct myrs_devmap), DMA_FROM_DEVICE);
	return status;
}