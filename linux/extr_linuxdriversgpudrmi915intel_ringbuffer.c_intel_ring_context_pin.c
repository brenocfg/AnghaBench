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
struct intel_engine_cs {int dummy; } ;
struct intel_context {int /*<<< orphan*/ * ops; int /*<<< orphan*/  pin_count; } ;
struct i915_gem_context {TYPE_2__* i915; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 struct intel_context* __ring_context_pin (struct intel_engine_cs*,struct i915_gem_context*,struct intel_context*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_context_ops ; 
 struct intel_context* to_intel_context (struct i915_gem_context*,struct intel_engine_cs*) ; 

__attribute__((used)) static struct intel_context *
intel_ring_context_pin(struct intel_engine_cs *engine,
		       struct i915_gem_context *ctx)
{
	struct intel_context *ce = to_intel_context(ctx, engine);

	lockdep_assert_held(&ctx->i915->drm.struct_mutex);

	if (likely(ce->pin_count++))
		return ce;
	GEM_BUG_ON(!ce->pin_count); /* no overflow please! */

	ce->ops = &ring_context_ops;

	return __ring_context_pin(engine, ctx, ce);
}