#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct attribute** pmu_attr; struct attribute** i915_attr; } ;
struct drm_i915_private {TYPE_1__ pmu; } ;
struct attribute {struct attribute** name; } ;
struct TYPE_4__ {struct attribute** attrs; } ;

/* Variables and functions */
 TYPE_2__ i915_pmu_events_attr_group ; 
 int /*<<< orphan*/  kfree (struct attribute**) ; 

__attribute__((used)) static void free_event_attributes(struct drm_i915_private *i915)
{
	struct attribute **attr_iter = i915_pmu_events_attr_group.attrs;

	for (; *attr_iter; attr_iter++)
		kfree((*attr_iter)->name);

	kfree(i915_pmu_events_attr_group.attrs);
	kfree(i915->pmu.i915_attr);
	kfree(i915->pmu.pmu_attr);

	i915_pmu_events_attr_group.attrs = NULL;
	i915->pmu.i915_attr = NULL;
	i915->pmu.pmu_attr = NULL;
}