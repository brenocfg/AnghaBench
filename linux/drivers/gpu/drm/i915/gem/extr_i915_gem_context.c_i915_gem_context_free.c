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
struct i915_gem_context {int /*<<< orphan*/  mutex; int /*<<< orphan*/  link; int /*<<< orphan*/  pid; int /*<<< orphan*/  name; scalar_t__ timeline; int /*<<< orphan*/  jump_whitelist; int /*<<< orphan*/  engines_mutex; int /*<<< orphan*/  engines; scalar_t__ vm; TYPE_2__* i915; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  free_engines (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_context_is_closed (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_vm_put (scalar_t__) ; 
 int /*<<< orphan*/  intel_timeline_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct i915_gem_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_hw_id (struct i915_gem_context*) ; 

__attribute__((used)) static void i915_gem_context_free(struct i915_gem_context *ctx)
{
	lockdep_assert_held(&ctx->i915->drm.struct_mutex);
	GEM_BUG_ON(!i915_gem_context_is_closed(ctx));

	release_hw_id(ctx);
	if (ctx->vm)
		i915_vm_put(ctx->vm);

	free_engines(rcu_access_pointer(ctx->engines));
	mutex_destroy(&ctx->engines_mutex);

	kfree(ctx->jump_whitelist);

	if (ctx->timeline)
		intel_timeline_put(ctx->timeline);

	kfree(ctx->name);
	put_pid(ctx->pid);

	list_del(&ctx->link);
	mutex_destroy(&ctx->mutex);

	kfree_rcu(ctx, rcu);
}