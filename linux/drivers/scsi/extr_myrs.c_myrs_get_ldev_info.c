#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
union myrs_sgl {TYPE_3__* sge; } ;
struct TYPE_9__ {unsigned short ldev_num; } ;
struct TYPE_8__ {int dma_ctrl_to_host; int no_autosense; } ;
struct TYPE_11__ {int dma_size; union myrs_sgl dma_addr; int /*<<< orphan*/  ioctl_opcode; TYPE_2__ ldev; TYPE_1__ control; int /*<<< orphan*/  opcode; int /*<<< orphan*/  id; } ;
union myrs_cmd_mbox {TYPE_4__ ldev_info; } ;
struct TYPE_13__ {scalar_t__ ldev_init_done; } ;
struct myrs_ldev_info {unsigned short ldev_num; unsigned long cfg_devsize; scalar_t__ dev_state; scalar_t__ cmds_failed; scalar_t__ deferred_write_errs; TYPE_6__ ldev_control; scalar_t__ bg_init_active; int /*<<< orphan*/  patrol_lba; scalar_t__ patrol_active; int /*<<< orphan*/  migration_lba; scalar_t__ migration_active; int /*<<< orphan*/  fg_init_lba; scalar_t__ fg_init_active; int /*<<< orphan*/  bg_init_lba; int /*<<< orphan*/  soft_errs; } ;
struct myrs_cmdblk {unsigned char status; union myrs_cmd_mbox mbox; } ;
struct myrs_hba {TYPE_7__* host; TYPE_5__* pdev; int /*<<< orphan*/  dcmd_mutex; struct myrs_cmdblk dcmd_blk; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_14__ {int /*<<< orphan*/  shost_gendev; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int sge_count; int /*<<< orphan*/  sge_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MYRS_CMD_OP_IOCTL ; 
 int /*<<< orphan*/  MYRS_DCMD_TAG ; 
 int /*<<< orphan*/  MYRS_IOCTL_GET_LDEV_INFO_VALID ; 
 unsigned char MYRS_STATUS_FAILED ; 
 unsigned char MYRS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned short) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,struct myrs_ldev_info*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct myrs_ldev_info*,struct myrs_ldev_info*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 char* myrs_devstate_name (scalar_t__) ; 
 int /*<<< orphan*/  myrs_exec_cmd (struct myrs_hba*,struct myrs_cmdblk*) ; 
 int /*<<< orphan*/  myrs_report_progress (struct myrs_hba*,unsigned short,char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  myrs_reset_cmd (struct myrs_cmdblk*) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,TYPE_7__*,char*,unsigned short,char const*,...) ; 

__attribute__((used)) static unsigned char myrs_get_ldev_info(struct myrs_hba *cs,
		unsigned short ldev_num, struct myrs_ldev_info *ldev_info)
{
	struct myrs_cmdblk *cmd_blk = &cs->dcmd_blk;
	union myrs_cmd_mbox *mbox = &cmd_blk->mbox;
	dma_addr_t ldev_info_addr;
	struct myrs_ldev_info ldev_info_orig;
	union myrs_sgl *sgl;
	unsigned char status;

	memcpy(&ldev_info_orig, ldev_info, sizeof(struct myrs_ldev_info));
	ldev_info_addr = dma_map_single(&cs->pdev->dev, ldev_info,
					sizeof(struct myrs_ldev_info),
					DMA_FROM_DEVICE);
	if (dma_mapping_error(&cs->pdev->dev, ldev_info_addr))
		return MYRS_STATUS_FAILED;

	mutex_lock(&cs->dcmd_mutex);
	myrs_reset_cmd(cmd_blk);
	mbox->ldev_info.id = MYRS_DCMD_TAG;
	mbox->ldev_info.opcode = MYRS_CMD_OP_IOCTL;
	mbox->ldev_info.control.dma_ctrl_to_host = true;
	mbox->ldev_info.control.no_autosense = true;
	mbox->ldev_info.dma_size = sizeof(struct myrs_ldev_info);
	mbox->ldev_info.ldev.ldev_num = ldev_num;
	mbox->ldev_info.ioctl_opcode = MYRS_IOCTL_GET_LDEV_INFO_VALID;
	sgl = &mbox->ldev_info.dma_addr;
	sgl->sge[0].sge_addr = ldev_info_addr;
	sgl->sge[0].sge_count = mbox->ldev_info.dma_size;
	dev_dbg(&cs->host->shost_gendev,
		"Sending GetLogicalDeviceInfoValid for ldev %d\n", ldev_num);
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	dma_unmap_single(&cs->pdev->dev, ldev_info_addr,
			 sizeof(struct myrs_ldev_info), DMA_FROM_DEVICE);
	if (status == MYRS_STATUS_SUCCESS) {
		unsigned short ldev_num = ldev_info->ldev_num;
		struct myrs_ldev_info *new = ldev_info;
		struct myrs_ldev_info *old = &ldev_info_orig;
		unsigned long ldev_size = new->cfg_devsize;

		if (new->dev_state != old->dev_state) {
			const char *name;

			name = myrs_devstate_name(new->dev_state);
			shost_printk(KERN_INFO, cs->host,
				     "Logical Drive %d is now %s\n",
				     ldev_num, name ? name : "Invalid");
		}
		if ((new->soft_errs != old->soft_errs) ||
		    (new->cmds_failed != old->cmds_failed) ||
		    (new->deferred_write_errs != old->deferred_write_errs))
			shost_printk(KERN_INFO, cs->host,
				     "Logical Drive %d Errors: Soft = %d, Failed = %d, Deferred Write = %d\n",
				     ldev_num, new->soft_errs,
				     new->cmds_failed,
				     new->deferred_write_errs);
		if (new->bg_init_active)
			myrs_report_progress(cs, ldev_num,
					     "Background Initialization",
					     new->bg_init_lba, ldev_size);
		else if (new->fg_init_active)
			myrs_report_progress(cs, ldev_num,
					     "Foreground Initialization",
					     new->fg_init_lba, ldev_size);
		else if (new->migration_active)
			myrs_report_progress(cs, ldev_num,
					     "Data Migration",
					     new->migration_lba, ldev_size);
		else if (new->patrol_active)
			myrs_report_progress(cs, ldev_num,
					     "Patrol Operation",
					     new->patrol_lba, ldev_size);
		if (old->bg_init_active && !new->bg_init_active)
			shost_printk(KERN_INFO, cs->host,
				     "Logical Drive %d: Background Initialization %s\n",
				     ldev_num,
				     (new->ldev_control.ldev_init_done ?
				      "Completed" : "Failed"));
	}
	return status;
}