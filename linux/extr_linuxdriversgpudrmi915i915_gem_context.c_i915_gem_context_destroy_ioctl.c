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
struct i915_gem_context {int dummy; } ;
struct drm_i915_gem_context_destroy {scalar_t__ pad; scalar_t__ ctx_id; } ;
struct drm_i915_file_private {int dummy; } ;
struct drm_file {struct drm_i915_file_private* driver_priv; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_CONTEXT_HANDLE ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  __destroy_hw_context (struct i915_gem_context*,struct drm_i915_file_private*) ; 
 struct i915_gem_context* i915_gem_context_lookup (struct drm_i915_file_private*,scalar_t__) ; 
 int /*<<< orphan*/  i915_gem_context_put (struct i915_gem_context*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int i915_gem_context_destroy_ioctl(struct drm_device *dev, void *data,
				   struct drm_file *file)
{
	struct drm_i915_gem_context_destroy *args = data;
	struct drm_i915_file_private *file_priv = file->driver_priv;
	struct i915_gem_context *ctx;
	int ret;

	if (args->pad != 0)
		return -EINVAL;

	if (args->ctx_id == DEFAULT_CONTEXT_HANDLE)
		return -ENOENT;

	ctx = i915_gem_context_lookup(file_priv, args->ctx_id);
	if (!ctx)
		return -ENOENT;

	ret = mutex_lock_interruptible(&dev->struct_mutex);
	if (ret)
		goto out;

	__destroy_hw_context(ctx, file_priv);
	mutex_unlock(&dev->struct_mutex);

out:
	i915_gem_context_put(ctx);
	return 0;
}