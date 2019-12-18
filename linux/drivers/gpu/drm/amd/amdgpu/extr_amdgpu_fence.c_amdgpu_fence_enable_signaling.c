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
struct dma_fence {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fallback_timer; } ;
struct amdgpu_ring {int /*<<< orphan*/  idx; TYPE_1__ fence_drv; } ;
struct amdgpu_fence {int /*<<< orphan*/  base; struct amdgpu_ring* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_TRACE (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_fence_schedule_fallback (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
 struct amdgpu_fence* to_amdgpu_fence (struct dma_fence*) ; 

__attribute__((used)) static bool amdgpu_fence_enable_signaling(struct dma_fence *f)
{
	struct amdgpu_fence *fence = to_amdgpu_fence(f);
	struct amdgpu_ring *ring = fence->ring;

	if (!timer_pending(&ring->fence_drv.fallback_timer))
		amdgpu_fence_schedule_fallback(ring);

	DMA_FENCE_TRACE(&fence->base, "armed on ring %i!\n", ring->idx);

	return true;
}