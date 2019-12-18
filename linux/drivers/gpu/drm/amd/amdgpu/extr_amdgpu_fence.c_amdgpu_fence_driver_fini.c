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
struct TYPE_2__ {int initialized; unsigned int num_fences_mask; int /*<<< orphan*/ * fences; int /*<<< orphan*/  fallback_timer; int /*<<< orphan*/  irq_type; int /*<<< orphan*/  irq_src; } ;
struct amdgpu_ring {TYPE_1__ fence_drv; int /*<<< orphan*/  sched; } ;
struct amdgpu_device {struct amdgpu_ring** rings; } ;

/* Variables and functions */
 unsigned int AMDGPU_MAX_RINGS ; 
 int /*<<< orphan*/  amdgpu_fence_driver_force_completion (struct amdgpu_ring*) ; 
 int amdgpu_fence_wait_empty (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_irq_put (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sched_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void amdgpu_fence_driver_fini(struct amdgpu_device *adev)
{
	unsigned i, j;
	int r;

	for (i = 0; i < AMDGPU_MAX_RINGS; i++) {
		struct amdgpu_ring *ring = adev->rings[i];

		if (!ring || !ring->fence_drv.initialized)
			continue;
		r = amdgpu_fence_wait_empty(ring);
		if (r) {
			/* no need to trigger GPU reset as we are unloading */
			amdgpu_fence_driver_force_completion(ring);
		}
		amdgpu_irq_put(adev, ring->fence_drv.irq_src,
			       ring->fence_drv.irq_type);
		drm_sched_fini(&ring->sched);
		del_timer_sync(&ring->fence_drv.fallback_timer);
		for (j = 0; j <= ring->fence_drv.num_fences_mask; ++j)
			dma_fence_put(ring->fence_drv.fences[j]);
		kfree(ring->fence_drv.fences);
		ring->fence_drv.fences = NULL;
		ring->fence_drv.initialized = false;
	}
}