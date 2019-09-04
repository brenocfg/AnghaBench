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
struct intel_context {struct i915_vma* state; } ;
struct i915_vma {int flags; TYPE_1__* obj; } ;
struct TYPE_2__ {int /*<<< orphan*/  pin_global; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_GTT_MIN_ALIGNMENT ; 
 int I915_VMA_GLOBAL_BIND ; 
 int PIN_GLOBAL ; 
 int PIN_HIGH ; 
 int i915_gem_object_set_to_gtt_domain (TYPE_1__*,int) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __context_pin(struct intel_context *ce)
{
	struct i915_vma *vma;
	int err;

	vma = ce->state;
	if (!vma)
		return 0;

	/*
	 * Clear this page out of any CPU caches for coherent swap-in/out.
	 * We only want to do this on the first bind so that we do not stall
	 * on an active context (which by nature is already on the GPU).
	 */
	if (!(vma->flags & I915_VMA_GLOBAL_BIND)) {
		err = i915_gem_object_set_to_gtt_domain(vma->obj, true);
		if (err)
			return err;
	}

	err = i915_vma_pin(vma, 0, I915_GTT_MIN_ALIGNMENT,
			   PIN_GLOBAL | PIN_HIGH);
	if (err)
		return err;

	/*
	 * And mark is as a globally pinned object to let the shrinker know
	 * it cannot reclaim the object until we release it.
	 */
	vma->obj->pin_global++;

	return 0;
}