#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct task_status_struct {int /*<<< orphan*/  stat; int /*<<< orphan*/  resp; } ;
struct sas_task {int /*<<< orphan*/  (* task_done ) (struct sas_task*) ;struct task_status_struct task_status; struct domain_device* dev; } ;
struct hisi_sas_tmf_task {int dummy; } ;
struct hisi_sas_dq {int /*<<< orphan*/  lock; } ;
struct hisi_hba {TYPE_1__* hw; int /*<<< orphan*/  sem; int /*<<< orphan*/  flags; struct device* dev; } ;
struct domain_device {scalar_t__ dev_type; struct asd_sas_port* port; } ;
struct device {int dummy; } ;
struct asd_sas_port {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* start_delivery ) (struct hisi_sas_dq*) ;} ;

/* Variables and functions */
 int ECOMM ; 
 int EINVAL ; 
 int /*<<< orphan*/  HISI_SAS_REJECT_CMD_BIT ; 
 int /*<<< orphan*/  SAS_PHY_DOWN ; 
 scalar_t__ SAS_SATA_DEV ; 
 int /*<<< orphan*/  SAS_TASK_UNDELIVERED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct hisi_hba* dev_to_hisi_hba (struct domain_device*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int hisi_sas_task_prep (struct sas_task*,struct hisi_sas_dq**,int,struct hisi_sas_tmf_task*,int*) ; 
 scalar_t__ in_softirq () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sas_task*) ; 
 int /*<<< orphan*/  stub2 (struct hisi_sas_dq*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisi_sas_task_exec(struct sas_task *task, gfp_t gfp_flags,
			      bool is_tmf, struct hisi_sas_tmf_task *tmf)
{
	u32 rc;
	u32 pass = 0;
	unsigned long flags;
	struct hisi_hba *hisi_hba;
	struct device *dev;
	struct domain_device *device = task->dev;
	struct asd_sas_port *sas_port = device->port;
	struct hisi_sas_dq *dq = NULL;

	if (!sas_port) {
		struct task_status_struct *ts = &task->task_status;

		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_PHY_DOWN;
		/*
		 * libsas will use dev->port, should
		 * not call task_done for sata
		 */
		if (device->dev_type != SAS_SATA_DEV)
			task->task_done(task);
		return -ECOMM;
	}

	hisi_hba = dev_to_hisi_hba(device);
	dev = hisi_hba->dev;

	if (unlikely(test_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags))) {
		if (in_softirq())
			return -EINVAL;

		down(&hisi_hba->sem);
		up(&hisi_hba->sem);
	}

	/* protect task_prep and start_delivery sequence */
	rc = hisi_sas_task_prep(task, &dq, is_tmf, tmf, &pass);
	if (rc)
		dev_err(dev, "task exec: failed[%d]!\n", rc);

	if (likely(pass)) {
		spin_lock_irqsave(&dq->lock, flags);
		hisi_hba->hw->start_delivery(dq);
		spin_unlock_irqrestore(&dq->lock, flags);
	}

	return rc;
}