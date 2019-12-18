#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int /*<<< orphan*/  request; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* function ) (TYPE_1__*) ;} ;
struct sas_task_slow {TYPE_1__ timer; } ;
struct sas_task {int /*<<< orphan*/  dev; struct sas_task_slow* slow_task; struct scsi_cmnd* uldd_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_abort_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ dev_is_sata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_ata_task_abort (struct sas_task*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void sas_task_abort(struct sas_task *task)
{
	struct scsi_cmnd *sc = task->uldd_task;

	/* Escape for libsas internal commands */
	if (!sc) {
		struct sas_task_slow *slow = task->slow_task;

		if (!slow)
			return;
		if (!del_timer(&slow->timer))
			return;
		slow->timer.function(&slow->timer);
		return;
	}

	if (dev_is_sata(task->dev))
		sas_ata_task_abort(task);
	else
		blk_abort_request(sc->request);
}