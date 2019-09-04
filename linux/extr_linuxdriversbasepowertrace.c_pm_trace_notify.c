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
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  PM_POST_HIBERNATION 129 
#define  PM_POST_SUSPEND 128 
 int pm_trace_rtc_abused ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int
pm_trace_notify(struct notifier_block *nb, unsigned long mode, void *_unused)
{
	switch (mode) {
	case PM_POST_HIBERNATION:
	case PM_POST_SUSPEND:
		if (pm_trace_rtc_abused) {
			pm_trace_rtc_abused = false;
			pr_warn("Possible incorrect RTC due to pm_trace, please use 'ntpdate' or 'rdate' to reset it.\n");
		}
		break;
	default:
		break;
	}
	return 0;
}