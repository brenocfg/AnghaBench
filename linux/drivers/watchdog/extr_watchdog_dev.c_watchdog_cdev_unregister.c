#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct watchdog_device {scalar_t__ id; struct watchdog_core_data* wd_data; int /*<<< orphan*/  status; } ;
struct watchdog_core_data {int /*<<< orphan*/  kref; int /*<<< orphan*/  work; int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; int /*<<< orphan*/ * wdd; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDOG_STOP_ON_UNREGISTER ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * old_wd_data ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ watchdog_active (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_core_data_release ; 
 int /*<<< orphan*/  watchdog_miscdev ; 
 int /*<<< orphan*/  watchdog_stop (struct watchdog_device*) ; 

__attribute__((used)) static void watchdog_cdev_unregister(struct watchdog_device *wdd)
{
	struct watchdog_core_data *wd_data = wdd->wd_data;

	cdev_del(&wd_data->cdev);
	if (wdd->id == 0) {
		misc_deregister(&watchdog_miscdev);
		old_wd_data = NULL;
	}

	if (watchdog_active(wdd) &&
	    test_bit(WDOG_STOP_ON_UNREGISTER, &wdd->status)) {
		watchdog_stop(wdd);
	}

	mutex_lock(&wd_data->lock);
	wd_data->wdd = NULL;
	wdd->wd_data = NULL;
	mutex_unlock(&wd_data->lock);

	hrtimer_cancel(&wd_data->timer);
	kthread_cancel_work_sync(&wd_data->work);

	kref_put(&wd_data->kref, watchdog_core_data_release);
}