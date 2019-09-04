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
struct intel_engine_cs {int /*<<< orphan*/  i915; } ;
struct i915_request {int dummy; } ;
typedef  struct i915_request i915_gem_context ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct i915_request*) ; 
 int PTR_ERR (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_request*) ; 
 struct i915_request* i915_request_alloc (struct intel_engine_cs*,struct i915_request*) ; 
 struct i915_request* kernel_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_context_close (struct i915_request*) ; 

__attribute__((used)) static int switch_to_scratch_context(struct intel_engine_cs *engine)
{
	struct i915_gem_context *ctx;
	struct i915_request *rq;

	ctx = kernel_context(engine->i915);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	rq = i915_request_alloc(engine, ctx);
	kernel_context_close(ctx);
	if (IS_ERR(rq))
		return PTR_ERR(rq);

	i915_request_add(rq);

	return 0;
}