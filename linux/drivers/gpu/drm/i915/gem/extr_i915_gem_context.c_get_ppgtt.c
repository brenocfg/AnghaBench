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
struct i915_gem_context {TYPE_2__* i915; struct i915_address_space* vm; } ;
struct i915_address_space {int dummy; } ;
struct drm_i915_gem_context_param {int value; scalar_t__ size; } ;
struct drm_i915_file_private {int /*<<< orphan*/  vm_idr_lock; int /*<<< orphan*/  vm_idr; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct i915_address_space* i915_vm_get (struct i915_address_space*) ; 
 int /*<<< orphan*/  i915_vm_put (struct i915_address_space*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct i915_address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_ppgtt(struct drm_i915_file_private *file_priv,
		     struct i915_gem_context *ctx,
		     struct drm_i915_gem_context_param *args)
{
	struct i915_address_space *vm;
	int ret;

	if (!ctx->vm)
		return -ENODEV;

	/* XXX rcu acquire? */
	ret = mutex_lock_interruptible(&ctx->i915->drm.struct_mutex);
	if (ret)
		return ret;

	vm = i915_vm_get(ctx->vm);
	mutex_unlock(&ctx->i915->drm.struct_mutex);

	ret = mutex_lock_interruptible(&file_priv->vm_idr_lock);
	if (ret)
		goto err_put;

	ret = idr_alloc(&file_priv->vm_idr, vm, 0, 0, GFP_KERNEL);
	GEM_BUG_ON(!ret);
	if (ret < 0)
		goto err_unlock;

	i915_vm_get(vm);

	args->size = 0;
	args->value = ret;

	ret = 0;
err_unlock:
	mutex_unlock(&file_priv->vm_idr_lock);
err_put:
	i915_vm_put(vm);
	return ret;
}