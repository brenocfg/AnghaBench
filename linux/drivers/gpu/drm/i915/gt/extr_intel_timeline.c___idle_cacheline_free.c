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
struct intel_timeline_cacheline {int /*<<< orphan*/  active; int /*<<< orphan*/  vaddr; TYPE_2__* hwsp; } ;
struct TYPE_4__ {TYPE_1__* vma; } ;
struct TYPE_3__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHELINE_BITS ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  __idle_hwsp_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_active_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_active_is_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_put (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct intel_timeline_cacheline*) ; 
 int /*<<< orphan*/  ptr_unmask_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __idle_cacheline_free(struct intel_timeline_cacheline *cl)
{
	GEM_BUG_ON(!i915_active_is_idle(&cl->active));

	i915_gem_object_unpin_map(cl->hwsp->vma->obj);
	i915_vma_put(cl->hwsp->vma);
	__idle_hwsp_free(cl->hwsp, ptr_unmask_bits(cl->vaddr, CACHELINE_BITS));

	i915_active_fini(&cl->active);
	kfree(cl);
}