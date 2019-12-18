#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_6__* bo; } ;
struct TYPE_11__ {TYPE_5__ base; } ;
struct amdgpu_vm {int pte_support_ats; int use_cpu_for_update; unsigned int pasid; int /*<<< orphan*/  entity; TYPE_4__ root; int /*<<< orphan*/  faults; int /*<<< orphan*/ * last_update; int /*<<< orphan*/ * update_funcs; int /*<<< orphan*/  freed; int /*<<< orphan*/  invalidated_lock; int /*<<< orphan*/  invalidated; int /*<<< orphan*/  idle; int /*<<< orphan*/  moved; int /*<<< orphan*/  relocated; int /*<<< orphan*/  evicted; int /*<<< orphan*/ ** reserved_vmid; int /*<<< orphan*/  va; } ;
struct TYPE_10__ {int vm_update_mode; int /*<<< orphan*/  pasid_lock; int /*<<< orphan*/  pasid_idr; int /*<<< orphan*/  root_level; int /*<<< orphan*/  vm_pte_num_rqs; int /*<<< orphan*/  vm_pte_rqs; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_3__ vm_manager; int /*<<< orphan*/  gmc; } ;
struct amdgpu_bo_param {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  resv; } ;
struct TYPE_9__ {TYPE_1__ base; } ;
struct amdgpu_bo {TYPE_2__ tbo; } ;
struct TYPE_13__ {struct TYPE_13__* shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_CREATE_SHADOW ; 
 int AMDGPU_MAX_VMHUBS ; 
 int AMDGPU_VM_CONTEXT_COMPUTE ; 
 int AMDGPU_VM_USE_CPU_FOR_COMPUTE ; 
 int AMDGPU_VM_USE_CPU_FOR_GFX ; 
 scalar_t__ CHIP_RAVEN ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_KFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int amdgpu_bo_create (struct amdgpu_device*,struct amdgpu_bo_param*,struct amdgpu_bo**) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (TYPE_6__**) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (TYPE_6__*) ; 
 int /*<<< orphan*/  amdgpu_gmc_vram_full_visible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_base_init (TYPE_5__*,struct amdgpu_vm*,struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_param (struct amdgpu_device*,struct amdgpu_vm*,int /*<<< orphan*/ ,struct amdgpu_bo_param*) ; 
 int amdgpu_vm_clear_bo (struct amdgpu_device*,struct amdgpu_vm*,struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_vm_cpu_funcs ; 
 int /*<<< orphan*/  amdgpu_vm_sdma_funcs ; 
 int dma_resv_reserve_shared (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_sched_entity_destroy (int /*<<< orphan*/ *) ; 
 int drm_sched_entity_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct amdgpu_vm*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int amdgpu_vm_init(struct amdgpu_device *adev, struct amdgpu_vm *vm,
		   int vm_context, unsigned int pasid)
{
	struct amdgpu_bo_param bp;
	struct amdgpu_bo *root;
	int r, i;

	vm->va = RB_ROOT_CACHED;
	for (i = 0; i < AMDGPU_MAX_VMHUBS; i++)
		vm->reserved_vmid[i] = NULL;
	INIT_LIST_HEAD(&vm->evicted);
	INIT_LIST_HEAD(&vm->relocated);
	INIT_LIST_HEAD(&vm->moved);
	INIT_LIST_HEAD(&vm->idle);
	INIT_LIST_HEAD(&vm->invalidated);
	spin_lock_init(&vm->invalidated_lock);
	INIT_LIST_HEAD(&vm->freed);

	/* create scheduler entity for page table updates */
	r = drm_sched_entity_init(&vm->entity, adev->vm_manager.vm_pte_rqs,
				  adev->vm_manager.vm_pte_num_rqs, NULL);
	if (r)
		return r;

	vm->pte_support_ats = false;

	if (vm_context == AMDGPU_VM_CONTEXT_COMPUTE) {
		vm->use_cpu_for_update = !!(adev->vm_manager.vm_update_mode &
						AMDGPU_VM_USE_CPU_FOR_COMPUTE);

		if (adev->asic_type == CHIP_RAVEN)
			vm->pte_support_ats = true;
	} else {
		vm->use_cpu_for_update = !!(adev->vm_manager.vm_update_mode &
						AMDGPU_VM_USE_CPU_FOR_GFX);
	}
	DRM_DEBUG_DRIVER("VM update mode is %s\n",
			 vm->use_cpu_for_update ? "CPU" : "SDMA");
	WARN_ONCE((vm->use_cpu_for_update && !amdgpu_gmc_vram_full_visible(&adev->gmc)),
		  "CPU update of VM recommended only for large BAR system\n");

	if (vm->use_cpu_for_update)
		vm->update_funcs = &amdgpu_vm_cpu_funcs;
	else
		vm->update_funcs = &amdgpu_vm_sdma_funcs;
	vm->last_update = NULL;

	amdgpu_vm_bo_param(adev, vm, adev->vm_manager.root_level, &bp);
	if (vm_context == AMDGPU_VM_CONTEXT_COMPUTE)
		bp.flags &= ~AMDGPU_GEM_CREATE_SHADOW;
	r = amdgpu_bo_create(adev, &bp, &root);
	if (r)
		goto error_free_sched_entity;

	r = amdgpu_bo_reserve(root, true);
	if (r)
		goto error_free_root;

	r = dma_resv_reserve_shared(root->tbo.base.resv, 1);
	if (r)
		goto error_unreserve;

	amdgpu_vm_bo_base_init(&vm->root.base, vm, root);

	r = amdgpu_vm_clear_bo(adev, vm, root);
	if (r)
		goto error_unreserve;

	amdgpu_bo_unreserve(vm->root.base.bo);

	if (pasid) {
		unsigned long flags;

		spin_lock_irqsave(&adev->vm_manager.pasid_lock, flags);
		r = idr_alloc(&adev->vm_manager.pasid_idr, vm, pasid, pasid + 1,
			      GFP_ATOMIC);
		spin_unlock_irqrestore(&adev->vm_manager.pasid_lock, flags);
		if (r < 0)
			goto error_free_root;

		vm->pasid = pasid;
	}

	INIT_KFIFO(vm->faults);

	return 0;

error_unreserve:
	amdgpu_bo_unreserve(vm->root.base.bo);

error_free_root:
	amdgpu_bo_unref(&vm->root.base.bo->shadow);
	amdgpu_bo_unref(&vm->root.base.bo);
	vm->root.base.bo = NULL;

error_free_sched_entity:
	drm_sched_entity_destroy(&vm->entity);

	return r;
}