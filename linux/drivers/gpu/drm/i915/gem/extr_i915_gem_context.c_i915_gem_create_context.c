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
struct intel_timeline {int /*<<< orphan*/  vm; } ;
struct i915_ppgtt {int /*<<< orphan*/  vm; } ;
struct i915_gem_context {int /*<<< orphan*/  vm; } ;
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {int /*<<< orphan*/  gt; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 struct intel_timeline* ERR_CAST (struct intel_timeline*) ; 
 struct intel_timeline* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAS_EXECLISTS (struct drm_i915_private*) ; 
 scalar_t__ HAS_FULL_PPGTT (struct drm_i915_private*) ; 
 unsigned int I915_CONTEXT_CREATE_FLAGS_SINGLE_TIMELINE ; 
 scalar_t__ IS_ERR (struct intel_timeline*) ; 
 int /*<<< orphan*/  PTR_ERR (struct intel_timeline*) ; 
 int /*<<< orphan*/  __assign_ppgtt (struct intel_timeline*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __assign_timeline (struct intel_timeline*,struct intel_timeline*) ; 
 struct intel_timeline* __create_context (struct drm_i915_private*) ; 
 int /*<<< orphan*/  context_close (struct intel_timeline*) ; 
 int /*<<< orphan*/  contexts_free_first (struct drm_i915_private*) ; 
 struct intel_timeline* i915_ppgtt_create (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_vm_put (int /*<<< orphan*/ *) ; 
 struct intel_timeline* intel_timeline_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_timeline_put (struct intel_timeline*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_i915_context_create (struct intel_timeline*) ; 

__attribute__((used)) static struct i915_gem_context *
i915_gem_create_context(struct drm_i915_private *dev_priv, unsigned int flags)
{
	struct i915_gem_context *ctx;

	lockdep_assert_held(&dev_priv->drm.struct_mutex);

	if (flags & I915_CONTEXT_CREATE_FLAGS_SINGLE_TIMELINE &&
	    !HAS_EXECLISTS(dev_priv))
		return ERR_PTR(-EINVAL);

	/* Reap the most stale context */
	contexts_free_first(dev_priv);

	ctx = __create_context(dev_priv);
	if (IS_ERR(ctx))
		return ctx;

	if (HAS_FULL_PPGTT(dev_priv)) {
		struct i915_ppgtt *ppgtt;

		ppgtt = i915_ppgtt_create(dev_priv);
		if (IS_ERR(ppgtt)) {
			DRM_DEBUG_DRIVER("PPGTT setup failed (%ld)\n",
					 PTR_ERR(ppgtt));
			context_close(ctx);
			return ERR_CAST(ppgtt);
		}

		__assign_ppgtt(ctx, &ppgtt->vm);
		i915_vm_put(&ppgtt->vm);
	}

	if (flags & I915_CONTEXT_CREATE_FLAGS_SINGLE_TIMELINE) {
		struct intel_timeline *timeline;

		timeline = intel_timeline_create(&dev_priv->gt, NULL);
		if (IS_ERR(timeline)) {
			context_close(ctx);
			return ERR_CAST(timeline);
		}

		__assign_timeline(ctx, timeline);
		intel_timeline_put(timeline);
	}

	trace_i915_context_create(ctx);

	return ctx;
}