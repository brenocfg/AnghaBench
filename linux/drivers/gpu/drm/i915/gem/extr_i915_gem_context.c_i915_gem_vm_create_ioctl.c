#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct drm_i915_file_private* file; } ;
struct i915_ppgtt {TYPE_1__ vm; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_gem_vm_control {int vm_id; scalar_t__ extensions; scalar_t__ flags; } ;
struct drm_i915_file_private {int /*<<< orphan*/  vm_idr_lock; int /*<<< orphan*/  vm_idr; } ;
struct drm_file {struct drm_i915_file_private* driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HAS_FULL_PPGTT (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (struct i915_ppgtt*) ; 
 int PTR_ERR (struct i915_ppgtt*) ; 
 struct i915_ppgtt* i915_ppgtt_create (struct drm_i915_private*) ; 
 int i915_user_extensions (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i915_ppgtt*) ; 
 int /*<<< orphan*/  i915_vm_put (TYPE_1__*) ; 
 int idr_alloc (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int /*<<< orphan*/  u64_to_user_ptr (scalar_t__) ; 

int i915_gem_vm_create_ioctl(struct drm_device *dev, void *data,
			     struct drm_file *file)
{
	struct drm_i915_private *i915 = to_i915(dev);
	struct drm_i915_gem_vm_control *args = data;
	struct drm_i915_file_private *file_priv = file->driver_priv;
	struct i915_ppgtt *ppgtt;
	int err;

	if (!HAS_FULL_PPGTT(i915))
		return -ENODEV;

	if (args->flags)
		return -EINVAL;

	ppgtt = i915_ppgtt_create(i915);
	if (IS_ERR(ppgtt))
		return PTR_ERR(ppgtt);

	ppgtt->vm.file = file_priv;

	if (args->extensions) {
		err = i915_user_extensions(u64_to_user_ptr(args->extensions),
					   NULL, 0,
					   ppgtt);
		if (err)
			goto err_put;
	}

	err = mutex_lock_interruptible(&file_priv->vm_idr_lock);
	if (err)
		goto err_put;

	err = idr_alloc(&file_priv->vm_idr, &ppgtt->vm, 0, 0, GFP_KERNEL);
	if (err < 0)
		goto err_unlock;

	GEM_BUG_ON(err == 0); /* reserved for invalid/unassigned ppgtt */

	mutex_unlock(&file_priv->vm_idr_lock);

	args->vm_id = err;
	return 0;

err_unlock:
	mutex_unlock(&file_priv->vm_idr_lock);
err_put:
	i915_vm_put(&ppgtt->vm);
	return err;
}