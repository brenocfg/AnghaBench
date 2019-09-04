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
struct TYPE_2__ {int /*<<< orphan*/  idx; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  arc_perf_event_update (struct perf_event*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arc_pmu_read(struct perf_event *event)
{
	arc_perf_event_update(event, &event->hw, event->hw.idx);
}