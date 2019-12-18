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
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct sas_task {struct domain_device* dev; struct scsi_cmnd* uldd_task; } ;
struct sas_ha_struct {int /*<<< orphan*/  state; } ;
struct domain_device {int /*<<< orphan*/  done_lock; TYPE_1__* port; } ;
struct TYPE_2__ {struct sas_ha_struct* ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_SAS_TASK (struct scsi_cmnd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SAS_HA_FROZEN ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  sas_end_task (struct scsi_cmnd*,struct sas_task*) ; 
 int /*<<< orphan*/  sas_free_task (struct sas_task*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void sas_scsi_task_done(struct sas_task *task)
{
	struct scsi_cmnd *sc = task->uldd_task;
	struct domain_device *dev = task->dev;
	struct sas_ha_struct *ha = dev->port->ha;
	unsigned long flags;

	spin_lock_irqsave(&dev->done_lock, flags);
	if (test_bit(SAS_HA_FROZEN, &ha->state))
		task = NULL;
	else
		ASSIGN_SAS_TASK(sc, NULL);
	spin_unlock_irqrestore(&dev->done_lock, flags);

	if (unlikely(!task)) {
		/* task will be completed by the error handler */
		pr_debug("task done but aborted\n");
		return;
	}

	if (unlikely(!sc)) {
		pr_debug("task_done called with non existing SCSI cmnd!\n");
		sas_free_task(task);
		return;
	}

	sas_end_task(sc, task);
	sc->scsi_done(sc);
}