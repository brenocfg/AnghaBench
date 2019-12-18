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
struct i915_gem_context {int /*<<< orphan*/  hw_id_link; int /*<<< orphan*/  hw_id; struct drm_i915_private* i915; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  hw_ida; } ;
struct drm_i915_private {TYPE_1__ contexts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_hw_id(struct i915_gem_context *ctx)
{
	struct drm_i915_private *i915 = ctx->i915;

	if (list_empty(&ctx->hw_id_link))
		return;

	mutex_lock(&i915->contexts.mutex);
	if (!list_empty(&ctx->hw_id_link)) {
		ida_simple_remove(&i915->contexts.hw_ida, ctx->hw_id);
		list_del_init(&ctx->hw_id_link);
	}
	mutex_unlock(&i915->contexts.mutex);
}