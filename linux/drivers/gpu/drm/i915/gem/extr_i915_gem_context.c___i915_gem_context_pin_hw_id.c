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
struct i915_gem_context {int /*<<< orphan*/  hw_id_pin_count; int /*<<< orphan*/  hw_id_link; int /*<<< orphan*/  hw_id; struct drm_i915_private* i915; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  hw_id_list; } ;
struct drm_i915_private {TYPE_1__ contexts; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int assign_hw_id (struct drm_i915_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int i915_gem_context_is_closed (struct i915_gem_context*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int __i915_gem_context_pin_hw_id(struct i915_gem_context *ctx)
{
	struct drm_i915_private *i915 = ctx->i915;
	int err = 0;

	mutex_lock(&i915->contexts.mutex);

	GEM_BUG_ON(i915_gem_context_is_closed(ctx));

	if (list_empty(&ctx->hw_id_link)) {
		GEM_BUG_ON(atomic_read(&ctx->hw_id_pin_count));

		err = assign_hw_id(i915, &ctx->hw_id);
		if (err)
			goto out_unlock;

		list_add_tail(&ctx->hw_id_link, &i915->contexts.hw_id_list);
	}

	GEM_BUG_ON(atomic_read(&ctx->hw_id_pin_count) == ~0u);
	atomic_inc(&ctx->hw_id_pin_count);

out_unlock:
	mutex_unlock(&i915->contexts.mutex);
	return err;
}