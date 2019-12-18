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
struct hw_perf_event {int state; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int /*<<< orphan*/  etm_event_start (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int etm_event_add(struct perf_event *event, int mode)
{
	int ret = 0;
	struct hw_perf_event *hwc = &event->hw;

	if (mode & PERF_EF_START) {
		etm_event_start(event, 0);
		if (hwc->state & PERF_HES_STOPPED)
			ret = -EINVAL;
	} else {
		hwc->state = PERF_HES_STOPPED;
	}

	return ret;
}