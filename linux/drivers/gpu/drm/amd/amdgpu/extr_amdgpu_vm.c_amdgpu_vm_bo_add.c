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
struct amdgpu_vm {int dummy; } ;
struct TYPE_4__ {int xgmi_map_counter; int /*<<< orphan*/  lock_pstate; } ;
struct amdgpu_device {TYPE_2__ vm_manager; } ;
struct amdgpu_bo_va {int ref_count; int is_xgmi; int /*<<< orphan*/  invalids; int /*<<< orphan*/  valids; int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {int preferred_domains; TYPE_1__ tbo; } ;

/* Variables and functions */
 int AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_base_init (int /*<<< orphan*/ *,struct amdgpu_vm*,struct amdgpu_bo*) ; 
 scalar_t__ amdgpu_xgmi_same_hive (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_xgmi_set_pstate (struct amdgpu_device*,int) ; 
 struct amdgpu_bo_va* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct amdgpu_bo_va *amdgpu_vm_bo_add(struct amdgpu_device *adev,
				      struct amdgpu_vm *vm,
				      struct amdgpu_bo *bo)
{
	struct amdgpu_bo_va *bo_va;

	bo_va = kzalloc(sizeof(struct amdgpu_bo_va), GFP_KERNEL);
	if (bo_va == NULL) {
		return NULL;
	}
	amdgpu_vm_bo_base_init(&bo_va->base, vm, bo);

	bo_va->ref_count = 1;
	INIT_LIST_HEAD(&bo_va->valids);
	INIT_LIST_HEAD(&bo_va->invalids);

	if (bo && amdgpu_xgmi_same_hive(adev, amdgpu_ttm_adev(bo->tbo.bdev)) &&
	    (bo->preferred_domains & AMDGPU_GEM_DOMAIN_VRAM)) {
		bo_va->is_xgmi = true;
		mutex_lock(&adev->vm_manager.lock_pstate);
		/* Power up XGMI if it can be potentially used */
		if (++adev->vm_manager.xgmi_map_counter == 1)
			amdgpu_xgmi_set_pstate(adev, 1);
		mutex_unlock(&adev->vm_manager.lock_pstate);
	}

	return bo_va;
}