#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct ide_pm_state {scalar_t__ pm_step; } ;
struct TYPE_7__ {TYPE_1__* hwif; int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  name; struct request_queue* queue; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_8__ {scalar_t__ type; struct ide_pm_state* special; } ;
struct TYPE_6__ {int /*<<< orphan*/ * rq; } ;

/* Variables and functions */
 scalar_t__ ATA_PRIV_PM_SUSPEND ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  IDE_DFLAG_BLOCKED ; 
 scalar_t__ IDE_PM_COMPLETED ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_stop_hw_queues (struct request_queue*) ; 
 int /*<<< orphan*/  ide_complete_power_step (TYPE_2__*,struct request*) ; 
 TYPE_3__* ide_req (struct request*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*) ; 

void ide_complete_pm_rq(ide_drive_t *drive, struct request *rq)
{
	struct request_queue *q = drive->queue;
	struct ide_pm_state *pm = ide_req(rq)->special;

	ide_complete_power_step(drive, rq);
	if (pm->pm_step != IDE_PM_COMPLETED)
		return;

#ifdef DEBUG_PM
	printk("%s: completing PM request, %s\n", drive->name,
	       (ide_req(rq)->type == ATA_PRIV_PM_SUSPEND) ? "suspend" : "resume");
#endif
	if (ide_req(rq)->type == ATA_PRIV_PM_SUSPEND)
		blk_mq_stop_hw_queues(q);
	else
		drive->dev_flags &= ~IDE_DFLAG_BLOCKED;

	drive->hwif->rq = NULL;

	blk_mq_end_request(rq, BLK_STS_OK);
}