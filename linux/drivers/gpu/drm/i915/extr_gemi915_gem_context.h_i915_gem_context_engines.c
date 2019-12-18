#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct i915_gem_engines {int dummy; } ;
struct i915_gem_context {int /*<<< orphan*/  engines_mutex; int /*<<< orphan*/  engines; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct i915_gem_engines* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct i915_gem_engines *
i915_gem_context_engines(struct i915_gem_context *ctx)
{
	return rcu_dereference_protected(ctx->engines,
					 lockdep_is_held(&ctx->engines_mutex));
}