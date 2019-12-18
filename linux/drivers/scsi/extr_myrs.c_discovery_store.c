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
struct TYPE_3__ {int dma_ctrl_to_host; int no_autosense; } ;
struct TYPE_4__ {int /*<<< orphan*/  ioctl_opcode; TYPE_1__ control; int /*<<< orphan*/  id; int /*<<< orphan*/  opcode; } ;
union myrs_cmd_mbox {TYPE_2__ common; } ;
struct myrs_cmdblk {unsigned char status; union myrs_cmd_mbox mbox; } ;
struct myrs_hba {int needs_update; int /*<<< orphan*/  monitor_work; int /*<<< orphan*/  work_q; scalar_t__ next_evseq; int /*<<< orphan*/  dcmd_mutex; struct myrs_cmdblk dcmd_blk; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MYRS_CMD_OP_IOCTL ; 
 int /*<<< orphan*/  MYRS_DCMD_TAG ; 
 int /*<<< orphan*/  MYRS_IOCTL_START_DISCOVERY ; 
 unsigned char MYRS_STATUS_SUCCESS ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  myrs_exec_cmd (struct myrs_hba*,struct myrs_cmdblk*) ; 
 int /*<<< orphan*/  myrs_reset_cmd (struct myrs_cmdblk*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,...) ; 
 struct myrs_hba* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static ssize_t discovery_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct myrs_hba *cs = shost_priv(shost);
	struct myrs_cmdblk *cmd_blk;
	union myrs_cmd_mbox *mbox;
	unsigned char status;

	mutex_lock(&cs->dcmd_mutex);
	cmd_blk = &cs->dcmd_blk;
	myrs_reset_cmd(cmd_blk);
	mbox = &cmd_blk->mbox;
	mbox->common.opcode = MYRS_CMD_OP_IOCTL;
	mbox->common.id = MYRS_DCMD_TAG;
	mbox->common.control.dma_ctrl_to_host = true;
	mbox->common.control.no_autosense = true;
	mbox->common.ioctl_opcode = MYRS_IOCTL_START_DISCOVERY;
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	if (status != MYRS_STATUS_SUCCESS) {
		shost_printk(KERN_INFO, shost,
			     "Discovery Not Initiated, status %02X\n",
			     status);
		return -EINVAL;
	}
	shost_printk(KERN_INFO, shost, "Discovery Initiated\n");
	cs->next_evseq = 0;
	cs->needs_update = true;
	queue_delayed_work(cs->work_q, &cs->monitor_work, 1);
	flush_delayed_work(&cs->monitor_work);
	shost_printk(KERN_INFO, shost, "Discovery Completed\n");

	return count;
}