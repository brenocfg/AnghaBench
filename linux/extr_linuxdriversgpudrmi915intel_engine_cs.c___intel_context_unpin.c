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
struct intel_engine_cs {int dummy; } ;
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_context_unpin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_intel_context (struct i915_gem_context*,struct intel_engine_cs*) ; 

__attribute__((used)) static void __intel_context_unpin(struct i915_gem_context *ctx,
				  struct intel_engine_cs *engine)
{
	intel_context_unpin(to_intel_context(ctx, engine));
}