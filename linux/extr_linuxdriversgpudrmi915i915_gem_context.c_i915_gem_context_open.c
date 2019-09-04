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
struct drm_i915_file_private {int /*<<< orphan*/  context_idr; } ;
struct drm_file {struct drm_i915_file_private* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct i915_gem_context*) ; 
 int PTR_ERR (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_is_kernel (struct i915_gem_context*) ; 
 struct i915_gem_context* i915_gem_create_context (struct drm_i915_private*,struct drm_i915_file_private*) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int i915_gem_context_open(struct drm_i915_private *i915,
			  struct drm_file *file)
{
	struct drm_i915_file_private *file_priv = file->driver_priv;
	struct i915_gem_context *ctx;

	idr_init(&file_priv->context_idr);

	mutex_lock(&i915->drm.struct_mutex);
	ctx = i915_gem_create_context(i915, file_priv);
	mutex_unlock(&i915->drm.struct_mutex);
	if (IS_ERR(ctx)) {
		idr_destroy(&file_priv->context_idr);
		return PTR_ERR(ctx);
	}

	GEM_BUG_ON(i915_gem_context_is_kernel(ctx));

	return 0;
}