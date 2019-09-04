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
struct intel_rps_client {int dummy; } ;
struct i915_request {int /*<<< orphan*/  i915; } ;
struct dma_fence {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_FENCE_FLAG_SIGNALED_BIT ; 
 int I915_WAIT_INTERRUPTIBLE ; 
 unsigned int I915_WAIT_LOCKED ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_is_i915 (struct dma_fence*) ; 
 long dma_fence_wait_timeout (struct dma_fence*,unsigned int,long) ; 
 int /*<<< orphan*/  gen6_rps_boost (struct i915_request*,struct intel_rps_client*) ; 
 scalar_t__ i915_request_completed (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_retire_upto (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_started (struct i915_request*) ; 
 long i915_request_wait (struct i915_request*,unsigned int,long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct i915_request* to_request (struct dma_fence*) ; 

__attribute__((used)) static long
i915_gem_object_wait_fence(struct dma_fence *fence,
			   unsigned int flags,
			   long timeout,
			   struct intel_rps_client *rps_client)
{
	struct i915_request *rq;

	BUILD_BUG_ON(I915_WAIT_INTERRUPTIBLE != 0x1);

	if (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags))
		return timeout;

	if (!dma_fence_is_i915(fence))
		return dma_fence_wait_timeout(fence,
					      flags & I915_WAIT_INTERRUPTIBLE,
					      timeout);

	rq = to_request(fence);
	if (i915_request_completed(rq))
		goto out;

	/*
	 * This client is about to stall waiting for the GPU. In many cases
	 * this is undesirable and limits the throughput of the system, as
	 * many clients cannot continue processing user input/output whilst
	 * blocked. RPS autotuning may take tens of milliseconds to respond
	 * to the GPU load and thus incurs additional latency for the client.
	 * We can circumvent that by promoting the GPU frequency to maximum
	 * before we wait. This makes the GPU throttle up much more quickly
	 * (good for benchmarks and user experience, e.g. window animations),
	 * but at a cost of spending more power processing the workload
	 * (bad for battery). Not all clients even want their results
	 * immediately and for them we should just let the GPU select its own
	 * frequency to maximise efficiency. To prevent a single client from
	 * forcing the clocks too high for the whole system, we only allow
	 * each client to waitboost once in a busy period.
	 */
	if (rps_client && !i915_request_started(rq)) {
		if (INTEL_GEN(rq->i915) >= 6)
			gen6_rps_boost(rq, rps_client);
	}

	timeout = i915_request_wait(rq, flags, timeout);

out:
	if (flags & I915_WAIT_LOCKED && i915_request_completed(rq))
		i915_request_retire_upto(rq);

	return timeout;
}