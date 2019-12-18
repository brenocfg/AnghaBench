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
struct wa_lists {int dummy; } ;
struct i915_gem_context {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  gt; int /*<<< orphan*/  runtime_pm; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_ENGINES ; 
 int ESRCH ; 
 scalar_t__ IS_ERR (struct i915_gem_context*) ; 
 int PTR_ERR (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_lock_engines (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_unlock_engines (struct i915_gem_context*) ; 
 int /*<<< orphan*/  igt_global_reset_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igt_global_reset_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gt_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  intel_has_gpu_reset (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct i915_gem_context* kernel_context (struct drm_i915_private*) ; 
 int /*<<< orphan*/  kernel_context_close (struct i915_gem_context*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  reference_lists_fini (struct drm_i915_private*,struct wa_lists*) ; 
 int /*<<< orphan*/  reference_lists_init (struct drm_i915_private*,struct wa_lists*) ; 
 int verify_wa_lists (struct i915_gem_context*,struct wa_lists*,char*) ; 

__attribute__((used)) static int
live_gpu_reset_workarounds(void *arg)
{
	struct drm_i915_private *i915 = arg;
	struct i915_gem_context *ctx;
	intel_wakeref_t wakeref;
	struct wa_lists lists;
	bool ok;

	if (!intel_has_gpu_reset(i915))
		return 0;

	ctx = kernel_context(i915);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	i915_gem_context_lock_engines(ctx);

	pr_info("Verifying after GPU reset...\n");

	igt_global_reset_lock(&i915->gt);
	wakeref = intel_runtime_pm_get(&i915->runtime_pm);

	reference_lists_init(i915, &lists);

	ok = verify_wa_lists(ctx, &lists, "before reset");
	if (!ok)
		goto out;

	intel_gt_reset(&i915->gt, ALL_ENGINES, "live_workarounds");

	ok = verify_wa_lists(ctx, &lists, "after reset");

out:
	i915_gem_context_unlock_engines(ctx);
	kernel_context_close(ctx);
	reference_lists_fini(i915, &lists);
	intel_runtime_pm_put(&i915->runtime_pm, wakeref);
	igt_global_reset_unlock(&i915->gt);

	return ok ? 0 : -ESRCH;
}