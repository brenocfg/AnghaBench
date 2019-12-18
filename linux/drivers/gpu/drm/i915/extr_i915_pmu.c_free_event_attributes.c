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
struct i915_pmu {struct attribute** pmu_attr; struct attribute** i915_attr; } ;
struct attribute {struct attribute** name; } ;
struct TYPE_2__ {struct attribute** attrs; } ;

/* Variables and functions */
 TYPE_1__ i915_pmu_events_attr_group ; 
 int /*<<< orphan*/  kfree (struct attribute**) ; 

__attribute__((used)) static void free_event_attributes(struct i915_pmu *pmu)
{
	struct attribute **attr_iter = i915_pmu_events_attr_group.attrs;

	for (; *attr_iter; attr_iter++)
		kfree((*attr_iter)->name);

	kfree(i915_pmu_events_attr_group.attrs);
	kfree(pmu->i915_attr);
	kfree(pmu->pmu_attr);

	i915_pmu_events_attr_group.attrs = NULL;
	pmu->i915_attr = NULL;
	pmu->pmu_attr = NULL;
}