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
struct intel_engine_cs {int /*<<< orphan*/  buffer; } ;
struct intel_context {int /*<<< orphan*/ * ops; int /*<<< orphan*/  ring; int /*<<< orphan*/  pin_count; } ;
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_context_get (struct i915_gem_context*) ; 
 int /*<<< orphan*/  mock_context_ops ; 
 struct intel_context* to_intel_context (struct i915_gem_context*,struct intel_engine_cs*) ; 

__attribute__((used)) static struct intel_context *
mock_context_pin(struct intel_engine_cs *engine,
		 struct i915_gem_context *ctx)
{
	struct intel_context *ce = to_intel_context(ctx, engine);

	if (!ce->pin_count++) {
		i915_gem_context_get(ctx);
		ce->ring = engine->buffer;
		ce->ops = &mock_context_ops;
	}

	return ce;
}