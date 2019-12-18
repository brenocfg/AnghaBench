#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  uc; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ gt; TYPE_1__ drm; int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEM_TRACE (char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ i915_gem_init_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_load_power_context (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gt_is_wedged (TYPE_2__*) ; 
 scalar_t__ intel_gt_resume (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_gt_set_wedged (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_uc_resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void i915_gem_resume(struct drm_i915_private *i915)
{
	GEM_TRACE("\n");

	mutex_lock(&i915->drm.struct_mutex);
	intel_uncore_forcewake_get(&i915->uncore, FORCEWAKE_ALL);

	if (i915_gem_init_hw(i915))
		goto err_wedged;

	/*
	 * As we didn't flush the kernel context before suspend, we cannot
	 * guarantee that the context image is complete. So let's just reset
	 * it and start again.
	 */
	if (intel_gt_resume(&i915->gt))
		goto err_wedged;

	intel_uc_resume(&i915->gt.uc);

	/* Always reload a context for powersaving. */
	if (!i915_gem_load_power_context(i915))
		goto err_wedged;

out_unlock:
	intel_uncore_forcewake_put(&i915->uncore, FORCEWAKE_ALL);
	mutex_unlock(&i915->drm.struct_mutex);
	return;

err_wedged:
	if (!intel_gt_is_wedged(&i915->gt)) {
		dev_err(i915->drm.dev,
			"Failed to re-initialize GPU, declaring it wedged!\n");
		intel_gt_set_wedged(&i915->gt);
	}
	goto out_unlock;
}