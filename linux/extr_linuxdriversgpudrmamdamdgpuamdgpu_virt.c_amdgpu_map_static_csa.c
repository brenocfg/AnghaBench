#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct ww_acquire_ctx {int dummy; } ;
struct list_head {int dummy; } ;
struct ttm_validate_buffer {int shared; struct list_head head; int /*<<< orphan*/ * bo; } ;
struct amdgpu_vm {int dummy; } ;
struct TYPE_4__ {TYPE_3__* csa_obj; } ;
struct amdgpu_device {TYPE_1__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  vm; } ;
struct amdgpu_bo_va {TYPE_2__ base; } ;
struct amdgpu_bo_list_entry {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_CSA_SIZE ; 
 int AMDGPU_PTE_EXECUTABLE ; 
 int AMDGPU_PTE_READABLE ; 
 int AMDGPU_PTE_WRITEABLE ; 
 int AMDGPU_VA_HOLE_MASK ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int amdgpu_csa_vaddr (struct amdgpu_device*) ; 
 int amdgpu_vm_alloc_pts (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct amdgpu_bo_va* amdgpu_vm_bo_add (struct amdgpu_device*,struct amdgpu_vm*,TYPE_3__*) ; 
 int amdgpu_vm_bo_map (struct amdgpu_device*,struct amdgpu_bo_va*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_rmv (struct amdgpu_device*,struct amdgpu_bo_va*) ; 
 int /*<<< orphan*/  amdgpu_vm_get_pd_bo (struct amdgpu_vm*,struct list_head*,struct amdgpu_bo_list_entry*) ; 
 int /*<<< orphan*/  list_add (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  ttm_eu_backoff_reservation (struct ww_acquire_ctx*,struct list_head*) ; 
 int ttm_eu_reserve_buffers (struct ww_acquire_ctx*,struct list_head*,int,int /*<<< orphan*/ *) ; 

int amdgpu_map_static_csa(struct amdgpu_device *adev, struct amdgpu_vm *vm,
			  struct amdgpu_bo_va **bo_va)
{
	uint64_t csa_addr = amdgpu_csa_vaddr(adev) & AMDGPU_VA_HOLE_MASK;
	struct ww_acquire_ctx ticket;
	struct list_head list;
	struct amdgpu_bo_list_entry pd;
	struct ttm_validate_buffer csa_tv;
	int r;

	INIT_LIST_HEAD(&list);
	INIT_LIST_HEAD(&csa_tv.head);
	csa_tv.bo = &adev->virt.csa_obj->tbo;
	csa_tv.shared = true;

	list_add(&csa_tv.head, &list);
	amdgpu_vm_get_pd_bo(vm, &list, &pd);

	r = ttm_eu_reserve_buffers(&ticket, &list, true, NULL);
	if (r) {
		DRM_ERROR("failed to reserve CSA,PD BOs: err=%d\n", r);
		return r;
	}

	*bo_va = amdgpu_vm_bo_add(adev, vm, adev->virt.csa_obj);
	if (!*bo_va) {
		ttm_eu_backoff_reservation(&ticket, &list);
		DRM_ERROR("failed to create bo_va for static CSA\n");
		return -ENOMEM;
	}

	r = amdgpu_vm_alloc_pts(adev, (*bo_va)->base.vm, csa_addr,
				AMDGPU_CSA_SIZE);
	if (r) {
		DRM_ERROR("failed to allocate pts for static CSA, err=%d\n", r);
		amdgpu_vm_bo_rmv(adev, *bo_va);
		ttm_eu_backoff_reservation(&ticket, &list);
		return r;
	}

	r = amdgpu_vm_bo_map(adev, *bo_va, csa_addr, 0, AMDGPU_CSA_SIZE,
			     AMDGPU_PTE_READABLE | AMDGPU_PTE_WRITEABLE |
			     AMDGPU_PTE_EXECUTABLE);

	if (r) {
		DRM_ERROR("failed to do bo_map on static CSA, err=%d\n", r);
		amdgpu_vm_bo_rmv(adev, *bo_va);
		ttm_eu_backoff_reservation(&ticket, &list);
		return r;
	}

	ttm_eu_backoff_reservation(&ticket, &list);
	return 0;
}