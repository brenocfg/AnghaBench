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
struct TYPE_2__ {int /*<<< orphan*/  vma; } ;
struct intel_engine_cs {int /*<<< orphan*/  i915; TYPE_1__ status_page; } ;
struct i915_vma {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWS_NEEDS_PHYSICAL (int /*<<< orphan*/ ) ; 
 struct i915_vma* fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int /*<<< orphan*/  intel_engine_set_hwsp_writemask (struct intel_engine_cs*,unsigned int) ; 

__attribute__((used)) static void cleanup_status_page(struct intel_engine_cs *engine)
{
	struct i915_vma *vma;

	/* Prevent writes into HWSP after returning the page to the system */
	intel_engine_set_hwsp_writemask(engine, ~0u);

	vma = fetch_and_zero(&engine->status_page.vma);
	if (!vma)
		return;

	if (!HWS_NEEDS_PHYSICAL(engine->i915))
		i915_vma_unpin(vma);

	i915_gem_object_unpin_map(vma->obj);
	i915_gem_object_put(vma->obj);
}