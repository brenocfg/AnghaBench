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
struct TYPE_2__ {int /*<<< orphan*/  prev_count; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  cstate_pmu_read_counter (struct perf_event*) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cstate_pmu_event_start(struct perf_event *event, int mode)
{
	local64_set(&event->hw.prev_count, cstate_pmu_read_counter(event));
}