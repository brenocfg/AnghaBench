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
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WAIT_LOCKED ; 
 int /*<<< orphan*/  i915_gem_driver_register__shrinker (struct drm_i915_private*) ; 
 int /*<<< orphan*/  igt_flush_test (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_gt_pm_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void restore_retire_worker(struct drm_i915_private *i915)
{
	intel_gt_pm_put(&i915->gt);

	mutex_lock(&i915->drm.struct_mutex);
	igt_flush_test(i915, I915_WAIT_LOCKED);
	mutex_unlock(&i915->drm.struct_mutex);

	i915_gem_driver_register__shrinker(i915);
}