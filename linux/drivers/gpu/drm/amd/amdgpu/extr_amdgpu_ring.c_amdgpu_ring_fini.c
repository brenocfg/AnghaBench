#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ready; } ;
struct amdgpu_ring {size_t idx; TYPE_2__* adev; scalar_t__ me; int /*<<< orphan*/ * vmid_wait; int /*<<< orphan*/  ring; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  ring_obj; int /*<<< orphan*/  fence_offs; int /*<<< orphan*/  cond_exe_offs; int /*<<< orphan*/  wptr_offs; int /*<<< orphan*/  rptr_offs; TYPE_1__ sched; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_debugfs_ring_fini (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_device_wb_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 

void amdgpu_ring_fini(struct amdgpu_ring *ring)
{
	ring->sched.ready = false;

	/* Not to finish a ring which is not initialized */
	if (!(ring->adev) || !(ring->adev->rings[ring->idx]))
		return;

	amdgpu_device_wb_free(ring->adev, ring->rptr_offs);
	amdgpu_device_wb_free(ring->adev, ring->wptr_offs);

	amdgpu_device_wb_free(ring->adev, ring->cond_exe_offs);
	amdgpu_device_wb_free(ring->adev, ring->fence_offs);

	amdgpu_bo_free_kernel(&ring->ring_obj,
			      &ring->gpu_addr,
			      (void **)&ring->ring);

	amdgpu_debugfs_ring_fini(ring);

	dma_fence_put(ring->vmid_wait);
	ring->vmid_wait = NULL;
	ring->me = 0;

	ring->adev->rings[ring->idx] = NULL;
}