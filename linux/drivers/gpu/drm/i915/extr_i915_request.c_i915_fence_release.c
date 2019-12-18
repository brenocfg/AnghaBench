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
struct i915_request {int /*<<< orphan*/  semaphore; int /*<<< orphan*/  submit; } ;
struct dma_fence {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  slab_requests; } ;

/* Variables and functions */
 TYPE_1__ global ; 
 int /*<<< orphan*/  i915_sw_fence_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct i915_request*) ; 
 struct i915_request* to_request (struct dma_fence*) ; 

__attribute__((used)) static void i915_fence_release(struct dma_fence *fence)
{
	struct i915_request *rq = to_request(fence);

	/*
	 * The request is put onto a RCU freelist (i.e. the address
	 * is immediately reused), mark the fences as being freed now.
	 * Otherwise the debugobjects for the fences are only marked as
	 * freed when the slab cache itself is freed, and so we would get
	 * caught trying to reuse dead objects.
	 */
	i915_sw_fence_fini(&rq->submit);
	i915_sw_fence_fini(&rq->semaphore);

	kmem_cache_free(global.slab_requests, rq);
}