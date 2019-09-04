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
struct i915_gem_context {TYPE_2__* ppgtt; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
struct TYPE_4__ {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct i915_gem_context*) ; 
 int PTR_ERR (struct i915_gem_context*) ; 
 int __igt_reset_evict_vma (struct drm_i915_private*,int /*<<< orphan*/ *) ; 
 struct i915_gem_context* kernel_context (struct drm_i915_private*) ; 
 int /*<<< orphan*/  kernel_context_close (struct i915_gem_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int igt_reset_evict_ppgtt(void *arg)
{
	struct drm_i915_private *i915 = arg;
	struct i915_gem_context *ctx;
	int err;

	mutex_lock(&i915->drm.struct_mutex);
	ctx = kernel_context(i915);
	mutex_unlock(&i915->drm.struct_mutex);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	err = 0;
	if (ctx->ppgtt) /* aliasing == global gtt locking, covered above */
		err = __igt_reset_evict_vma(i915, &ctx->ppgtt->vm);

	kernel_context_close(ctx);
	return err;
}