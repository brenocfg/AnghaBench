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
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  __pmu_event_start (struct perf_event*) ; 

__attribute__((used)) static int pmu_event_add(struct perf_event *event, int mode)
{
	struct hw_perf_event *hwc = &event->hw;

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	if (mode & PERF_EF_START)
		__pmu_event_start(event);

	return 0;
}