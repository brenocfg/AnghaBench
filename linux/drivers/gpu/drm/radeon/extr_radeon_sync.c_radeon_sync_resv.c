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
struct radeon_sync {int dummy; } ;
struct radeon_fence {struct radeon_device* rdev; } ;
struct radeon_device {int dummy; } ;
struct dma_resv_list {unsigned int shared_count; int /*<<< orphan*/ * shared; } ;
struct dma_resv {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int dma_fence_wait (struct dma_fence*,int) ; 
 struct dma_fence* dma_resv_get_excl (struct dma_resv*) ; 
 struct dma_resv_list* dma_resv_get_list (struct dma_resv*) ; 
 int /*<<< orphan*/  dma_resv_held (struct dma_resv*) ; 
 int /*<<< orphan*/  radeon_sync_fence (struct radeon_sync*,struct radeon_fence*) ; 
 struct dma_fence* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radeon_fence* to_radeon_fence (struct dma_fence*) ; 

int radeon_sync_resv(struct radeon_device *rdev,
		     struct radeon_sync *sync,
		     struct dma_resv *resv,
		     bool shared)
{
	struct dma_resv_list *flist;
	struct dma_fence *f;
	struct radeon_fence *fence;
	unsigned i;
	int r = 0;

	/* always sync to the exclusive fence */
	f = dma_resv_get_excl(resv);
	fence = f ? to_radeon_fence(f) : NULL;
	if (fence && fence->rdev == rdev)
		radeon_sync_fence(sync, fence);
	else if (f)
		r = dma_fence_wait(f, true);

	flist = dma_resv_get_list(resv);
	if (shared || !flist || r)
		return r;

	for (i = 0; i < flist->shared_count; ++i) {
		f = rcu_dereference_protected(flist->shared[i],
					      dma_resv_held(resv));
		fence = to_radeon_fence(f);
		if (fence && fence->rdev == rdev)
			radeon_sync_fence(sync, fence);
		else
			r = dma_fence_wait(f, true);

		if (r)
			break;
	}
	return r;
}