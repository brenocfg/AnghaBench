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
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* resume ) (struct drm_i915_private*) ;int /*<<< orphan*/  awake; } ;
struct drm_i915_private {int /*<<< orphan*/  gpu_error; TYPE_1__ drm; TYPE_2__ gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEM_TRACE (char*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ i915_gem_init_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_restore_fences (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_restore_gtt_mappings (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_set_wedged (struct drm_i915_private*) ; 
 scalar_t__ i915_gem_switch_to_kernel_context (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_terminally_wedged (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_resume (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*) ; 

void i915_gem_resume(struct drm_i915_private *i915)
{
	GEM_TRACE("\n");

	WARN_ON(i915->gt.awake);

	mutex_lock(&i915->drm.struct_mutex);
	intel_uncore_forcewake_get(i915, FORCEWAKE_ALL);

	i915_gem_restore_gtt_mappings(i915);
	i915_gem_restore_fences(i915);

	/*
	 * As we didn't flush the kernel context before suspend, we cannot
	 * guarantee that the context image is complete. So let's just reset
	 * it and start again.
	 */
	i915->gt.resume(i915);

	if (i915_gem_init_hw(i915))
		goto err_wedged;

	intel_uc_resume(i915);

	/* Always reload a context for powersaving. */
	if (i915_gem_switch_to_kernel_context(i915))
		goto err_wedged;

out_unlock:
	intel_uncore_forcewake_put(i915, FORCEWAKE_ALL);
	mutex_unlock(&i915->drm.struct_mutex);
	return;

err_wedged:
	if (!i915_terminally_wedged(&i915->gpu_error)) {
		DRM_ERROR("failed to re-initialize GPU, declaring wedged!\n");
		i915_gem_set_wedged(i915);
	}
	goto out_unlock;
}