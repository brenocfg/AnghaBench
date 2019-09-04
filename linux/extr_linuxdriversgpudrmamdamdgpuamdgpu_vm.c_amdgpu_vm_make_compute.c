#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* bo; } ;
struct TYPE_11__ {TYPE_3__ base; scalar_t__ entries; } ;
struct TYPE_8__ {int /*<<< orphan*/  rb_root; } ;
struct amdgpu_vm {int pte_support_ats; int use_cpu_for_update; TYPE_4__ root; scalar_t__ pasid; TYPE_1__ va; } ;
struct TYPE_9__ {int vm_update_mode; int /*<<< orphan*/  pasid_lock; int /*<<< orphan*/  pasid_idr; int /*<<< orphan*/  root_level; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_2__ vm_manager; int /*<<< orphan*/  gmc; } ;
struct TYPE_12__ {int /*<<< orphan*/  shadow; } ;

/* Variables and functions */
 int AMDGPU_VM_USE_CPU_FOR_COMPUTE ; 
 scalar_t__ CHIP_RAVEN ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int amdgpu_bo_reserve (TYPE_5__*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (TYPE_5__*) ; 
 int /*<<< orphan*/  amdgpu_gmc_vram_full_visible (int /*<<< orphan*/ *) ; 
 int amdgpu_vm_clear_bo (struct amdgpu_device*,struct amdgpu_vm*,TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int amdgpu_vm_make_compute(struct amdgpu_device *adev, struct amdgpu_vm *vm)
{
	bool pte_support_ats = (adev->asic_type == CHIP_RAVEN);
	int r;

	r = amdgpu_bo_reserve(vm->root.base.bo, true);
	if (r)
		return r;

	/* Sanity checks */
	if (!RB_EMPTY_ROOT(&vm->va.rb_root) || vm->root.entries) {
		r = -EINVAL;
		goto error;
	}

	/* Check if PD needs to be reinitialized and do it before
	 * changing any other state, in case it fails.
	 */
	if (pte_support_ats != vm->pte_support_ats) {
		r = amdgpu_vm_clear_bo(adev, vm, vm->root.base.bo,
			       adev->vm_manager.root_level,
			       pte_support_ats);
		if (r)
			goto error;
	}

	/* Update VM state */
	vm->use_cpu_for_update = !!(adev->vm_manager.vm_update_mode &
				    AMDGPU_VM_USE_CPU_FOR_COMPUTE);
	vm->pte_support_ats = pte_support_ats;
	DRM_DEBUG_DRIVER("VM update mode is %s\n",
			 vm->use_cpu_for_update ? "CPU" : "SDMA");
	WARN_ONCE((vm->use_cpu_for_update & !amdgpu_gmc_vram_full_visible(&adev->gmc)),
		  "CPU update of VM recommended only for large BAR system\n");

	if (vm->pasid) {
		unsigned long flags;

		spin_lock_irqsave(&adev->vm_manager.pasid_lock, flags);
		idr_remove(&adev->vm_manager.pasid_idr, vm->pasid);
		spin_unlock_irqrestore(&adev->vm_manager.pasid_lock, flags);

		vm->pasid = 0;
	}

	/* Free the shadow bo for compute VM */
	amdgpu_bo_unref(&vm->root.base.bo->shadow);

error:
	amdgpu_bo_unreserve(vm->root.base.bo);
	return r;
}