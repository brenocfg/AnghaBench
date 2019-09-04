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
struct spinner {int dummy; } ;
struct intel_engine_cs {int dummy; } ;
struct i915_request {int dummy; } ;
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 struct i915_request* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct i915_request*) ; 
 int emit_recurse_batch (struct spinner*,struct i915_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_request*) ; 
 struct i915_request* i915_request_alloc (struct intel_engine_cs*,struct i915_gem_context*) ; 

__attribute__((used)) static struct i915_request *
spinner_create_request(struct spinner *spin,
		       struct i915_gem_context *ctx,
		       struct intel_engine_cs *engine,
		       u32 arbitration_command)
{
	struct i915_request *rq;
	int err;

	rq = i915_request_alloc(engine, ctx);
	if (IS_ERR(rq))
		return rq;

	err = emit_recurse_batch(spin, rq, arbitration_command);
	if (err) {
		i915_request_add(rq);
		return ERR_PTR(err);
	}

	return rq;
}