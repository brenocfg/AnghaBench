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
struct intel_engine_cs {size_t id; } ;
struct intel_context {int dummy; } ;
struct i915_gem_context {struct intel_context* __engine; } ;

/* Variables and functions */

__attribute__((used)) static inline struct intel_context *
to_intel_context(struct i915_gem_context *ctx,
		 const struct intel_engine_cs *engine)
{
	return &ctx->__engine[engine->id];
}