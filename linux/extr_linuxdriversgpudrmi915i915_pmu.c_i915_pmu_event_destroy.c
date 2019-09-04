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
struct perf_event {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  engine_event_destroy (struct perf_event*) ; 
 scalar_t__ is_engine_event (struct perf_event*) ; 

__attribute__((used)) static void i915_pmu_event_destroy(struct perf_event *event)
{
	WARN_ON(event->parent);

	if (is_engine_event(event))
		engine_event_destroy(event);
}