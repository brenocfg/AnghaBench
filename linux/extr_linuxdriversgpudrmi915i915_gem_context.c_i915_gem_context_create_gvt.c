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
struct i915_gem_context {int ring_size; struct i915_gem_context* file_priv; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DRM_I915_GVT ; 
 int EBADF ; 
 int ENODEV ; 
 struct i915_gem_context* ERR_PTR (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct i915_gem_context*) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  USES_GUC_SUBMISSION (int /*<<< orphan*/ ) ; 
 struct i915_gem_context* __create_hw_context (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_context_clear_bannable (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_is_kernel (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_closed (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_force_single_submission (struct i915_gem_context*) ; 
 int i915_mutex_lock_interruptible (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_i915 (struct drm_device*) ; 

struct i915_gem_context *
i915_gem_context_create_gvt(struct drm_device *dev)
{
	struct i915_gem_context *ctx;
	int ret;

	if (!IS_ENABLED(CONFIG_DRM_I915_GVT))
		return ERR_PTR(-ENODEV);

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ERR_PTR(ret);

	ctx = __create_hw_context(to_i915(dev), NULL);
	if (IS_ERR(ctx))
		goto out;

	ctx->file_priv = ERR_PTR(-EBADF);
	i915_gem_context_set_closed(ctx); /* not user accessible */
	i915_gem_context_clear_bannable(ctx);
	i915_gem_context_set_force_single_submission(ctx);
	if (!USES_GUC_SUBMISSION(to_i915(dev)))
		ctx->ring_size = 512 * PAGE_SIZE; /* Max ring buffer size */

	GEM_BUG_ON(i915_gem_context_is_kernel(ctx));
out:
	mutex_unlock(&dev->struct_mutex);
	return ctx;
}