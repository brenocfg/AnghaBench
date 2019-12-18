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
struct i915_request {int /*<<< orphan*/  fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  dma_fence_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_request_mark_complete (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_signaled (struct i915_request*) ; 

__attribute__((used)) static void mark_eio(struct i915_request *rq)
{
	if (!i915_request_signaled(rq))
		dma_fence_set_error(&rq->fence, -EIO);
	i915_request_mark_complete(rq);
}