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
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  context_close (struct i915_gem_context*) ; 
 int /*<<< orphan*/  fetch_and_zero (struct i915_gem_context**) ; 
 int /*<<< orphan*/  i915_gem_context_free (struct i915_gem_context*) ; 
 struct i915_gem_context* i915_gem_context_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_context_is_kernel (struct i915_gem_context*) ; 

__attribute__((used)) static void
destroy_kernel_context(struct i915_gem_context **ctxp)
{
	struct i915_gem_context *ctx;

	/* Keep the context ref so that we can free it immediately ourselves */
	ctx = i915_gem_context_get(fetch_and_zero(ctxp));
	GEM_BUG_ON(!i915_gem_context_is_kernel(ctx));

	context_close(ctx);
	i915_gem_context_free(ctx);
}