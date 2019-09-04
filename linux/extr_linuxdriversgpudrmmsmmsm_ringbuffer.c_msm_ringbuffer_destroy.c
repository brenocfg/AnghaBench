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
struct msm_ringbuffer {scalar_t__ bo; TYPE_1__* gpu; int /*<<< orphan*/  fctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  aspace; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  msm_fence_context_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gem_put_iova (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gem_put_vaddr (scalar_t__) ; 

void msm_ringbuffer_destroy(struct msm_ringbuffer *ring)
{
	if (IS_ERR_OR_NULL(ring))
		return;

	msm_fence_context_free(ring->fctx);

	if (ring->bo) {
		msm_gem_put_iova(ring->bo, ring->gpu->aspace);
		msm_gem_put_vaddr(ring->bo);
		drm_gem_object_put_unlocked(ring->bo);
	}
	kfree(ring);
}