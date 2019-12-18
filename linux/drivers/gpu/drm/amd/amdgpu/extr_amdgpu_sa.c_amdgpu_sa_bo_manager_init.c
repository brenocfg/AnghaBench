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
typedef  void* u32 ;
struct amdgpu_sa_manager {unsigned int size; int /*<<< orphan*/  cpu_ptr; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/ * bo; int /*<<< orphan*/ * flist; int /*<<< orphan*/  olist; int /*<<< orphan*/ * hole; void* align; void* domain; int /*<<< orphan*/  wq; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AMDGPU_SA_NUM_FENCE_LISTS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,unsigned int,void*,void*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int amdgpu_sa_bo_manager_init(struct amdgpu_device *adev,
			      struct amdgpu_sa_manager *sa_manager,
			      unsigned size, u32 align, u32 domain)
{
	int i, r;

	init_waitqueue_head(&sa_manager->wq);
	sa_manager->bo = NULL;
	sa_manager->size = size;
	sa_manager->domain = domain;
	sa_manager->align = align;
	sa_manager->hole = &sa_manager->olist;
	INIT_LIST_HEAD(&sa_manager->olist);
	for (i = 0; i < AMDGPU_SA_NUM_FENCE_LISTS; ++i)
		INIT_LIST_HEAD(&sa_manager->flist[i]);

	r = amdgpu_bo_create_kernel(adev, size, align, domain, &sa_manager->bo,
				&sa_manager->gpu_addr, &sa_manager->cpu_ptr);
	if (r) {
		dev_err(adev->dev, "(%d) failed to allocate bo for manager\n", r);
		return r;
	}

	memset(sa_manager->cpu_ptr, 0, sa_manager->size);
	return r;
}