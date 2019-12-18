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
struct kfd_bo_va_list {struct amdgpu_bo_va* bo_va; } ;
struct amdgpu_sync {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo_va {int /*<<< orphan*/  last_pt_update; } ;

/* Variables and functions */
 int amdgpu_sync_fence (int /*<<< orphan*/ *,struct amdgpu_sync*,int /*<<< orphan*/ ,int) ; 
 int amdgpu_vm_bo_update (struct amdgpu_device*,struct amdgpu_bo_va*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int update_gpuvm_pte(struct amdgpu_device *adev,
		struct kfd_bo_va_list *entry,
		struct amdgpu_sync *sync)
{
	int ret;
	struct amdgpu_bo_va *bo_va = entry->bo_va;

	/* Update the page tables  */
	ret = amdgpu_vm_bo_update(adev, bo_va, false);
	if (ret) {
		pr_err("amdgpu_vm_bo_update failed\n");
		return ret;
	}

	return amdgpu_sync_fence(NULL, sync, bo_va->last_pt_update, false);
}