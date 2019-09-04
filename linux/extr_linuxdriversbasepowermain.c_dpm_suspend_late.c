#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  prev; } ;
struct TYPE_12__ {TYPE_7__ entry; } ;
struct device {TYPE_1__ power; } ;
struct TYPE_13__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ pm_message_t ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_14__ {int /*<<< orphan*/  failed_suspend_late; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUSPEND_SUSPEND_LATE ; 
 int /*<<< orphan*/  TPS (char*) ; 
 int async_error ; 
 int /*<<< orphan*/  async_synchronize_full () ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int device_suspend_late (struct device*) ; 
 int /*<<< orphan*/  dpm_late_early_list ; 
 int /*<<< orphan*/  dpm_list_mtx ; 
 int /*<<< orphan*/  dpm_resume_early (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_save_failed_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_save_failed_step (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_show_time (int /*<<< orphan*/ ,TYPE_2__,int,char*) ; 
 TYPE_7__ dpm_suspended_list ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  list_empty (TYPE_7__*) ; 
 int /*<<< orphan*/  list_move (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_dev_err (struct device*,TYPE_2__,char*,int) ; 
 TYPE_2__ pm_transition ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  resume_event (TYPE_2__) ; 
 TYPE_3__ suspend_stats ; 
 struct device* to_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_suspend_resume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int dpm_suspend_late(pm_message_t state)
{
	ktime_t starttime = ktime_get();
	int error = 0;

	trace_suspend_resume(TPS("dpm_suspend_late"), state.event, true);
	mutex_lock(&dpm_list_mtx);
	pm_transition = state;
	async_error = 0;

	while (!list_empty(&dpm_suspended_list)) {
		struct device *dev = to_device(dpm_suspended_list.prev);

		get_device(dev);
		mutex_unlock(&dpm_list_mtx);

		error = device_suspend_late(dev);

		mutex_lock(&dpm_list_mtx);
		if (!list_empty(&dev->power.entry))
			list_move(&dev->power.entry, &dpm_late_early_list);

		if (error) {
			pm_dev_err(dev, state, " late", error);
			dpm_save_failed_dev(dev_name(dev));
			put_device(dev);
			break;
		}
		put_device(dev);

		if (async_error)
			break;
	}
	mutex_unlock(&dpm_list_mtx);
	async_synchronize_full();
	if (!error)
		error = async_error;
	if (error) {
		suspend_stats.failed_suspend_late++;
		dpm_save_failed_step(SUSPEND_SUSPEND_LATE);
		dpm_resume_early(resume_event(state));
	}
	dpm_show_time(starttime, state, error, "late");
	trace_suspend_resume(TPS("dpm_suspend_late"), state.event, false);
	return error;
}