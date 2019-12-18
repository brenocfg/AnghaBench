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
struct TYPE_3__ {int /*<<< orphan*/  resv; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_pages; TYPE_1__ base; } ;
struct amdgpu_bo {int flags; int /*<<< orphan*/  kmap; TYPE_2__ tbo; } ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_NO_CPU_ACCESS ; 
 int EPERM ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 void* amdgpu_bo_kptr (struct amdgpu_bo*) ; 
 long dma_resv_wait_timeout_rcu (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 long ttm_bo_kmap (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int amdgpu_bo_kmap(struct amdgpu_bo *bo, void **ptr)
{
	void *kptr;
	long r;

	if (bo->flags & AMDGPU_GEM_CREATE_NO_CPU_ACCESS)
		return -EPERM;

	kptr = amdgpu_bo_kptr(bo);
	if (kptr) {
		if (ptr)
			*ptr = kptr;
		return 0;
	}

	r = dma_resv_wait_timeout_rcu(bo->tbo.base.resv, false, false,
						MAX_SCHEDULE_TIMEOUT);
	if (r < 0)
		return r;

	r = ttm_bo_kmap(&bo->tbo, 0, bo->tbo.num_pages, &bo->kmap);
	if (r)
		return r;

	if (ptr)
		*ptr = amdgpu_bo_kptr(bo);

	return 0;
}