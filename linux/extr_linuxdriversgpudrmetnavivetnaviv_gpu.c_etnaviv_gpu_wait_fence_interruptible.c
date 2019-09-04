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
typedef  int /*<<< orphan*/  u32 ;
struct timespec {int dummy; } ;
struct etnaviv_gpu {int /*<<< orphan*/  fence_idr; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ERESTARTSYS ; 
 int ETIMEDOUT ; 
 struct dma_fence* dma_fence_get_rcu (struct dma_fence*) ; 
 scalar_t__ dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int dma_fence_wait_timeout (struct dma_fence*,int,unsigned long) ; 
 unsigned long etnaviv_timeout_to_jiffies (struct timespec*) ; 
 struct dma_fence* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int etnaviv_gpu_wait_fence_interruptible(struct etnaviv_gpu *gpu,
	u32 id, struct timespec *timeout)
{
	struct dma_fence *fence;
	int ret;

	/*
	 * Look up the fence and take a reference. We might still find a fence
	 * whose refcount has already dropped to zero. dma_fence_get_rcu
	 * pretends we didn't find a fence in that case.
	 */
	rcu_read_lock();
	fence = idr_find(&gpu->fence_idr, id);
	if (fence)
		fence = dma_fence_get_rcu(fence);
	rcu_read_unlock();

	if (!fence)
		return 0;

	if (!timeout) {
		/* No timeout was requested: just test for completion */
		ret = dma_fence_is_signaled(fence) ? 0 : -EBUSY;
	} else {
		unsigned long remaining = etnaviv_timeout_to_jiffies(timeout);

		ret = dma_fence_wait_timeout(fence, true, remaining);
		if (ret == 0)
			ret = -ETIMEDOUT;
		else if (ret != -ERESTARTSYS)
			ret = 0;

	}

	dma_fence_put(fence);
	return ret;
}