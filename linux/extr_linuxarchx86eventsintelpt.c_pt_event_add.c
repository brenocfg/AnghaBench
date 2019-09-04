#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ event; } ;
struct pt {TYPE_1__ handle; } ;
struct hw_perf_event {scalar_t__ state; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int PERF_EF_START ; 
 scalar_t__ PERF_HES_STOPPED ; 
 int /*<<< orphan*/  pt_ctx ; 
 int /*<<< orphan*/  pt_event_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 struct pt* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pt_event_add(struct perf_event *event, int mode)
{
	struct pt *pt = this_cpu_ptr(&pt_ctx);
	struct hw_perf_event *hwc = &event->hw;
	int ret = -EBUSY;

	if (pt->handle.event)
		goto fail;

	if (mode & PERF_EF_START) {
		pt_event_start(event, 0);
		ret = -EINVAL;
		if (hwc->state == PERF_HES_STOPPED)
			goto fail;
	} else {
		hwc->state = PERF_HES_STOPPED;
	}

	ret = 0;
fail:

	return ret;
}