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
struct TYPE_2__ {int /*<<< orphan*/  pasid_lock; int /*<<< orphan*/  pasid_idr; scalar_t__ vm_update_mode; int /*<<< orphan*/  num_prt_users; int /*<<< orphan*/  prt_lock; int /*<<< orphan*/  vm_pte_next_ring; scalar_t__* seqno; int /*<<< orphan*/  fence_context; } ;
struct amdgpu_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 unsigned int AMDGPU_MAX_RINGS ; 
 int /*<<< orphan*/  amdgpu_vmid_mgr_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_context_alloc (unsigned int) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void amdgpu_vm_manager_init(struct amdgpu_device *adev)
{
	unsigned i;

	amdgpu_vmid_mgr_init(adev);

	adev->vm_manager.fence_context =
		dma_fence_context_alloc(AMDGPU_MAX_RINGS);
	for (i = 0; i < AMDGPU_MAX_RINGS; ++i)
		adev->vm_manager.seqno[i] = 0;

	atomic_set(&adev->vm_manager.vm_pte_next_ring, 0);
	spin_lock_init(&adev->vm_manager.prt_lock);
	atomic_set(&adev->vm_manager.num_prt_users, 0);

	/* If not overridden by the user, by default, only in large BAR systems
	 * Compute VM tables will be updated by CPU
	 */
#ifdef CONFIG_X86_64
	if (amdgpu_vm_update_mode == -1) {
		if (amdgpu_gmc_vram_full_visible(&adev->gmc))
			adev->vm_manager.vm_update_mode =
				AMDGPU_VM_USE_CPU_FOR_COMPUTE;
		else
			adev->vm_manager.vm_update_mode = 0;
	} else
		adev->vm_manager.vm_update_mode = amdgpu_vm_update_mode;
#else
	adev->vm_manager.vm_update_mode = 0;
#endif

	idr_init(&adev->vm_manager.pasid_idr);
	spin_lock_init(&adev->vm_manager.pasid_lock);
}