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
struct i915_gem_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
typedef  struct i915_gem_context drm_file ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct i915_gem_context*) ; 
 int PTR_ERR (struct i915_gem_context*) ; 
 struct i915_gem_context* live_context (struct drm_i915_private*,struct i915_gem_context*) ; 
 struct i915_gem_context* mock_file (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mock_file_free (struct drm_i915_private*,struct i915_gem_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_prepare (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pm_resume (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pm_suspend (struct drm_i915_private*) ; 
 int /*<<< orphan*/  simulate_hibernate (struct drm_i915_private*) ; 
 int switch_to_context (struct drm_i915_private*,struct i915_gem_context*) ; 

__attribute__((used)) static int igt_gem_suspend(void *arg)
{
	struct drm_i915_private *i915 = arg;
	struct i915_gem_context *ctx;
	struct drm_file *file;
	int err;

	file = mock_file(i915);
	if (IS_ERR(file))
		return PTR_ERR(file);

	err = -ENOMEM;
	mutex_lock(&i915->drm.struct_mutex);
	ctx = live_context(i915, file);
	if (!IS_ERR(ctx))
		err = switch_to_context(i915, ctx);
	mutex_unlock(&i915->drm.struct_mutex);
	if (err)
		goto out;

	err = pm_prepare(i915);
	if (err)
		goto out;

	pm_suspend(i915);

	/* Here be dragons! Note that with S3RST any S3 may become S4! */
	simulate_hibernate(i915);

	pm_resume(i915);

	mutex_lock(&i915->drm.struct_mutex);
	err = switch_to_context(i915, ctx);
	mutex_unlock(&i915->drm.struct_mutex);
out:
	mock_file_free(i915, file);
	return err;
}