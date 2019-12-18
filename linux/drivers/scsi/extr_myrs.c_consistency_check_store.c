#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned short ldev_num; } ;
struct TYPE_10__ {int restore_consistency; int initialized_area_only; int /*<<< orphan*/  ioctl_opcode; TYPE_4__ ldev; } ;
struct TYPE_7__ {int dma_ctrl_to_host; int no_autosense; } ;
struct TYPE_8__ {TYPE_2__ control; int /*<<< orphan*/  id; int /*<<< orphan*/  opcode; } ;
union myrs_cmd_mbox {TYPE_5__ cc; TYPE_3__ common; } ;
struct scsi_device {scalar_t__ channel; struct myrs_ldev_info* hostdata; int /*<<< orphan*/  host; } ;
struct myrs_ldev_info {unsigned short ldev_num; scalar_t__ cc_active; } ;
struct myrs_cmdblk {unsigned char status; union myrs_cmd_mbox mbox; } ;
struct myrs_hba {int /*<<< orphan*/  dcmd_mutex; struct myrs_cmdblk dcmd_blk; TYPE_1__* ctlr_info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_6__ {scalar_t__ physchan_present; } ;

/* Variables and functions */
 int EALREADY ; 
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MYRS_CMD_OP_IOCTL ; 
 int /*<<< orphan*/  MYRS_DCMD_TAG ; 
 int /*<<< orphan*/  MYRS_IOCTL_CC_START ; 
 int /*<<< orphan*/  MYRS_IOCTL_CC_STOP ; 
 unsigned char MYRS_STATUS_SUCCESS ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  myrs_exec_cmd (struct myrs_hba*,struct myrs_cmdblk*) ; 
 unsigned char myrs_get_ldev_info (struct myrs_hba*,unsigned short,struct myrs_ldev_info*) ; 
 int /*<<< orphan*/  myrs_reset_cmd (struct myrs_cmdblk*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,...) ; 
 struct myrs_hba* shost_priv (int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t consistency_check_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct myrs_hba *cs = shost_priv(sdev->host);
	struct myrs_ldev_info *ldev_info;
	struct myrs_cmdblk *cmd_blk;
	union myrs_cmd_mbox *mbox;
	unsigned short ldev_num;
	unsigned char status;
	int check, ret;

	if (sdev->channel < cs->ctlr_info->physchan_present)
		return -EINVAL;

	ldev_info = sdev->hostdata;
	if (!ldev_info)
		return -ENXIO;
	ldev_num = ldev_info->ldev_num;

	ret = kstrtoint(buf, 0, &check);
	if (ret)
		return ret;

	status = myrs_get_ldev_info(cs, ldev_num, ldev_info);
	if (status != MYRS_STATUS_SUCCESS) {
		sdev_printk(KERN_INFO, sdev,
			    "Failed to get device information, status 0x%02x\n",
			    status);
		return -EIO;
	}
	if (check && ldev_info->cc_active) {
		sdev_printk(KERN_INFO, sdev,
			    "Consistency Check Not Initiated; "
			    "already in progress\n");
		return -EALREADY;
	}
	if (!check && !ldev_info->cc_active) {
		sdev_printk(KERN_INFO, sdev,
			    "Consistency Check Not Cancelled; "
			    "check not in progress\n");
		return count;
	}

	mutex_lock(&cs->dcmd_mutex);
	cmd_blk = &cs->dcmd_blk;
	myrs_reset_cmd(cmd_blk);
	mbox = &cmd_blk->mbox;
	mbox->common.opcode = MYRS_CMD_OP_IOCTL;
	mbox->common.id = MYRS_DCMD_TAG;
	mbox->common.control.dma_ctrl_to_host = true;
	mbox->common.control.no_autosense = true;
	if (check) {
		mbox->cc.ldev.ldev_num = ldev_num;
		mbox->cc.ioctl_opcode = MYRS_IOCTL_CC_START;
		mbox->cc.restore_consistency = true;
		mbox->cc.initialized_area_only = false;
	} else {
		mbox->cc.ldev.ldev_num = ldev_num;
		mbox->cc.ioctl_opcode = MYRS_IOCTL_CC_STOP;
	}
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	if (status != MYRS_STATUS_SUCCESS) {
		sdev_printk(KERN_INFO, sdev,
			    "Consistency Check Not %s, status 0x%02x\n",
			    check ? "Initiated" : "Cancelled", status);
		ret = -EIO;
	} else {
		sdev_printk(KERN_INFO, sdev, "Consistency Check %s\n",
			    check ? "Initiated" : "Cancelled");
		ret = count;
	}

	return ret;
}