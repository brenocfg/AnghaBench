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
struct watchdog_device {int /*<<< orphan*/  id; TYPE_1__* info; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;
struct watchdog_core_data {int /*<<< orphan*/  kref; TYPE_2__ cdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  status; struct watchdog_device* wdd; } ;
struct inode {int dummy; } ;
struct file {struct watchdog_core_data* private_data; } ;
struct TYPE_3__ {int options; } ;

/* Variables and functions */
 int EBUSY ; 
 int WDIOF_MAGICCLOSE ; 
 int /*<<< orphan*/  WDOG_ACTIVE ; 
 int /*<<< orphan*/  _WDOG_ALLOW_RELEASE ; 
 int /*<<< orphan*/  _WDOG_DEV_OPEN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_core_data_release ; 
 scalar_t__ watchdog_hw_running (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_ping (struct watchdog_device*) ; 
 int watchdog_stop (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_update_worker (struct watchdog_device*) ; 

__attribute__((used)) static int watchdog_release(struct inode *inode, struct file *file)
{
	struct watchdog_core_data *wd_data = file->private_data;
	struct watchdog_device *wdd;
	int err = -EBUSY;
	bool running;

	mutex_lock(&wd_data->lock);

	wdd = wd_data->wdd;
	if (!wdd)
		goto done;

	/*
	 * We only stop the watchdog if we received the magic character
	 * or if WDIOF_MAGICCLOSE is not set. If nowayout was set then
	 * watchdog_stop will fail.
	 */
	if (!test_bit(WDOG_ACTIVE, &wdd->status))
		err = 0;
	else if (test_and_clear_bit(_WDOG_ALLOW_RELEASE, &wd_data->status) ||
		 !(wdd->info->options & WDIOF_MAGICCLOSE))
		err = watchdog_stop(wdd);

	/* If the watchdog was not stopped, send a keepalive ping */
	if (err < 0) {
		pr_crit("watchdog%d: watchdog did not stop!\n", wdd->id);
		watchdog_ping(wdd);
	}

	watchdog_update_worker(wdd);

	/* make sure that /dev/watchdog can be re-opened */
	clear_bit(_WDOG_DEV_OPEN, &wd_data->status);

done:
	running = wdd && watchdog_hw_running(wdd);
	mutex_unlock(&wd_data->lock);
	/*
	 * Allow the owner module to be unloaded again unless the watchdog
	 * is still running. If the watchdog is still running, it can not
	 * be stopped, and its driver must not be unloaded.
	 */
	if (!running) {
		module_put(wd_data->cdev.owner);
		kref_put(&wd_data->kref, watchdog_core_data_release);
	}
	return 0;
}