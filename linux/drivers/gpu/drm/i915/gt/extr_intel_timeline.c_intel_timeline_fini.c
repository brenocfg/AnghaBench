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
struct intel_timeline {TYPE_1__* hwsp_ggtt; scalar_t__ hwsp_cacheline; int /*<<< orphan*/  requests; int /*<<< orphan*/  pin_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cacheline_free (scalar_t__) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_put (TYPE_1__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void intel_timeline_fini(struct intel_timeline *timeline)
{
	GEM_BUG_ON(atomic_read(&timeline->pin_count));
	GEM_BUG_ON(!list_empty(&timeline->requests));

	if (timeline->hwsp_cacheline)
		cacheline_free(timeline->hwsp_cacheline);
	else
		i915_gem_object_unpin_map(timeline->hwsp_ggtt->obj);

	i915_vma_put(timeline->hwsp_ggtt);
}