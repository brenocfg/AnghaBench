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
struct intel_context {int /*<<< orphan*/  engine; } ;
struct i915_vma {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int /*<<< orphan*/  intel_engine_pm_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engine_pool_put (int /*<<< orphan*/ ) ; 

void intel_emit_vma_release(struct intel_context *ce, struct i915_vma *vma)
{
	i915_vma_unpin(vma);
	intel_engine_pool_put(vma->private);
	intel_engine_pm_put(ce->engine);
}