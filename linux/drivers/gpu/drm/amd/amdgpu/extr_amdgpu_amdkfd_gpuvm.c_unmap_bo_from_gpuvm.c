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
struct kfd_bo_va_list {int /*<<< orphan*/  va; struct amdgpu_bo_va* bo_va; } ;
struct amdgpu_vm {int dummy; } ;
struct amdgpu_sync {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {struct amdgpu_vm* vm; } ;
struct amdgpu_bo_va {int /*<<< orphan*/  last_pt_update; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_sync_fence (int /*<<< orphan*/ *,struct amdgpu_sync*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_unmap (struct amdgpu_device*,struct amdgpu_bo_va*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_vm_clear_freed (struct amdgpu_device*,struct amdgpu_vm*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int unmap_bo_from_gpuvm(struct amdgpu_device *adev,
				struct kfd_bo_va_list *entry,
				struct amdgpu_sync *sync)
{
	struct amdgpu_bo_va *bo_va = entry->bo_va;
	struct amdgpu_vm *vm = bo_va->base.vm;

	amdgpu_vm_bo_unmap(adev, bo_va, entry->va);

	amdgpu_vm_clear_freed(adev, vm, &bo_va->last_pt_update);

	amdgpu_sync_fence(NULL, sync, bo_va->last_pt_update, false);

	return 0;
}