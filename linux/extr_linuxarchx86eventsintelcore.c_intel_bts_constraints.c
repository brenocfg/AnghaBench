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
struct event_constraint {int dummy; } ;

/* Variables and functions */
 struct event_constraint bts_constraint ; 
 int /*<<< orphan*/  intel_pmu_has_bts (struct perf_event*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct event_constraint *
intel_bts_constraints(struct perf_event *event)
{
	if (unlikely(intel_pmu_has_bts(event)))
		return &bts_constraint;

	return NULL;
}