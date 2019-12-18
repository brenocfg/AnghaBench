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
struct intel_gt {TYPE_2__* i915; } ;
struct i915_gem_context {scalar_t__ vm; } ;
struct drm_file {scalar_t__ vm; } ;
struct TYPE_5__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_6__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_OBJECT_WRITE ; 
 scalar_t__ IS_ERR (struct i915_gem_context*) ; 
 int PTR_ERR (struct i915_gem_context*) ; 
 int __igt_reset_evict_vma (struct intel_gt*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evict_vma ; 
 struct i915_gem_context* live_context (TYPE_2__*,struct i915_gem_context*) ; 
 struct i915_gem_context* mock_file (TYPE_2__*) ; 
 int /*<<< orphan*/  mock_file_free (TYPE_2__*,struct i915_gem_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int igt_reset_evict_ppgtt(void *arg)
{
	struct intel_gt *gt = arg;
	struct i915_gem_context *ctx;
	struct drm_file *file;
	int err;

	file = mock_file(gt->i915);
	if (IS_ERR(file))
		return PTR_ERR(file);

	mutex_lock(&gt->i915->drm.struct_mutex);
	ctx = live_context(gt->i915, file);
	mutex_unlock(&gt->i915->drm.struct_mutex);
	if (IS_ERR(ctx)) {
		err = PTR_ERR(ctx);
		goto out;
	}

	err = 0;
	if (ctx->vm) /* aliasing == global gtt locking, covered above */
		err = __igt_reset_evict_vma(gt, ctx->vm,
					    evict_vma, EXEC_OBJECT_WRITE);

out:
	mock_file_free(gt->i915, file);
	return err;
}