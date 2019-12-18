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
struct TYPE_8__ {unsigned short ldev_num; } ;
struct TYPE_9__ {int state; TYPE_3__ ldev; int /*<<< orphan*/  ioctl_opcode; } ;
struct TYPE_6__ {int dma_ctrl_to_host; int no_autosense; } ;
struct TYPE_7__ {TYPE_1__ control; int /*<<< orphan*/  id; int /*<<< orphan*/  opcode; } ;
union myrs_cmd_mbox {TYPE_4__ set_devstate; TYPE_2__ common; } ;
struct scsi_device {scalar_t__ channel; struct myrs_pdev_info* hostdata; int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  host; } ;
struct myrs_pdev_info {int dev_state; unsigned short ldev_num; int /*<<< orphan*/  rsvd13; } ;
struct myrs_ldev_info {int dev_state; unsigned short ldev_num; int /*<<< orphan*/  rsvd13; } ;
struct myrs_cmdblk {unsigned char status; union myrs_cmd_mbox mbox; } ;
struct myrs_hba {TYPE_5__* ctlr_info; int /*<<< orphan*/  dcmd_mutex; struct myrs_cmdblk dcmd_blk; } ;
struct myrs_devmap {unsigned short ldev_num; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  enum myrs_devstate { ____Placeholder_myrs_devstate } myrs_devstate ;
struct TYPE_10__ {scalar_t__ physchan_present; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENXIO ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MYRS_CMD_OP_IOCTL ; 
 int /*<<< orphan*/  MYRS_DCMD_TAG ; 
 int MYRS_DEVICE_OFFLINE ; 
 int MYRS_DEVICE_ONLINE ; 
 int MYRS_DEVICE_STANDBY ; 
 int /*<<< orphan*/  MYRS_IOCTL_SET_DEVICE_STATE ; 
 unsigned char MYRS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  myrs_devstate_name (int) ; 
 int /*<<< orphan*/  myrs_exec_cmd (struct myrs_hba*,struct myrs_cmdblk*) ; 
 int /*<<< orphan*/  myrs_reset_cmd (struct myrs_cmdblk*) ; 
 unsigned char myrs_translate_pdev (struct myrs_hba*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct myrs_devmap*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,...) ; 
 struct myrs_hba* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t raid_state_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct myrs_hba *cs = shost_priv(sdev->host);
	struct myrs_cmdblk *cmd_blk;
	union myrs_cmd_mbox *mbox;
	enum myrs_devstate new_state;
	unsigned short ldev_num;
	unsigned char status;

	if (!strncmp(buf, "offline", 7) ||
	    !strncmp(buf, "kill", 4))
		new_state = MYRS_DEVICE_OFFLINE;
	else if (!strncmp(buf, "online", 6))
		new_state = MYRS_DEVICE_ONLINE;
	else if (!strncmp(buf, "standby", 7))
		new_state = MYRS_DEVICE_STANDBY;
	else
		return -EINVAL;

	if (sdev->channel < cs->ctlr_info->physchan_present) {
		struct myrs_pdev_info *pdev_info = sdev->hostdata;
		struct myrs_devmap *pdev_devmap =
			(struct myrs_devmap *)&pdev_info->rsvd13;

		if (pdev_info->dev_state == new_state) {
			sdev_printk(KERN_INFO, sdev,
				    "Device already in %s\n",
				    myrs_devstate_name(new_state));
			return count;
		}
		status = myrs_translate_pdev(cs, sdev->channel, sdev->id,
					     sdev->lun, pdev_devmap);
		if (status != MYRS_STATUS_SUCCESS)
			return -ENXIO;
		ldev_num = pdev_devmap->ldev_num;
	} else {
		struct myrs_ldev_info *ldev_info = sdev->hostdata;

		if (ldev_info->dev_state == new_state) {
			sdev_printk(KERN_INFO, sdev,
				    "Device already in %s\n",
				    myrs_devstate_name(new_state));
			return count;
		}
		ldev_num = ldev_info->ldev_num;
	}
	mutex_lock(&cs->dcmd_mutex);
	cmd_blk = &cs->dcmd_blk;
	myrs_reset_cmd(cmd_blk);
	mbox = &cmd_blk->mbox;
	mbox->common.opcode = MYRS_CMD_OP_IOCTL;
	mbox->common.id = MYRS_DCMD_TAG;
	mbox->common.control.dma_ctrl_to_host = true;
	mbox->common.control.no_autosense = true;
	mbox->set_devstate.ioctl_opcode = MYRS_IOCTL_SET_DEVICE_STATE;
	mbox->set_devstate.state = new_state;
	mbox->set_devstate.ldev.ldev_num = ldev_num;
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	if (status == MYRS_STATUS_SUCCESS) {
		if (sdev->channel < cs->ctlr_info->physchan_present) {
			struct myrs_pdev_info *pdev_info = sdev->hostdata;

			pdev_info->dev_state = new_state;
		} else {
			struct myrs_ldev_info *ldev_info = sdev->hostdata;

			ldev_info->dev_state = new_state;
		}
		sdev_printk(KERN_INFO, sdev,
			    "Set device state to %s\n",
			    myrs_devstate_name(new_state));
		return count;
	}
	sdev_printk(KERN_INFO, sdev,
		    "Failed to set device state to %s, status 0x%02x\n",
		    myrs_devstate_name(new_state), status);
	return -EINVAL;
}