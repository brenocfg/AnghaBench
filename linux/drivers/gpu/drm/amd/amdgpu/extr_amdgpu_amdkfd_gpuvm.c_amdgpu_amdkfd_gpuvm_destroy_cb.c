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
struct amdkfd_process_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  pid; int /*<<< orphan*/  restore_userptr_work; TYPE_3__* eviction_fence; int /*<<< orphan*/  userptr_inval_list; int /*<<< orphan*/  userptr_valid_list; int /*<<< orphan*/  kfd_bo_list; int /*<<< orphan*/  n_vms; } ;
struct TYPE_4__ {struct amdgpu_bo* bo; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct amdgpu_vm {int /*<<< orphan*/  vm_list_node; TYPE_2__ root; struct amdkfd_process_info* process_info; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  amdgpu_bo_fence (struct amdgpu_bo*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct amdkfd_process_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 

void amdgpu_amdkfd_gpuvm_destroy_cb(struct amdgpu_device *adev,
				    struct amdgpu_vm *vm)
{
	struct amdkfd_process_info *process_info = vm->process_info;
	struct amdgpu_bo *pd = vm->root.base.bo;

	if (!process_info)
		return;

	/* Release eviction fence from PD */
	amdgpu_bo_reserve(pd, false);
	amdgpu_bo_fence(pd, NULL, false);
	amdgpu_bo_unreserve(pd);

	/* Update process info */
	mutex_lock(&process_info->lock);
	process_info->n_vms--;
	list_del(&vm->vm_list_node);
	mutex_unlock(&process_info->lock);

	/* Release per-process resources when last compute VM is destroyed */
	if (!process_info->n_vms) {
		WARN_ON(!list_empty(&process_info->kfd_bo_list));
		WARN_ON(!list_empty(&process_info->userptr_valid_list));
		WARN_ON(!list_empty(&process_info->userptr_inval_list));

		dma_fence_put(&process_info->eviction_fence->base);
		cancel_delayed_work_sync(&process_info->restore_userptr_work);
		put_pid(process_info->pid);
		mutex_destroy(&process_info->lock);
		kfree(process_info);
	}
}