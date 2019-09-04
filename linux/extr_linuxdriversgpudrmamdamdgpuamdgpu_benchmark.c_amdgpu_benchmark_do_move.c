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
typedef  int /*<<< orphan*/  uint64_t ;
struct dma_fence {int dummy; } ;
struct amdgpu_ring {int dummy; } ;
struct TYPE_2__ {struct amdgpu_ring* buffer_funcs_ring; } ;
struct amdgpu_device {TYPE_1__ mman; } ;

/* Variables and functions */
 int amdgpu_copy_buffer (struct amdgpu_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,struct dma_fence**,int,int) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int dma_fence_wait (struct dma_fence*,int) ; 
 unsigned long jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 

__attribute__((used)) static int amdgpu_benchmark_do_move(struct amdgpu_device *adev, unsigned size,
				    uint64_t saddr, uint64_t daddr, int n)
{
	unsigned long start_jiffies;
	unsigned long end_jiffies;
	struct dma_fence *fence = NULL;
	int i, r;

	start_jiffies = jiffies;
	for (i = 0; i < n; i++) {
		struct amdgpu_ring *ring = adev->mman.buffer_funcs_ring;
		r = amdgpu_copy_buffer(ring, saddr, daddr, size, NULL, &fence,
				       false, false);
		if (r)
			goto exit_do_move;
		r = dma_fence_wait(fence, false);
		if (r)
			goto exit_do_move;
		dma_fence_put(fence);
	}
	end_jiffies = jiffies;
	r = jiffies_to_msecs(end_jiffies - start_jiffies);

exit_do_move:
	if (fence)
		dma_fence_put(fence);
	return r;
}