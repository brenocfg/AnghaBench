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
struct drm_i915_file_private {int /*<<< orphan*/  context_idr_lock; int /*<<< orphan*/  vm_idr_lock; int /*<<< orphan*/  context_idr; int /*<<< orphan*/  vm_idr; } ;
struct drm_file {struct drm_i915_file_private* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct i915_gem_context*) ; 
 int PTR_ERR (struct i915_gem_context*) ; 
 int /*<<< orphan*/  context_close (struct i915_gem_context*) ; 
 int gem_context_register (struct i915_gem_context*,struct drm_i915_file_private*) ; 
 int i915_gem_context_is_kernel (struct i915_gem_context*) ; 
 struct i915_gem_context* i915_gem_create_context (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_init_base (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int i915_gem_context_open(struct drm_i915_private *i915,
			  struct drm_file *file)
{
	struct drm_i915_file_private *file_priv = file->driver_priv;
	struct i915_gem_context *ctx;
	int err;

	mutex_init(&file_priv->context_idr_lock);
	mutex_init(&file_priv->vm_idr_lock);

	idr_init(&file_priv->context_idr);
	idr_init_base(&file_priv->vm_idr, 1);

	mutex_lock(&i915->drm.struct_mutex);
	ctx = i915_gem_create_context(i915, 0);
	mutex_unlock(&i915->drm.struct_mutex);
	if (IS_ERR(ctx)) {
		err = PTR_ERR(ctx);
		goto err;
	}

	err = gem_context_register(ctx, file_priv);
	if (err < 0)
		goto err_ctx;

	GEM_BUG_ON(i915_gem_context_is_kernel(ctx));
	GEM_BUG_ON(err > 0);

	return 0;

err_ctx:
	context_close(ctx);
err:
	idr_destroy(&file_priv->vm_idr);
	idr_destroy(&file_priv->context_idr);
	mutex_destroy(&file_priv->vm_idr_lock);
	mutex_destroy(&file_priv->context_idr_lock);
	return err;
}