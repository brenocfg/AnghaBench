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
struct i915_hw_ppgtt {int /*<<< orphan*/  desc_template; struct i915_hw_ppgtt* ppgtt; } ;
struct i915_gem_context {int /*<<< orphan*/  desc_template; struct i915_gem_context* ppgtt; } ;
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
struct drm_i915_file_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 struct i915_hw_ppgtt* ERR_CAST (struct i915_hw_ppgtt*) ; 
 scalar_t__ IS_ERR (struct i915_hw_ppgtt*) ; 
 int /*<<< orphan*/  PTR_ERR (struct i915_hw_ppgtt*) ; 
 scalar_t__ USES_FULL_PPGTT (struct drm_i915_private*) ; 
 struct i915_hw_ppgtt* __create_hw_context (struct drm_i915_private*,struct drm_i915_file_private*) ; 
 int /*<<< orphan*/  __destroy_hw_context (struct i915_hw_ppgtt*,struct drm_i915_file_private*) ; 
 int /*<<< orphan*/  contexts_free_first (struct drm_i915_private*) ; 
 int /*<<< orphan*/  default_desc_template (struct drm_i915_private*,struct i915_hw_ppgtt*) ; 
 struct i915_hw_ppgtt* i915_ppgtt_create (struct drm_i915_private*,struct drm_i915_file_private*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_i915_context_create (struct i915_hw_ppgtt*) ; 

__attribute__((used)) static struct i915_gem_context *
i915_gem_create_context(struct drm_i915_private *dev_priv,
			struct drm_i915_file_private *file_priv)
{
	struct i915_gem_context *ctx;

	lockdep_assert_held(&dev_priv->drm.struct_mutex);

	/* Reap the most stale context */
	contexts_free_first(dev_priv);

	ctx = __create_hw_context(dev_priv, file_priv);
	if (IS_ERR(ctx))
		return ctx;

	if (USES_FULL_PPGTT(dev_priv)) {
		struct i915_hw_ppgtt *ppgtt;

		ppgtt = i915_ppgtt_create(dev_priv, file_priv);
		if (IS_ERR(ppgtt)) {
			DRM_DEBUG_DRIVER("PPGTT setup failed (%ld)\n",
					 PTR_ERR(ppgtt));
			__destroy_hw_context(ctx, file_priv);
			return ERR_CAST(ppgtt);
		}

		ctx->ppgtt = ppgtt;
		ctx->desc_template = default_desc_template(dev_priv, ppgtt);
	}

	trace_i915_context_create(ctx);

	return ctx;
}