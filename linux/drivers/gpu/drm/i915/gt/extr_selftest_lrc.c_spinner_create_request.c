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
typedef  int /*<<< orphan*/  u32 ;
struct intel_engine_cs {int /*<<< orphan*/  legacy_idx; } ;
struct intel_context {int dummy; } ;
struct igt_spinner {int dummy; } ;
struct i915_request {int dummy; } ;
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 struct i915_request* ERR_CAST (struct intel_context*) ; 
 scalar_t__ IS_ERR (struct intel_context*) ; 
 struct intel_context* i915_gem_context_get_engine (struct i915_gem_context*,int /*<<< orphan*/ ) ; 
 struct i915_request* igt_spinner_create_request (struct igt_spinner*,struct intel_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_context_put (struct intel_context*) ; 

__attribute__((used)) static struct i915_request *
spinner_create_request(struct igt_spinner *spin,
		       struct i915_gem_context *ctx,
		       struct intel_engine_cs *engine,
		       u32 arb)
{
	struct intel_context *ce;
	struct i915_request *rq;

	ce = i915_gem_context_get_engine(ctx, engine->legacy_idx);
	if (IS_ERR(ce))
		return ERR_CAST(ce);

	rq = igt_spinner_create_request(spin, ce, arb);
	intel_context_put(ce);
	return rq;
}