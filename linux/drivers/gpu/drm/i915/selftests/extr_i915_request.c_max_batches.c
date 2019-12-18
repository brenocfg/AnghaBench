#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_engine_cs {int dummy; } ;
struct i915_request {int reserved_space; int head; TYPE_1__* ring; } ;
struct i915_gem_context {int /*<<< orphan*/  i915; } ;
struct TYPE_2__ {int size; int emit; } ;

/* Variables and functions */
 scalar_t__ HAS_EXECLISTS (int /*<<< orphan*/ ) ; 
 int INT_MAX ; 
 scalar_t__ IS_ERR (struct i915_request*) ; 
 int PTR_ERR (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_request*) ; 
 struct i915_request* igt_request_alloc (struct i915_gem_context*,struct intel_engine_cs*) ; 

__attribute__((used)) static int
max_batches(struct i915_gem_context *ctx, struct intel_engine_cs *engine)
{
	struct i915_request *rq;
	int ret;

	/*
	 * Before execlists, all contexts share the same ringbuffer. With
	 * execlists, each context/engine has a separate ringbuffer and
	 * for the purposes of this test, inexhaustible.
	 *
	 * For the global ringbuffer though, we have to be very careful
	 * that we do not wrap while preventing the execution of requests
	 * with a unsignaled fence.
	 */
	if (HAS_EXECLISTS(ctx->i915))
		return INT_MAX;

	rq = igt_request_alloc(ctx, engine);
	if (IS_ERR(rq)) {
		ret = PTR_ERR(rq);
	} else {
		int sz;

		ret = rq->ring->size - rq->reserved_space;
		i915_request_add(rq);

		sz = rq->ring->emit - rq->head;
		if (sz < 0)
			sz += rq->ring->size;
		ret /= sz;
		ret /= 2; /* leave half spare, in case of emergency! */
	}

	return ret;
}