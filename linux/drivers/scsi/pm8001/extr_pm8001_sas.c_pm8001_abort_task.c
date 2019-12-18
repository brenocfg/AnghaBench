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
typedef  int u32 ;
struct scsi_lun {int /*<<< orphan*/  scsi_lun; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct sas_task_slow {int /*<<< orphan*/  completion; } ;
struct sas_task {int task_state_flags; int task_proto; int /*<<< orphan*/  task_state_lock; struct sas_task_slow* slow_task; struct scsi_cmnd* uldd_task; struct domain_device* dev; int /*<<< orphan*/  lldd_task; } ;
struct pm8001_tmf_task {int tag_of_task_to_be_managed; int /*<<< orphan*/  tmf; } ;
struct pm8001_phy {int reset_success; scalar_t__ port_reset_status; int /*<<< orphan*/ * reset_completion; int /*<<< orphan*/ * enable_completion; } ;
struct pm8001_hba_info {scalar_t__ chip_id; struct pm8001_phy* phy; } ;
struct pm8001_device {int attached_phy; int /*<<< orphan*/  sas_device; int /*<<< orphan*/ * setds_completion; } ;
struct domain_device {struct pm8001_device* lldd_dev; } ;
struct TYPE_4__ {int (* phy_ctl_req ) (struct pm8001_hba_info*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_dev_state_req ) (struct pm8001_hba_info*,struct pm8001_device*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  PHY_HARD_RESET ; 
 TYPE_2__* PM8001_CHIP_DISP ; 
 int /*<<< orphan*/  PM8001_MSG_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int PM8001_TASK_TIMEOUT ; 
 int SAS_PROTOCOL_SATA ; 
 int SAS_PROTOCOL_SMP ; 
 int SAS_PROTOCOL_SSP ; 
 int SAS_PROTOCOL_STP ; 
 int SAS_TASK_STATE_ABORTED ; 
 int SAS_TASK_STATE_DONE ; 
 int /*<<< orphan*/  TMF_ABORT_TASK ; 
 int TMF_RESP_FUNC_COMPLETE ; 
 int TMF_RESP_FUNC_FAILED ; 
 scalar_t__ chip_8006 ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  completion_reset ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,struct scsi_lun*) ; 
 int /*<<< orphan*/  pm8001_dev_gone_notify (struct domain_device*) ; 
 int pm8001_exec_internal_task_abort (struct pm8001_hba_info*,struct pm8001_device*,int /*<<< orphan*/ ,int,int) ; 
 struct pm8001_hba_info* pm8001_find_ha_by_dev (struct domain_device*) ; 
 int pm8001_find_tag (struct sas_task*,int*) ; 
 int pm8001_issue_ssp_tmf (struct domain_device*,int /*<<< orphan*/ ,struct pm8001_tmf_task*) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct pm8001_hba_info*,struct pm8001_device*,int) ; 
 int stub2 (struct pm8001_hba_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct pm8001_hba_info*,struct pm8001_device*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

int pm8001_abort_task(struct sas_task *task)
{
	unsigned long flags;
	u32 tag;
	struct domain_device *dev ;
	struct pm8001_hba_info *pm8001_ha;
	struct scsi_lun lun;
	struct pm8001_device *pm8001_dev;
	struct pm8001_tmf_task tmf_task;
	int rc = TMF_RESP_FUNC_FAILED, ret;
	u32 phy_id;
	struct sas_task_slow slow_task;
	if (unlikely(!task || !task->lldd_task || !task->dev))
		return TMF_RESP_FUNC_FAILED;
	dev = task->dev;
	pm8001_dev = dev->lldd_dev;
	pm8001_ha = pm8001_find_ha_by_dev(dev);
	phy_id = pm8001_dev->attached_phy;
	rc = pm8001_find_tag(task, &tag);
	if (rc == 0) {
		pm8001_printk("no tag for task:%p\n", task);
		return TMF_RESP_FUNC_FAILED;
	}
	spin_lock_irqsave(&task->task_state_lock, flags);
	if (task->task_state_flags & SAS_TASK_STATE_DONE) {
		spin_unlock_irqrestore(&task->task_state_lock, flags);
		return TMF_RESP_FUNC_COMPLETE;
	}
	task->task_state_flags |= SAS_TASK_STATE_ABORTED;
	if (task->slow_task == NULL) {
		init_completion(&slow_task.completion);
		task->slow_task = &slow_task;
	}
	spin_unlock_irqrestore(&task->task_state_lock, flags);
	if (task->task_proto & SAS_PROTOCOL_SSP) {
		struct scsi_cmnd *cmnd = task->uldd_task;
		int_to_scsilun(cmnd->device->lun, &lun);
		tmf_task.tmf = TMF_ABORT_TASK;
		tmf_task.tag_of_task_to_be_managed = tag;
		rc = pm8001_issue_ssp_tmf(dev, lun.scsi_lun, &tmf_task);
		pm8001_exec_internal_task_abort(pm8001_ha, pm8001_dev,
			pm8001_dev->sas_device, 0, tag);
	} else if (task->task_proto & SAS_PROTOCOL_SATA ||
		task->task_proto & SAS_PROTOCOL_STP) {
		if (pm8001_ha->chip_id == chip_8006) {
			DECLARE_COMPLETION_ONSTACK(completion_reset);
			DECLARE_COMPLETION_ONSTACK(completion);
			struct pm8001_phy *phy = pm8001_ha->phy + phy_id;

			/* 1. Set Device state as Recovery */
			pm8001_dev->setds_completion = &completion;
			PM8001_CHIP_DISP->set_dev_state_req(pm8001_ha,
				pm8001_dev, 0x03);
			wait_for_completion(&completion);

			/* 2. Send Phy Control Hard Reset */
			reinit_completion(&completion);
			phy->reset_success = false;
			phy->enable_completion = &completion;
			phy->reset_completion = &completion_reset;
			ret = PM8001_CHIP_DISP->phy_ctl_req(pm8001_ha, phy_id,
				PHY_HARD_RESET);
			if (ret)
				goto out;
			PM8001_MSG_DBG(pm8001_ha,
				pm8001_printk("Waiting for local phy ctl\n"));
			wait_for_completion(&completion);
			if (!phy->reset_success)
				goto out;

			/* 3. Wait for Port Reset complete / Port reset TMO */
			PM8001_MSG_DBG(pm8001_ha,
				pm8001_printk("Waiting for Port reset\n"));
			wait_for_completion(&completion_reset);
			if (phy->port_reset_status) {
				pm8001_dev_gone_notify(dev);
				goto out;
			}

			/*
			 * 4. SATA Abort ALL
			 * we wait for the task to be aborted so that the task
			 * is removed from the ccb. on success the caller is
			 * going to free the task.
			 */
			ret = pm8001_exec_internal_task_abort(pm8001_ha,
				pm8001_dev, pm8001_dev->sas_device, 1, tag);
			if (ret)
				goto out;
			ret = wait_for_completion_timeout(
				&task->slow_task->completion,
				PM8001_TASK_TIMEOUT * HZ);
			if (!ret)
				goto out;

			/* 5. Set Device State as Operational */
			reinit_completion(&completion);
			pm8001_dev->setds_completion = &completion;
			PM8001_CHIP_DISP->set_dev_state_req(pm8001_ha,
				pm8001_dev, 0x01);
			wait_for_completion(&completion);
		} else {
			rc = pm8001_exec_internal_task_abort(pm8001_ha,
				pm8001_dev, pm8001_dev->sas_device, 0, tag);
		}
		rc = TMF_RESP_FUNC_COMPLETE;
	} else if (task->task_proto & SAS_PROTOCOL_SMP) {
		/* SMP */
		rc = pm8001_exec_internal_task_abort(pm8001_ha, pm8001_dev,
			pm8001_dev->sas_device, 0, tag);

	}
out:
	spin_lock_irqsave(&task->task_state_lock, flags);
	if (task->slow_task == &slow_task)
		task->slow_task = NULL;
	spin_unlock_irqrestore(&task->task_state_lock, flags);
	if (rc != TMF_RESP_FUNC_COMPLETE)
		pm8001_printk("rc= %d\n", rc);
	return rc;
}