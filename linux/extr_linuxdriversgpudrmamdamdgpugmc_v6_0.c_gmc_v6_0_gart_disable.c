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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 unsigned long MC_VM_MX_L1_TLB_CNTL__SYSTEM_ACCESS_MODE_MASK ; 
 unsigned long MC_VM_MX_L1_TLB_CNTL__SYSTEM_APERTURE_UNMAPPED_ACCESS__SHIFT ; 
 unsigned long VM_L2_CNTL3__L2_CACHE_BIGK_ASSOCIATIVITY_MASK ; 
 unsigned long VM_L2_CNTL3__L2_CACHE_BIGK_FRAGMENT_SIZE__SHIFT ; 
 unsigned long VM_L2_CNTL__CONTEXT1_IDENTITY_ACCESS_MODE__SHIFT ; 
 unsigned long VM_L2_CNTL__EFFECTIVE_L2_QUEUE_SIZE__SHIFT ; 
 unsigned long VM_L2_CNTL__ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE_MASK ; 
 unsigned long VM_L2_CNTL__ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  amdgpu_gart_table_vram_unpin (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmMC_VM_MX_L1_TLB_CNTL ; 
 int /*<<< orphan*/  mmVM_CONTEXT0_CNTL ; 
 int /*<<< orphan*/  mmVM_CONTEXT1_CNTL ; 
 int /*<<< orphan*/  mmVM_L2_CNTL ; 
 int /*<<< orphan*/  mmVM_L2_CNTL2 ; 
 int /*<<< orphan*/  mmVM_L2_CNTL3 ; 

__attribute__((used)) static void gmc_v6_0_gart_disable(struct amdgpu_device *adev)
{
	/*unsigned i;

	for (i = 1; i < 16; ++i) {
		uint32_t reg;
		if (i < 8)
			reg = VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + i ;
		else
			reg = VM_CONTEXT8_PAGE_TABLE_BASE_ADDR + (i - 8);
		adev->vm_manager.saved_table_addr[i] = RREG32(reg);
	}*/

	/* Disable all tables */
	WREG32(mmVM_CONTEXT0_CNTL, 0);
	WREG32(mmVM_CONTEXT1_CNTL, 0);
	/* Setup TLB control */
	WREG32(mmMC_VM_MX_L1_TLB_CNTL,
	       MC_VM_MX_L1_TLB_CNTL__SYSTEM_ACCESS_MODE_MASK |
	       (0UL << MC_VM_MX_L1_TLB_CNTL__SYSTEM_APERTURE_UNMAPPED_ACCESS__SHIFT));
	/* Setup L2 cache */
	WREG32(mmVM_L2_CNTL,
	       VM_L2_CNTL__ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE_MASK |
	       VM_L2_CNTL__ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE_MASK |
	       (7UL << VM_L2_CNTL__EFFECTIVE_L2_QUEUE_SIZE__SHIFT) |
	       (1UL << VM_L2_CNTL__CONTEXT1_IDENTITY_ACCESS_MODE__SHIFT));
	WREG32(mmVM_L2_CNTL2, 0);
	WREG32(mmVM_L2_CNTL3,
	       VM_L2_CNTL3__L2_CACHE_BIGK_ASSOCIATIVITY_MASK |
	       (0UL << VM_L2_CNTL3__L2_CACHE_BIGK_FRAGMENT_SIZE__SHIFT));
	amdgpu_gart_table_vram_unpin(adev);
}