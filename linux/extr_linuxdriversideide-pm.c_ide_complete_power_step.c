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
struct request {struct ide_pm_state* special; } ;
struct ide_pm_state {int pm_step; int /*<<< orphan*/  pm_state; } ;
struct TYPE_3__ {scalar_t__ media; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 void* IDE_PM_COMPLETED ; 
#define  IDE_PM_FLUSH_CACHE 131 
#define  IDE_PM_IDLE 130 
 int IDE_PM_RESTORE_DMA ; 
#define  IDE_PM_RESTORE_PIO 129 
#define  IDE_PM_STANDBY 128 
 int /*<<< orphan*/  PM_EVENT_FREEZE ; 
 scalar_t__ ide_disk ; 

void ide_complete_power_step(ide_drive_t *drive, struct request *rq)
{
	struct ide_pm_state *pm = rq->special;

#ifdef DEBUG_PM
	printk(KERN_INFO "%s: complete_power_step(step: %d)\n",
		drive->name, pm->pm_step);
#endif
	if (drive->media != ide_disk)
		return;

	switch (pm->pm_step) {
	case IDE_PM_FLUSH_CACHE:	/* Suspend step 1 (flush cache) */
		if (pm->pm_state == PM_EVENT_FREEZE)
			pm->pm_step = IDE_PM_COMPLETED;
		else
			pm->pm_step = IDE_PM_STANDBY;
		break;
	case IDE_PM_STANDBY:		/* Suspend step 2 (standby) */
		pm->pm_step = IDE_PM_COMPLETED;
		break;
	case IDE_PM_RESTORE_PIO:	/* Resume step 1 (restore PIO) */
		pm->pm_step = IDE_PM_IDLE;
		break;
	case IDE_PM_IDLE:		/* Resume step 2 (idle)*/
		pm->pm_step = IDE_PM_RESTORE_DMA;
		break;
	}
}