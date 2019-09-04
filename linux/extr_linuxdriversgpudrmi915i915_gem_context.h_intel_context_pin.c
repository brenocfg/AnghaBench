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
struct intel_engine_cs {struct intel_context* (* context_pin ) (struct intel_engine_cs*,struct i915_gem_context*) ;} ;
struct intel_context {int dummy; } ;
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 struct intel_context* stub1 (struct intel_engine_cs*,struct i915_gem_context*) ; 

__attribute__((used)) static inline struct intel_context *
intel_context_pin(struct i915_gem_context *ctx, struct intel_engine_cs *engine)
{
	return engine->context_pin(engine, ctx);
}