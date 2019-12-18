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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct amdgpu_ring {scalar_t__ trail_seq; int /*<<< orphan*/  idx; int /*<<< orphan*/ * trail_fence_cpu_addr; int /*<<< orphan*/  trail_fence_gpu_addr; struct amdgpu_device* adev; } ;
struct amdgpu_device {int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  amdgpu_ring_commit (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_set_preempt_cond_exec (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  amdgpu_sdma_get_index_from_ring (struct amdgpu_ring*,scalar_t__*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSDMA0_GFX_PREEMPT ; 
 int /*<<< orphan*/  mmSDMA1_GFX_PREEMPT ; 
 int /*<<< orphan*/  sdma_v5_0_ring_emit_fence (struct amdgpu_ring*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sdma_v5_0_ring_preempt_ib(struct amdgpu_ring *ring)
{
	int i, r = 0;
	struct amdgpu_device *adev = ring->adev;
	u32 index = 0;
	u64 sdma_gfx_preempt;

	amdgpu_sdma_get_index_from_ring(ring, &index);
	if (index == 0)
		sdma_gfx_preempt = mmSDMA0_GFX_PREEMPT;
	else
		sdma_gfx_preempt = mmSDMA1_GFX_PREEMPT;

	/* assert preemption condition */
	amdgpu_ring_set_preempt_cond_exec(ring, false);

	/* emit the trailing fence */
	ring->trail_seq += 1;
	amdgpu_ring_alloc(ring, 10);
	sdma_v5_0_ring_emit_fence(ring, ring->trail_fence_gpu_addr,
				  ring->trail_seq, 0);
	amdgpu_ring_commit(ring);

	/* assert IB preemption */
	WREG32(sdma_gfx_preempt, 1);

	/* poll the trailing fence */
	for (i = 0; i < adev->usec_timeout; i++) {
		if (ring->trail_seq ==
		    le32_to_cpu(*(ring->trail_fence_cpu_addr)))
			break;
		udelay(1);
	}

	if (i >= adev->usec_timeout) {
		r = -EINVAL;
		DRM_ERROR("ring %d failed to be preempted\n", ring->idx);
	}

	/* deassert IB preemption */
	WREG32(sdma_gfx_preempt, 0);

	/* deassert the preemption condition */
	amdgpu_ring_set_preempt_cond_exec(ring, true);
	return r;
}