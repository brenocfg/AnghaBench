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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int I915_SHRINK_ACTIVE ; 
 int I915_SHRINK_BOUND ; 
 int I915_SHRINK_UNBOUND ; 
 unsigned long i915_gem_shrink (struct drm_i915_private*,unsigned long,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 

unsigned long i915_gem_shrink_all(struct drm_i915_private *i915)
{
	unsigned long freed;

	intel_runtime_pm_get(i915);
	freed = i915_gem_shrink(i915, -1UL, NULL,
				I915_SHRINK_BOUND |
				I915_SHRINK_UNBOUND |
				I915_SHRINK_ACTIVE);
	intel_runtime_pm_put(i915);

	return freed;
}