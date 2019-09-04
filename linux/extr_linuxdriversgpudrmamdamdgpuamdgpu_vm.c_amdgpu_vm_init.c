#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_sched_rq {int dummy; } ;
struct TYPE_10__ {TYPE_5__* bo; } ;
struct TYPE_9__ {TYPE_4__ base; } ;
struct amdgpu_vm {int pte_support_ats; int use_cpu_for_update; unsigned int pasid; int fault_credit; int /*<<< orphan*/  entity; TYPE_3__ root; int /*<<< orphan*/  faults; int /*<<< orphan*/ * last_update; int /*<<< orphan*/  freed; int /*<<< orphan*/  idle; int /*<<< orphan*/  moved; int /*<<< orphan*/  moved_lock; int /*<<< orphan*/  relocated; int /*<<< orphan*/  evicted; int /*<<< orphan*/ ** reserved_vmid; int /*<<< orphan*/  va; } ;
struct TYPE_7__ {struct drm_sched_rq* sched_rq; } ;
struct amdgpu_ring {TYPE_1__ sched; } ;
struct TYPE_8__ {unsigned int vm_pte_num_rings; int vm_update_mode; int /*<<< orphan*/  pasid_lock; int /*<<< orphan*/  pasid_idr; int /*<<< orphan*/  root_level; struct amdgpu_ring** vm_pte_rings; int /*<<< orphan*/  vm_pte_next_ring; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_2__ vm_manager; int /*<<< orphan*/  gmc; } ;
struct amdgpu_bo_param {unsigned long size; unsigned int byte_align; int /*<<< orphan*/ * resv; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; int /*<<< orphan*/  domain; } ;
struct amdgpu_bo {int dummy; } ;
typedef  int /*<<< orphan*/  bp ;
struct TYPE_11__ {struct TYPE_11__* shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED ; 
 int /*<<< orphan*/  AMDGPU_GEM_CREATE_SHADOW ; 
 int /*<<< orphan*/  AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int AMDGPU_MAX_VMHUBS ; 
 int AMDGPU_VM_CONTEXT_COMPUTE ; 
 int /*<<< orphan*/  AMDGPU_VM_PTB_ALIGN_SIZE ; 
 int AMDGPU_VM_PTE_COUNT (struct amdgpu_device*) ; 
 int AMDGPU_VM_USE_CPU_FOR_COMPUTE ; 
 int AMDGPU_VM_USE_CPU_FOR_GFX ; 
 scalar_t__ CHIP_RAVEN ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char*) ; 
 size_t DRM_SCHED_PRIORITY_KERNEL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_KFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int amdgpu_bo_create (struct amdgpu_device*,struct amdgpu_bo_param*,struct amdgpu_bo**) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (TYPE_5__**) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (TYPE_5__*) ; 
 int /*<<< orphan*/  amdgpu_gmc_vram_full_visible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_base_init (TYPE_4__*,struct amdgpu_vm*,struct amdgpu_bo*) ; 
 unsigned long amdgpu_vm_bo_size (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int amdgpu_vm_clear_bo (struct amdgpu_device*,struct amdgpu_vm*,struct amdgpu_bo*,int /*<<< orphan*/ ,int) ; 
 unsigned int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sched_entity_destroy (int /*<<< orphan*/ *) ; 
 int drm_sched_entity_init (int /*<<< orphan*/ *,struct drm_sched_rq**,int,int /*<<< orphan*/ *) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct amdgpu_vm*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct amdgpu_bo_param*,int /*<<< orphan*/ ,int) ; 
 unsigned int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ttm_bo_type_kernel ; 

int amdgpu_vm_init(struct amdgpu_device *adev, struct amdgpu_vm *vm,
		   int vm_context, unsigned int pasid)
{
	struct amdgpu_bo_param bp;
	struct amdgpu_bo *root;
	const unsigned align = min(AMDGPU_VM_PTB_ALIGN_SIZE,
		AMDGPU_VM_PTE_COUNT(adev) * 8);
	unsigned ring_instance;
	struct amdgpu_ring *ring;
	struct drm_sched_rq *rq;
	unsigned long size;
	uint64_t flags;
	int r, i;

	vm->va = RB_ROOT_CACHED;
	for (i = 0; i < AMDGPU_MAX_VMHUBS; i++)
		vm->reserved_vmid[i] = NULL;
	INIT_LIST_HEAD(&vm->evicted);
	INIT_LIST_HEAD(&vm->relocated);
	spin_lock_init(&vm->moved_lock);
	INIT_LIST_HEAD(&vm->moved);
	INIT_LIST_HEAD(&vm->idle);
	INIT_LIST_HEAD(&vm->freed);

	/* create scheduler entity for page table updates */

	ring_instance = atomic_inc_return(&adev->vm_manager.vm_pte_next_ring);
	ring_instance %= adev->vm_manager.vm_pte_num_rings;
	ring = adev->vm_manager.vm_pte_rings[ring_instance];
	rq = &ring->sched.sched_rq[DRM_SCHED_PRIORITY_KERNEL];
	r = drm_sched_entity_init(&vm->entity, &rq, 1, NULL);
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
	WARN_ONCE((vm->use_cpu_for_update & !amdgpu_gmc_vram_full_visible(&adev->gmc)),
		  "CPU update of VM recommended only for large BAR system\n");
	vm->last_update = NULL;

	flags = AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS;
	if (vm->use_cpu_for_update)
		flags |= AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;
	else if (vm_context != AMDGPU_VM_CONTEXT_COMPUTE)
		flags |= AMDGPU_GEM_CREATE_SHADOW;

	size = amdgpu_vm_bo_size(adev, adev->vm_manager.root_level);
	memset(&bp, 0, sizeof(bp));
	bp.size = size;
	bp.byte_align = align;
	bp.domain = AMDGPU_GEM_DOMAIN_VRAM;
	bp.flags = flags;
	bp.type = ttm_bo_type_kernel;
	bp.resv = NULL;
	r = amdgpu_bo_create(adev, &bp, &root);
	if (r)
		goto error_free_sched_entity;

	r = amdgpu_bo_reserve(root, true);
	if (r)
		goto error_free_root;

	r = amdgpu_vm_clear_bo(adev, vm, root,
			       adev->vm_manager.root_level,
			       vm->pte_support_ats);
	if (r)
		goto error_unreserve;

	amdgpu_vm_bo_base_init(&vm->root.base, vm, root);
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
	vm->fault_credit = 16;

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