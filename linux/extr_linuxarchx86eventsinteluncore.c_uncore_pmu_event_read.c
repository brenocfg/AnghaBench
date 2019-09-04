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
struct perf_event {int dummy; } ;
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 struct intel_uncore_box* uncore_event_to_box (struct perf_event*) ; 
 int /*<<< orphan*/  uncore_perf_event_update (struct intel_uncore_box*,struct perf_event*) ; 

void uncore_pmu_event_read(struct perf_event *event)
{
	struct intel_uncore_box *box = uncore_event_to_box(event);
	uncore_perf_event_update(box, event);
}