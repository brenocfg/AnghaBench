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
struct TYPE_2__ {int /*<<< orphan*/  total; int /*<<< orphan*/  (* clear_range ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct i915_ggtt {TYPE_1__ vm; } ;
struct drm_i915_private {struct i915_ggtt ggtt; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_check_and_clear_faults (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_ggtt_invalidate (struct drm_i915_private*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i915_gem_suspend_gtt_mappings(struct drm_i915_private *dev_priv)
{
	struct i915_ggtt *ggtt = &dev_priv->ggtt;

	/* Don't bother messing with faults pre GEN6 as we have little
	 * documentation supporting that it's a good idea.
	 */
	if (INTEL_GEN(dev_priv) < 6)
		return;

	i915_check_and_clear_faults(dev_priv);

	ggtt->vm.clear_range(&ggtt->vm, 0, ggtt->vm.total);

	i915_ggtt_invalidate(dev_priv);
}