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
struct TYPE_2__ {int /*<<< orphan*/  priority; } ;
struct i915_gem_context {TYPE_1__ sched; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 struct i915_gem_context* ERR_PTR (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  I915_USER_PRIORITY (int) ; 
 scalar_t__ IS_ERR (struct i915_gem_context*) ; 
 int /*<<< orphan*/  destroy_kernel_context (struct i915_gem_context**) ; 
 int /*<<< orphan*/  i915_gem_context_clear_bannable (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_is_kernel (struct i915_gem_context*) ; 
 int i915_gem_context_pin_hw_id (struct i915_gem_context*) ; 
 struct i915_gem_context* i915_gem_create_context (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

struct i915_gem_context *
i915_gem_context_create_kernel(struct drm_i915_private *i915, int prio)
{
	struct i915_gem_context *ctx;
	int err;

	ctx = i915_gem_create_context(i915, 0);
	if (IS_ERR(ctx))
		return ctx;

	err = i915_gem_context_pin_hw_id(ctx);
	if (err) {
		destroy_kernel_context(&ctx);
		return ERR_PTR(err);
	}

	i915_gem_context_clear_bannable(ctx);
	ctx->sched.priority = I915_USER_PRIORITY(prio);

	GEM_BUG_ON(!i915_gem_context_is_kernel(ctx));

	return ctx;
}