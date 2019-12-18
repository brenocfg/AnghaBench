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
struct intel_engine_cs {int /*<<< orphan*/  legacy_idx; } ;
struct intel_context {int dummy; } ;
struct i915_request {int dummy; } ;
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 struct i915_request* ERR_CAST (struct intel_context*) ; 
 scalar_t__ IS_ERR (struct intel_context*) ; 
 struct intel_context* i915_gem_context_get_engine (struct i915_gem_context*,int /*<<< orphan*/ ) ; 
 struct i915_request* intel_context_create_request (struct intel_context*) ; 
 int /*<<< orphan*/  intel_context_put (struct intel_context*) ; 

struct i915_request *
igt_request_alloc(struct i915_gem_context *ctx, struct intel_engine_cs *engine)
{
	struct intel_context *ce;
	struct i915_request *rq;

	/*
	 * Pinning the contexts may generate requests in order to acquire
	 * GGTT space, so do this first before we reserve a seqno for
	 * ourselves.
	 */
	ce = i915_gem_context_get_engine(ctx, engine->legacy_idx);
	if (IS_ERR(ce))
		return ERR_CAST(ce);

	rq = intel_context_create_request(ce);
	intel_context_put(ce);

	return rq;
}