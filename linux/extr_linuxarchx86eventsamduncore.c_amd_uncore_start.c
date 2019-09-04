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
typedef  int u64 ;
struct hw_perf_event {int config; int /*<<< orphan*/  config_base; scalar_t__ state; int /*<<< orphan*/  prev_count; int /*<<< orphan*/  event_base; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int ARCH_PERFMON_EVENTSEL_ENABLE ; 
 int PERF_EF_RELOAD ; 
 scalar_t__ local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void amd_uncore_start(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;

	if (flags & PERF_EF_RELOAD)
		wrmsrl(hwc->event_base, (u64)local64_read(&hwc->prev_count));

	hwc->state = 0;
	wrmsrl(hwc->config_base, (hwc->config | ARCH_PERFMON_EVENTSEL_ENABLE));
	perf_event_update_userpage(event);
}