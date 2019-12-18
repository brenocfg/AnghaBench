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
struct msm_ringbuffer {TYPE_1__* gpu; int /*<<< orphan*/  bo; int /*<<< orphan*/  fctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  aspace; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  kfree (struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  msm_fence_context_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gem_kernel_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void msm_ringbuffer_destroy(struct msm_ringbuffer *ring)
{
	if (IS_ERR_OR_NULL(ring))
		return;

	msm_fence_context_free(ring->fctx);

	msm_gem_kernel_put(ring->bo, ring->gpu->aspace, false);

	kfree(ring);
}