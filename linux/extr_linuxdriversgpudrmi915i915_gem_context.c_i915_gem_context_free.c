#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_context {TYPE_2__* ops; } ;
struct i915_gem_context {int /*<<< orphan*/  hw_id; TYPE_4__* i915; int /*<<< orphan*/  link; int /*<<< orphan*/  pid; int /*<<< orphan*/  name; struct intel_context* __engine; int /*<<< orphan*/  ppgtt; } ;
struct TYPE_7__ {int /*<<< orphan*/  hw_ida; } ;
struct TYPE_5__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_8__ {TYPE_3__ contexts; TYPE_1__ drm; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* destroy ) (struct intel_context*) ;} ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct intel_context*) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  i915_gem_context_is_closed (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_ppgtt_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct i915_gem_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  stub1 (struct intel_context*) ; 

__attribute__((used)) static void i915_gem_context_free(struct i915_gem_context *ctx)
{
	unsigned int n;

	lockdep_assert_held(&ctx->i915->drm.struct_mutex);
	GEM_BUG_ON(!i915_gem_context_is_closed(ctx));

	i915_ppgtt_put(ctx->ppgtt);

	for (n = 0; n < ARRAY_SIZE(ctx->__engine); n++) {
		struct intel_context *ce = &ctx->__engine[n];

		if (ce->ops)
			ce->ops->destroy(ce);
	}

	kfree(ctx->name);
	put_pid(ctx->pid);

	list_del(&ctx->link);

	ida_simple_remove(&ctx->i915->contexts.hw_ida, ctx->hw_id);
	kfree_rcu(ctx, rcu);
}