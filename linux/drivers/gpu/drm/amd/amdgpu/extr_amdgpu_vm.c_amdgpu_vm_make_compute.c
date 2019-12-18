#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* bo; } ;
struct TYPE_9__ {TYPE_2__ base; } ;
struct amdgpu_vm {int pte_support_ats; int use_cpu_for_update; int pasid; TYPE_3__ root; int /*<<< orphan*/ * last_update; int /*<<< orphan*/ * update_funcs; } ;
struct TYPE_7__ {int vm_update_mode; int /*<<< orphan*/  pasid_lock; int /*<<< orphan*/  pasid_idr; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_1__ vm_manager; int /*<<< orphan*/  gmc; } ;
struct TYPE_10__ {int /*<<< orphan*/  shadow; } ;

/* Variables and functions */
 int AMDGPU_VM_USE_CPU_FOR_COMPUTE ; 
 scalar_t__ CHIP_RAVEN ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char*) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int amdgpu_bo_reserve (TYPE_4__*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (TYPE_4__*) ; 
 int /*<<< orphan*/  amdgpu_gmc_vram_full_visible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_pasid_free (unsigned int) ; 
 int amdgpu_vm_check_clean_reserved (struct amdgpu_device*,struct amdgpu_vm*) ; 
 int amdgpu_vm_clear_bo (struct amdgpu_device*,struct amdgpu_vm*,TYPE_4__*) ; 
 int /*<<< orphan*/  amdgpu_vm_cpu_funcs ; 
 int /*<<< orphan*/  amdgpu_vm_sdma_funcs ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct amdgpu_vm*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int amdgpu_vm_make_compute(struct amdgpu_device *adev, struct amdgpu_vm *vm, unsigned int pasid)
{
	bool pte_support_ats = (adev->asic_type == CHIP_RAVEN);
	int r;

	r = amdgpu_bo_reserve(vm->root.base.bo, true);
	if (r)
		return r;

	/* Sanity checks */
	r = amdgpu_vm_check_clean_reserved(adev, vm);
	if (r)
		goto unreserve_bo;

	if (pasid) {
		unsigned long flags;

		spin_lock_irqsave(&adev->vm_manager.pasid_lock, flags);
		r = idr_alloc(&adev->vm_manager.pasid_idr, vm, pasid, pasid + 1,
			      GFP_ATOMIC);
		spin_unlock_irqrestore(&adev->vm_manager.pasid_lock, flags);

		if (r == -ENOSPC)
			goto unreserve_bo;
		r = 0;
	}

	/* Check if PD needs to be reinitialized and do it before
	 * changing any other state, in case it fails.
	 */
	if (pte_support_ats != vm->pte_support_ats) {
		vm->pte_support_ats = pte_support_ats;
		r = amdgpu_vm_clear_bo(adev, vm, vm->root.base.bo);
		if (r)
			goto free_idr;
	}

	/* Update VM state */
	vm->use_cpu_for_update = !!(adev->vm_manager.vm_update_mode &
				    AMDGPU_VM_USE_CPU_FOR_COMPUTE);
	DRM_DEBUG_DRIVER("VM update mode is %s\n",
			 vm->use_cpu_for_update ? "CPU" : "SDMA");
	WARN_ONCE((vm->use_cpu_for_update && !amdgpu_gmc_vram_full_visible(&adev->gmc)),
		  "CPU update of VM recommended only for large BAR system\n");

	if (vm->use_cpu_for_update)
		vm->update_funcs = &amdgpu_vm_cpu_funcs;
	else
		vm->update_funcs = &amdgpu_vm_sdma_funcs;
	dma_fence_put(vm->last_update);
	vm->last_update = NULL;

	if (vm->pasid) {
		unsigned long flags;

		spin_lock_irqsave(&adev->vm_manager.pasid_lock, flags);
		idr_remove(&adev->vm_manager.pasid_idr, vm->pasid);
		spin_unlock_irqrestore(&adev->vm_manager.pasid_lock, flags);

		/* Free the original amdgpu allocated pasid
		 * Will be replaced with kfd allocated pasid
		 */
		amdgpu_pasid_free(vm->pasid);
		vm->pasid = 0;
	}

	/* Free the shadow bo for compute VM */
	amdgpu_bo_unref(&vm->root.base.bo->shadow);

	if (pasid)
		vm->pasid = pasid;

	goto unreserve_bo;

free_idr:
	if (pasid) {
		unsigned long flags;

		spin_lock_irqsave(&adev->vm_manager.pasid_lock, flags);
		idr_remove(&adev->vm_manager.pasid_idr, pasid);
		spin_unlock_irqrestore(&adev->vm_manager.pasid_lock, flags);
	}
unreserve_bo:
	amdgpu_bo_unreserve(vm->root.base.bo);
	return r;
}