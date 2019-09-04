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
struct TYPE_4__ {int /*<<< orphan*/  idle_work; int /*<<< orphan*/  retire_work; int /*<<< orphan*/  active_requests; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ gt; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_unpark (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disable_retire_worker(struct drm_i915_private *i915)
{
	mutex_lock(&i915->drm.struct_mutex);
	if (!i915->gt.active_requests++) {
		intel_runtime_pm_get(i915);
		i915_gem_unpark(i915);
		intel_runtime_pm_put(i915);
	}
	mutex_unlock(&i915->drm.struct_mutex);
	cancel_delayed_work_sync(&i915->gt.retire_work);
	cancel_delayed_work_sync(&i915->gt.idle_work);
}