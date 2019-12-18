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
struct dma_fence {int dummy; } ;
struct amdgpu_ring {TYPE_1__* funcs; TYPE_2__* adev; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_4__ {int /*<<< orphan*/  gpu_reset_counter; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* soft_recovery ) (struct amdgpu_ring*,unsigned int) ;} ;

/* Variables and functions */
 scalar_t__ amdgpu_sriov_vf (TYPE_2__*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_ring*,unsigned int) ; 

bool amdgpu_ring_soft_recovery(struct amdgpu_ring *ring, unsigned int vmid,
			       struct dma_fence *fence)
{
	ktime_t deadline = ktime_add_us(ktime_get(), 10000);

	if (amdgpu_sriov_vf(ring->adev) || !ring->funcs->soft_recovery || !fence)
		return false;

	atomic_inc(&ring->adev->gpu_reset_counter);
	while (!dma_fence_is_signaled(fence) &&
	       ktime_to_ns(ktime_sub(deadline, ktime_get())) > 0)
		ring->funcs->soft_recovery(ring, vmid);

	return dma_fence_is_signaled(fence);
}