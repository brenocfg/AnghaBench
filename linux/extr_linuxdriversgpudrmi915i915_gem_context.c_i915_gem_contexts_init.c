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
struct i915_gem_context {struct i915_gem_context* hw_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw_ida; int /*<<< orphan*/  free_list; int /*<<< orphan*/  free_work; int /*<<< orphan*/  list; } ;
struct drm_i915_private {struct i915_gem_context* preempt_context; struct i915_gem_context* kernel_context; TYPE_1__ contexts; } ;
struct TYPE_4__ {scalar_t__ has_logical_contexts; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 TYPE_2__* DRIVER_CAPS (struct drm_i915_private*) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GEM_BUG_ON (struct i915_gem_context*) ; 
 scalar_t__ GEN11_MAX_CONTEXT_HW_ID ; 
 scalar_t__ I915_PRIORITY_MIN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ IS_ERR (struct i915_gem_context*) ; 
 scalar_t__ MAX_CONTEXT_HW_ID ; 
 int PTR_ERR (struct i915_gem_context*) ; 
 int /*<<< orphan*/  contexts_free_worker ; 
 struct i915_gem_context* i915_gem_context_create_kernel (struct drm_i915_private*,scalar_t__) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_llist_head (int /*<<< orphan*/ *) ; 
 int intel_ctx_workarounds_init (struct drm_i915_private*) ; 
 scalar_t__ needs_preempt_context (struct drm_i915_private*) ; 

int i915_gem_contexts_init(struct drm_i915_private *dev_priv)
{
	struct i915_gem_context *ctx;
	int ret;

	/* Reassure ourselves we are only called once */
	GEM_BUG_ON(dev_priv->kernel_context);
	GEM_BUG_ON(dev_priv->preempt_context);

	ret = intel_ctx_workarounds_init(dev_priv);
	if (ret)
		return ret;

	INIT_LIST_HEAD(&dev_priv->contexts.list);
	INIT_WORK(&dev_priv->contexts.free_work, contexts_free_worker);
	init_llist_head(&dev_priv->contexts.free_list);

	/* Using the simple ida interface, the max is limited by sizeof(int) */
	BUILD_BUG_ON(MAX_CONTEXT_HW_ID > INT_MAX);
	BUILD_BUG_ON(GEN11_MAX_CONTEXT_HW_ID > INT_MAX);
	ida_init(&dev_priv->contexts.hw_ida);

	/* lowest priority; idle task */
	ctx = i915_gem_context_create_kernel(dev_priv, I915_PRIORITY_MIN);
	if (IS_ERR(ctx)) {
		DRM_ERROR("Failed to create default global context\n");
		return PTR_ERR(ctx);
	}
	/*
	 * For easy recognisablity, we want the kernel context to be 0 and then
	 * all user contexts will have non-zero hw_id.
	 */
	GEM_BUG_ON(ctx->hw_id);
	dev_priv->kernel_context = ctx;

	/* highest priority; preempting task */
	if (needs_preempt_context(dev_priv)) {
		ctx = i915_gem_context_create_kernel(dev_priv, INT_MAX);
		if (!IS_ERR(ctx))
			dev_priv->preempt_context = ctx;
		else
			DRM_ERROR("Failed to create preempt context; disabling preemption\n");
	}

	DRM_DEBUG_DRIVER("%s context support initialized\n",
			 DRIVER_CAPS(dev_priv)->has_logical_contexts ?
			 "logical" : "fake");
	return 0;
}