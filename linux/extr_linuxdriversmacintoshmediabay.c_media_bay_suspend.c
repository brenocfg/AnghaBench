#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct media_bay_info {int sleeping; int /*<<< orphan*/  lock; } ;
struct TYPE_9__ {int event; } ;
struct TYPE_6__ {TYPE_4__ power_state; } ;
struct TYPE_7__ {TYPE_1__ power; } ;
struct TYPE_8__ {TYPE_2__ dev; } ;
struct macio_dev {TYPE_3__ ofdev; } ;
typedef  TYPE_4__ pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  MB_POLL_DELAY ; 
 int PM_EVENT_SLEEP ; 
 struct media_bay_info* macio_get_drvdata (struct macio_dev*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_mb_power (struct media_bay_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int media_bay_suspend(struct macio_dev *mdev, pm_message_t state)
{
	struct media_bay_info	*bay = macio_get_drvdata(mdev);

	if (state.event != mdev->ofdev.dev.power.power_state.event
	    && (state.event & PM_EVENT_SLEEP)) {
		mutex_lock(&bay->lock);
		bay->sleeping = 1;
		set_mb_power(bay, 0);
		mutex_unlock(&bay->lock);
		msleep(MB_POLL_DELAY);
		mdev->ofdev.dev.power.power_state = state;
	}
	return 0;
}