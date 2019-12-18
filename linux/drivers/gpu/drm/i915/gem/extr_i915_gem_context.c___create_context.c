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
struct i915_gem_engines {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  priority; } ;
struct i915_gem_context {scalar_t__ jump_whitelist_cmds; int /*<<< orphan*/ * jump_whitelist; scalar_t__* hang_timestamp; int /*<<< orphan*/  remap_slice; int /*<<< orphan*/  hw_id_link; int /*<<< orphan*/  handles_vma; int /*<<< orphan*/  engines; int /*<<< orphan*/  engines_mutex; int /*<<< orphan*/  mutex; TYPE_2__ sched; struct drm_i915_private* i915; int /*<<< orphan*/  link; int /*<<< orphan*/  ref; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
struct drm_i915_private {TYPE_1__ contexts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_L3_SLICES (struct drm_i915_private*) ; 
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ CONTEXT_FAST_HANG_JIFFIES ; 
 int ENOMEM ; 
 struct i915_gem_context* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I915_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  I915_USER_PRIORITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct i915_gem_engines*) ; 
 int PTR_ERR (struct i915_gem_engines*) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct i915_gem_engines*) ; 
 struct i915_gem_engines* default_engines (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_bannable (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_recoverable (struct i915_gem_context*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct i915_gem_context*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct i915_gem_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct i915_gem_context *
__create_context(struct drm_i915_private *i915)
{
	struct i915_gem_context *ctx;
	struct i915_gem_engines *e;
	int err;
	int i;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return ERR_PTR(-ENOMEM);

	kref_init(&ctx->ref);
	list_add_tail(&ctx->link, &i915->contexts.list);
	ctx->i915 = i915;
	ctx->sched.priority = I915_USER_PRIORITY(I915_PRIORITY_NORMAL);
	mutex_init(&ctx->mutex);

	mutex_init(&ctx->engines_mutex);
	e = default_engines(ctx);
	if (IS_ERR(e)) {
		err = PTR_ERR(e);
		goto err_free;
	}
	RCU_INIT_POINTER(ctx->engines, e);

	INIT_RADIX_TREE(&ctx->handles_vma, GFP_KERNEL);
	INIT_LIST_HEAD(&ctx->hw_id_link);

	/* NB: Mark all slices as needing a remap so that when the context first
	 * loads it will restore whatever remap state already exists. If there
	 * is no remap info, it will be a NOP. */
	ctx->remap_slice = ALL_L3_SLICES(i915);

	i915_gem_context_set_bannable(ctx);
	i915_gem_context_set_recoverable(ctx);

	for (i = 0; i < ARRAY_SIZE(ctx->hang_timestamp); i++)
		ctx->hang_timestamp[i] = jiffies - CONTEXT_FAST_HANG_JIFFIES;

	ctx->jump_whitelist = NULL;
	ctx->jump_whitelist_cmds = 0;

	return ctx;

err_free:
	kfree(ctx);
	return ERR_PTR(err);
}