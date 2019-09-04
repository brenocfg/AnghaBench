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
struct kfd_bo_va_list {struct amdgpu_bo_va* bo_va; } ;
struct amdgpu_vm {int dummy; } ;
struct amdgpu_sync {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {struct amdgpu_bo* bo; struct amdgpu_vm* vm; } ;
struct amdgpu_bo_va {int /*<<< orphan*/  last_pt_update; TYPE_1__ base; } ;
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 int amdgpu_vm_bo_update (struct amdgpu_device*,struct amdgpu_bo_va*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int sync_vm_fence (struct amdgpu_device*,struct amdgpu_sync*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_gpuvm_pte(struct amdgpu_device *adev,
		struct kfd_bo_va_list *entry,
		struct amdgpu_sync *sync)
{
	int ret;
	struct amdgpu_vm *vm;
	struct amdgpu_bo_va *bo_va;
	struct amdgpu_bo *bo;

	bo_va = entry->bo_va;
	vm = bo_va->base.vm;
	bo = bo_va->base.bo;

	/* Update the page tables  */
	ret = amdgpu_vm_bo_update(adev, bo_va, false);
	if (ret) {
		pr_err("amdgpu_vm_bo_update failed\n");
		return ret;
	}

	return sync_vm_fence(adev, sync, bo_va->last_pt_update);
}