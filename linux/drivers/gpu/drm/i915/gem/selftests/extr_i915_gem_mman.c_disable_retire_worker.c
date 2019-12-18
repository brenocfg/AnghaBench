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
struct TYPE_2__ {int /*<<< orphan*/  idle_work; int /*<<< orphan*/  retire_work; } ;
struct drm_i915_private {TYPE_1__ gem; int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_driver_unregister__shrinker (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gt_pm_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disable_retire_worker(struct drm_i915_private *i915)
{
	i915_gem_driver_unregister__shrinker(i915);

	intel_gt_pm_get(&i915->gt);

	cancel_delayed_work_sync(&i915->gem.retire_work);
	flush_work(&i915->gem.idle_work);
}