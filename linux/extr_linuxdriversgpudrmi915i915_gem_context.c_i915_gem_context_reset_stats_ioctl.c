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
struct i915_gem_context {int /*<<< orphan*/  active_count; int /*<<< orphan*/  guilty_count; } ;
struct drm_i915_reset_stats {void* batch_pending; void* batch_active; scalar_t__ reset_count; int /*<<< orphan*/  ctx_id; scalar_t__ pad; scalar_t__ flags; } ;
struct drm_i915_private {int /*<<< orphan*/  gpu_error; } ;
struct drm_file {int /*<<< orphan*/  driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int ENOENT ; 
 struct i915_gem_context* __i915_gem_context_lookup_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 scalar_t__ i915_reset_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

int i915_gem_context_reset_stats_ioctl(struct drm_device *dev,
				       void *data, struct drm_file *file)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct drm_i915_reset_stats *args = data;
	struct i915_gem_context *ctx;
	int ret;

	if (args->flags || args->pad)
		return -EINVAL;

	ret = -ENOENT;
	rcu_read_lock();
	ctx = __i915_gem_context_lookup_rcu(file->driver_priv, args->ctx_id);
	if (!ctx)
		goto out;

	/*
	 * We opt for unserialised reads here. This may result in tearing
	 * in the extremely unlikely event of a GPU hang on this context
	 * as we are querying them. If we need that extra layer of protection,
	 * we should wrap the hangstats with a seqlock.
	 */

	if (capable(CAP_SYS_ADMIN))
		args->reset_count = i915_reset_count(&dev_priv->gpu_error);
	else
		args->reset_count = 0;

	args->batch_active = atomic_read(&ctx->guilty_count);
	args->batch_pending = atomic_read(&ctx->active_count);

	ret = 0;
out:
	rcu_read_unlock();
	return ret;
}