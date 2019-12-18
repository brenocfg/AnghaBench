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
struct i915_gem_context {TYPE_2__* i915; int /*<<< orphan*/  mutex; struct i915_address_space* vm; } ;
struct i915_address_space {int dummy; } ;
struct drm_i915_gem_context_param {int /*<<< orphan*/  value; scalar_t__ size; } ;
struct drm_i915_file_private {int /*<<< orphan*/  vm_idr_lock; int /*<<< orphan*/  vm_idr; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_ENGINES ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 struct i915_address_space* __set_ppgtt (struct i915_gem_context*,struct i915_address_space*) ; 
 int context_barrier_task (struct i915_gem_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i915_address_space*) ; 
 int /*<<< orphan*/  emit_ppgtt_update ; 
 int /*<<< orphan*/  i915_vm_get (struct i915_address_space*) ; 
 int /*<<< orphan*/  i915_vm_put (struct i915_address_space*) ; 
 struct i915_address_space* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lut_close (struct i915_gem_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_ppgtt_barrier ; 
 int /*<<< orphan*/  skip_ppgtt_update ; 
 scalar_t__ upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_ppgtt(struct drm_i915_file_private *file_priv,
		     struct i915_gem_context *ctx,
		     struct drm_i915_gem_context_param *args)
{
	struct i915_address_space *vm, *old;
	int err;

	if (args->size)
		return -EINVAL;

	if (!ctx->vm)
		return -ENODEV;

	if (upper_32_bits(args->value))
		return -ENOENT;

	err = mutex_lock_interruptible(&file_priv->vm_idr_lock);
	if (err)
		return err;

	vm = idr_find(&file_priv->vm_idr, args->value);
	if (vm)
		i915_vm_get(vm);
	mutex_unlock(&file_priv->vm_idr_lock);
	if (!vm)
		return -ENOENT;

	err = mutex_lock_interruptible(&ctx->i915->drm.struct_mutex);
	if (err)
		goto out;

	if (vm == ctx->vm)
		goto unlock;

	/* Teardown the existing obj:vma cache, it will have to be rebuilt. */
	mutex_lock(&ctx->mutex);
	lut_close(ctx);
	mutex_unlock(&ctx->mutex);

	old = __set_ppgtt(ctx, vm);

	/*
	 * We need to flush any requests using the current ppgtt before
	 * we release it as the requests do not hold a reference themselves,
	 * only indirectly through the context.
	 */
	err = context_barrier_task(ctx, ALL_ENGINES,
				   skip_ppgtt_update,
				   emit_ppgtt_update,
				   set_ppgtt_barrier,
				   old);
	if (err) {
		i915_vm_put(__set_ppgtt(ctx, old));
		i915_vm_put(old);
	}

unlock:
	mutex_unlock(&ctx->i915->drm.struct_mutex);

out:
	i915_vm_put(vm);
	return err;
}