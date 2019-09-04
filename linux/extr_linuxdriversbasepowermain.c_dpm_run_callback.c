#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ pm_message_t ;
typedef  int (* pm_callback_t ) (struct device*) ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  initcall_debug_report (struct device*,int /*<<< orphan*/ ,int (*) (struct device*),int) ; 
 int /*<<< orphan*/  initcall_debug_start (struct device*,int (*) (struct device*)) ; 
 int /*<<< orphan*/  pm_dev_dbg (struct device*,TYPE_1__,char const*) ; 
 int /*<<< orphan*/  suspend_report_result (int (*) (struct device*),int) ; 
 int /*<<< orphan*/  trace_device_pm_callback_end (struct device*,int) ; 
 int /*<<< orphan*/  trace_device_pm_callback_start (struct device*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpm_run_callback(pm_callback_t cb, struct device *dev,
			    pm_message_t state, const char *info)
{
	ktime_t calltime;
	int error;

	if (!cb)
		return 0;

	calltime = initcall_debug_start(dev, cb);

	pm_dev_dbg(dev, state, info);
	trace_device_pm_callback_start(dev, info, state.event);
	error = cb(dev);
	trace_device_pm_callback_end(dev, error);
	suspend_report_result(cb, error);

	initcall_debug_report(dev, calltime, cb, error);

	return error;
}