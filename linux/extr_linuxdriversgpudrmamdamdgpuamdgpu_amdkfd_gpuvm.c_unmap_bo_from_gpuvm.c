#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct kfd_bo_va_list {int /*<<< orphan*/  va; struct amdgpu_bo_va* bo_va; } ;
struct TYPE_6__ {struct amdgpu_bo* bo; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
struct amdgpu_vm {TYPE_3__* process_info; TYPE_2__ root; } ;
struct amdgpu_sync {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_9__ {struct amdgpu_vm* vm; } ;
struct amdgpu_bo_va {int /*<<< orphan*/  last_pt_update; TYPE_4__ base; } ;
struct amdgpu_bo {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  base; } ;
struct TYPE_8__ {TYPE_5__* eviction_fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_amdkfd_remove_eviction_fence (struct amdgpu_bo*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_bo_fence (struct amdgpu_bo*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_unmap (struct amdgpu_device*,struct amdgpu_bo_va*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_vm_clear_freed (struct amdgpu_device*,struct amdgpu_vm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_vm_fence (struct amdgpu_device*,struct amdgpu_sync*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unmap_bo_from_gpuvm(struct amdgpu_device *adev,
				struct kfd_bo_va_list *entry,
				struct amdgpu_sync *sync)
{
	struct amdgpu_bo_va *bo_va = entry->bo_va;
	struct amdgpu_vm *vm = bo_va->base.vm;
	struct amdgpu_bo *pd = vm->root.base.bo;

	/* Remove eviction fence from PD (and thereby from PTs too as
	 * they share the resv. object). Otherwise during PT update
	 * job (see amdgpu_vm_bo_update_mapping), eviction fence would
	 * get added to job->sync object and job execution would
	 * trigger the eviction fence.
	 */
	amdgpu_amdkfd_remove_eviction_fence(pd,
					    vm->process_info->eviction_fence,
					    NULL, NULL);
	amdgpu_vm_bo_unmap(adev, bo_va, entry->va);

	amdgpu_vm_clear_freed(adev, vm, &bo_va->last_pt_update);

	/* Add the eviction fence back */
	amdgpu_bo_fence(pd, &vm->process_info->eviction_fence->base, true);

	sync_vm_fence(adev, sync, bo_va->last_pt_update);

	return 0;
}