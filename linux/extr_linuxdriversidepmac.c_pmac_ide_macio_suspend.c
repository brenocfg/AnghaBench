#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int event; } ;
struct TYPE_6__ {TYPE_3__ power_state; } ;
struct TYPE_9__ {TYPE_1__ power; } ;
struct TYPE_7__ {TYPE_5__ dev; } ;
struct macio_dev {TYPE_2__ ofdev; } ;
typedef  int /*<<< orphan*/  pmac_ide_hwif_t ;
typedef  TYPE_3__ pm_message_t ;

/* Variables and functions */
 int PM_EVENT_SLEEP ; 
 int /*<<< orphan*/ * dev_get_drvdata (TYPE_5__*) ; 
 int pmac_ide_do_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pmac_ide_macio_suspend(struct macio_dev *mdev, pm_message_t mesg)
{
	pmac_ide_hwif_t *pmif = dev_get_drvdata(&mdev->ofdev.dev);
	int rc = 0;

	if (mesg.event != mdev->ofdev.dev.power.power_state.event
			&& (mesg.event & PM_EVENT_SLEEP)) {
		rc = pmac_ide_do_suspend(pmif);
		if (rc == 0)
			mdev->ofdev.dev.power.power_state = mesg;
	}

	return rc;
}