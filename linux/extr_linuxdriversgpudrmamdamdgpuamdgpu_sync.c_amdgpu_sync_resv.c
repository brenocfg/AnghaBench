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
struct reservation_object_list {unsigned int shared_count; int /*<<< orphan*/ * shared; } ;
struct reservation_object {int dummy; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_sync {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 void* AMDGPU_FENCE_OWNER_KFD ; 
 void* AMDGPU_FENCE_OWNER_UNDEFINED ; 
 void* AMDGPU_FENCE_OWNER_VM ; 
 int EINVAL ; 
 int amdgpu_sync_fence (struct amdgpu_device*,struct amdgpu_sync*,struct dma_fence*,int) ; 
 void* amdgpu_sync_get_owner (struct dma_fence*) ; 
 scalar_t__ amdgpu_sync_same_dev (struct amdgpu_device*,struct dma_fence*) ; 
 struct dma_fence* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dma_fence* reservation_object_get_excl (struct reservation_object*) ; 
 struct reservation_object_list* reservation_object_get_list (struct reservation_object*) ; 
 int /*<<< orphan*/  reservation_object_held (struct reservation_object*) ; 

int amdgpu_sync_resv(struct amdgpu_device *adev,
		     struct amdgpu_sync *sync,
		     struct reservation_object *resv,
		     void *owner, bool explicit_sync)
{
	struct reservation_object_list *flist;
	struct dma_fence *f;
	void *fence_owner;
	unsigned i;
	int r = 0;

	if (resv == NULL)
		return -EINVAL;

	/* always sync to the exclusive fence */
	f = reservation_object_get_excl(resv);
	r = amdgpu_sync_fence(adev, sync, f, false);

	flist = reservation_object_get_list(resv);
	if (!flist || r)
		return r;

	for (i = 0; i < flist->shared_count; ++i) {
		f = rcu_dereference_protected(flist->shared[i],
					      reservation_object_held(resv));
		/* We only want to trigger KFD eviction fences on
		 * evict or move jobs. Skip KFD fences otherwise.
		 */
		fence_owner = amdgpu_sync_get_owner(f);
		if (fence_owner == AMDGPU_FENCE_OWNER_KFD &&
		    owner != AMDGPU_FENCE_OWNER_UNDEFINED)
			continue;

		if (amdgpu_sync_same_dev(adev, f)) {
			/* VM updates are only interesting
			 * for other VM updates and moves.
			 */
			if ((owner != AMDGPU_FENCE_OWNER_UNDEFINED) &&
			    (fence_owner != AMDGPU_FENCE_OWNER_UNDEFINED) &&
			    ((owner == AMDGPU_FENCE_OWNER_VM) !=
			     (fence_owner == AMDGPU_FENCE_OWNER_VM)))
				continue;

			/* Ignore fence from the same owner and explicit one as
			 * long as it isn't undefined.
			 */
			if (owner != AMDGPU_FENCE_OWNER_UNDEFINED &&
			    (fence_owner == owner || explicit_sync))
				continue;
		}

		r = amdgpu_sync_fence(adev, sync, f, false);
		if (r)
			break;
	}
	return r;
}