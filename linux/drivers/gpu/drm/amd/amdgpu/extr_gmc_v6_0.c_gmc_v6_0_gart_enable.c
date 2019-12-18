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
typedef  int uint64_t ;
typedef  unsigned long u32 ;
struct TYPE_6__ {int ready; int /*<<< orphan*/ * bo; } ;
struct TYPE_5__ {int gart_start; int gart_end; int gart_size; } ;
struct TYPE_4__ {unsigned long fragment_size; int max_pfn; int block_size; } ;
struct amdgpu_device {int dummy_page_addr; TYPE_3__ gart; TYPE_2__ gmc; int /*<<< orphan*/  dev; TYPE_1__ vm_manager; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_VM_FAULT_STOP_ALWAYS ; 
 int EINVAL ; 
 int MC_VM_MX_L1_TLB_CNTL__ENABLE_ADVANCED_DRIVER_MODEL_MASK ; 
 int MC_VM_MX_L1_TLB_CNTL__ENABLE_L1_FRAGMENT_PROCESSING_MASK ; 
 int MC_VM_MX_L1_TLB_CNTL__ENABLE_L1_TLB_MASK ; 
 int MC_VM_MX_L1_TLB_CNTL__SYSTEM_ACCESS_MODE_MASK ; 
 unsigned long MC_VM_MX_L1_TLB_CNTL__SYSTEM_APERTURE_UNMAPPED_ACCESS__SHIFT ; 
 unsigned long VM_CONTEXT0_CNTL__ENABLE_CONTEXT_MASK ; 
 unsigned long VM_CONTEXT0_CNTL__PAGE_TABLE_DEPTH__SHIFT ; 
 unsigned long VM_CONTEXT0_CNTL__RANGE_PROTECTION_FAULT_ENABLE_DEFAULT_MASK ; 
 unsigned long VM_CONTEXT1_CNTL__ENABLE_CONTEXT_MASK ; 
 int VM_CONTEXT1_CNTL__PAGE_TABLE_BLOCK_SIZE__SHIFT ; 
 unsigned long VM_CONTEXT1_CNTL__PAGE_TABLE_DEPTH__SHIFT ; 
 unsigned long VM_L2_CNTL2__INVALIDATE_ALL_L1_TLBS_MASK ; 
 unsigned long VM_L2_CNTL2__INVALIDATE_L2_CACHE_MASK ; 
 unsigned long VM_L2_CNTL3__BANK_SELECT__SHIFT ; 
 unsigned long VM_L2_CNTL3__L2_CACHE_BIGK_ASSOCIATIVITY_MASK ; 
 unsigned long VM_L2_CNTL3__L2_CACHE_BIGK_FRAGMENT_SIZE__SHIFT ; 
 unsigned long VM_L2_CNTL__CONTEXT1_IDENTITY_ACCESS_MODE__SHIFT ; 
 unsigned long VM_L2_CNTL__EFFECTIVE_L2_QUEUE_SIZE__SHIFT ; 
 unsigned long VM_L2_CNTL__ENABLE_L2_CACHE_MASK ; 
 unsigned long VM_L2_CNTL__ENABLE_L2_FRAGMENT_PROCESSING_MASK ; 
 unsigned long VM_L2_CNTL__ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE_MASK ; 
 unsigned long VM_L2_CNTL__ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE_MASK ; 
 int /*<<< orphan*/  WREG32 (int,unsigned long) ; 
 int amdgpu_bo_gpu_offset (int /*<<< orphan*/ *) ; 
 int amdgpu_gart_table_vram_pin (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_vm_fault_stop ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int,unsigned long long) ; 
 int /*<<< orphan*/  gmc_v6_0_flush_gpu_tlb (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmc_v6_0_set_fault_enable_default (struct amdgpu_device*,int) ; 
 int mmMC_VM_MX_L1_TLB_CNTL ; 
 int mmVM_CONTEXT0_CNTL ; 
 int mmVM_CONTEXT0_CNTL2 ; 
 int mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR ; 
 int mmVM_CONTEXT0_PAGE_TABLE_END_ADDR ; 
 int mmVM_CONTEXT0_PAGE_TABLE_START_ADDR ; 
 int mmVM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR ; 
 int mmVM_CONTEXT1_CNTL ; 
 int mmVM_CONTEXT1_CNTL2 ; 
 int mmVM_CONTEXT1_PAGE_TABLE_END_ADDR ; 
 int mmVM_CONTEXT1_PAGE_TABLE_START_ADDR ; 
 int mmVM_CONTEXT1_PROTECTION_FAULT_DEFAULT_ADDR ; 
 int mmVM_CONTEXT8_PAGE_TABLE_BASE_ADDR ; 
 int mmVM_L2_CNTL ; 
 int mmVM_L2_CNTL2 ; 
 int mmVM_L2_CNTL3 ; 

__attribute__((used)) static int gmc_v6_0_gart_enable(struct amdgpu_device *adev)
{
	uint64_t table_addr;
	int r, i;
	u32 field;

	if (adev->gart.bo == NULL) {
		dev_err(adev->dev, "No VRAM object for PCIE GART.\n");
		return -EINVAL;
	}
	r = amdgpu_gart_table_vram_pin(adev);
	if (r)
		return r;

	table_addr = amdgpu_bo_gpu_offset(adev->gart.bo);

	/* Setup TLB control */
	WREG32(mmMC_VM_MX_L1_TLB_CNTL,
	       (0xA << 7) |
	       MC_VM_MX_L1_TLB_CNTL__ENABLE_L1_TLB_MASK |
	       MC_VM_MX_L1_TLB_CNTL__ENABLE_L1_FRAGMENT_PROCESSING_MASK |
	       MC_VM_MX_L1_TLB_CNTL__SYSTEM_ACCESS_MODE_MASK |
	       MC_VM_MX_L1_TLB_CNTL__ENABLE_ADVANCED_DRIVER_MODEL_MASK |
	       (0UL << MC_VM_MX_L1_TLB_CNTL__SYSTEM_APERTURE_UNMAPPED_ACCESS__SHIFT));
	/* Setup L2 cache */
	WREG32(mmVM_L2_CNTL,
	       VM_L2_CNTL__ENABLE_L2_CACHE_MASK |
	       VM_L2_CNTL__ENABLE_L2_FRAGMENT_PROCESSING_MASK |
	       VM_L2_CNTL__ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE_MASK |
	       VM_L2_CNTL__ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE_MASK |
	       (7UL << VM_L2_CNTL__EFFECTIVE_L2_QUEUE_SIZE__SHIFT) |
	       (1UL << VM_L2_CNTL__CONTEXT1_IDENTITY_ACCESS_MODE__SHIFT));
	WREG32(mmVM_L2_CNTL2,
	       VM_L2_CNTL2__INVALIDATE_ALL_L1_TLBS_MASK |
	       VM_L2_CNTL2__INVALIDATE_L2_CACHE_MASK);

	field = adev->vm_manager.fragment_size;
	WREG32(mmVM_L2_CNTL3,
	       VM_L2_CNTL3__L2_CACHE_BIGK_ASSOCIATIVITY_MASK |
	       (field << VM_L2_CNTL3__BANK_SELECT__SHIFT) |
	       (field << VM_L2_CNTL3__L2_CACHE_BIGK_FRAGMENT_SIZE__SHIFT));
	/* setup context0 */
	WREG32(mmVM_CONTEXT0_PAGE_TABLE_START_ADDR, adev->gmc.gart_start >> 12);
	WREG32(mmVM_CONTEXT0_PAGE_TABLE_END_ADDR, adev->gmc.gart_end >> 12);
	WREG32(mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR, table_addr >> 12);
	WREG32(mmVM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR,
			(u32)(adev->dummy_page_addr >> 12));
	WREG32(mmVM_CONTEXT0_CNTL2, 0);
	WREG32(mmVM_CONTEXT0_CNTL,
	       VM_CONTEXT0_CNTL__ENABLE_CONTEXT_MASK |
	       (0UL << VM_CONTEXT0_CNTL__PAGE_TABLE_DEPTH__SHIFT) |
	       VM_CONTEXT0_CNTL__RANGE_PROTECTION_FAULT_ENABLE_DEFAULT_MASK);

	WREG32(0x575, 0);
	WREG32(0x576, 0);
	WREG32(0x577, 0);

	/* empty context1-15 */
	/* set vm size, must be a multiple of 4 */
	WREG32(mmVM_CONTEXT1_PAGE_TABLE_START_ADDR, 0);
	WREG32(mmVM_CONTEXT1_PAGE_TABLE_END_ADDR, adev->vm_manager.max_pfn - 1);
	/* Assign the pt base to something valid for now; the pts used for
	 * the VMs are determined by the application and setup and assigned
	 * on the fly in the vm part of radeon_gart.c
	 */
	for (i = 1; i < 16; i++) {
		if (i < 8)
			WREG32(mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR + i,
			       table_addr >> 12);
		else
			WREG32(mmVM_CONTEXT8_PAGE_TABLE_BASE_ADDR + i - 8,
			       table_addr >> 12);
	}

	/* enable context1-15 */
	WREG32(mmVM_CONTEXT1_PROTECTION_FAULT_DEFAULT_ADDR,
	       (u32)(adev->dummy_page_addr >> 12));
	WREG32(mmVM_CONTEXT1_CNTL2, 4);
	WREG32(mmVM_CONTEXT1_CNTL,
	       VM_CONTEXT1_CNTL__ENABLE_CONTEXT_MASK |
	       (1UL << VM_CONTEXT1_CNTL__PAGE_TABLE_DEPTH__SHIFT) |
	       ((adev->vm_manager.block_size - 9)
	       << VM_CONTEXT1_CNTL__PAGE_TABLE_BLOCK_SIZE__SHIFT));
	if (amdgpu_vm_fault_stop == AMDGPU_VM_FAULT_STOP_ALWAYS)
		gmc_v6_0_set_fault_enable_default(adev, false);
	else
		gmc_v6_0_set_fault_enable_default(adev, true);

	gmc_v6_0_flush_gpu_tlb(adev, 0, 0, 0);
	dev_info(adev->dev, "PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (unsigned)(adev->gmc.gart_size >> 20),
		 (unsigned long long)table_addr);
	adev->gart.ready = true;
	return 0;
}