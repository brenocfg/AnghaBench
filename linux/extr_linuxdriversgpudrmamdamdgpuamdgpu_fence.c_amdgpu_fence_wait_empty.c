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
typedef  size_t uint64_t ;
struct dma_fence {int dummy; } ;
struct TYPE_2__ {size_t num_fences_mask; struct dma_fence** fences; int /*<<< orphan*/  sync_seq; } ;
struct amdgpu_ring {TYPE_1__ fence_drv; } ;

/* Variables and functions */
 size_t READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_get_rcu (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int dma_fence_wait (struct dma_fence*,int) ; 
 struct dma_fence* rcu_dereference (struct dma_fence*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int amdgpu_fence_wait_empty(struct amdgpu_ring *ring)
{
	uint64_t seq = READ_ONCE(ring->fence_drv.sync_seq);
	struct dma_fence *fence, **ptr;
	int r;

	if (!seq)
		return 0;

	ptr = &ring->fence_drv.fences[seq & ring->fence_drv.num_fences_mask];
	rcu_read_lock();
	fence = rcu_dereference(*ptr);
	if (!fence || !dma_fence_get_rcu(fence)) {
		rcu_read_unlock();
		return 0;
	}
	rcu_read_unlock();

	r = dma_fence_wait(fence, false);
	dma_fence_put(fence);
	return r;
}