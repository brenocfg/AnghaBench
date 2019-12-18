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
typedef  int u32 ;
struct TYPE_6__ {int ready; int /*<<< orphan*/ * bo; } ;
struct TYPE_5__ {int gart_start; int gart_end; int gart_size; } ;
struct TYPE_4__ {int fragment_size; int max_pfn; int block_size; } ;
struct amdgpu_device {int dummy_page_addr; scalar_t__ asic_type; TYPE_3__ gart; TYPE_2__ gmc; TYPE_1__ vm_manager; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_VM_FAULT_STOP_ALWAYS ; 
 int /*<<< orphan*/  BANK_SELECT ; 
 int BYPASS_VM ; 
 scalar_t__ CHIP_KAVERI ; 
 int /*<<< orphan*/  CONTEXT1_IDENTITY_ACCESS_MODE ; 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int,unsigned long long) ; 
 int /*<<< orphan*/  EFFECTIVE_L2_QUEUE_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  ENABLE_ADVANCED_DRIVER_MODEL ; 
 int /*<<< orphan*/  ENABLE_CONTEXT ; 
 int /*<<< orphan*/  ENABLE_DEFAULT_PAGE_OUT_TO_SYSTEM_MEMORY ; 
 int /*<<< orphan*/  ENABLE_L1_FRAGMENT_PROCESSING ; 
 int /*<<< orphan*/  ENABLE_L1_TLB ; 
 int /*<<< orphan*/  ENABLE_L2_CACHE ; 
 int /*<<< orphan*/  ENABLE_L2_FRAGMENT_PROCESSING ; 
 int /*<<< orphan*/  ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE ; 
 int /*<<< orphan*/  ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE ; 
 int /*<<< orphan*/  INVALIDATE_ALL_L1_TLBS ; 
 int /*<<< orphan*/  INVALIDATE_L2_CACHE ; 
 int /*<<< orphan*/  L2_CACHE_BIGK_ASSOCIATIVITY ; 
 int /*<<< orphan*/  L2_CACHE_BIGK_FRAGMENT_SIZE ; 
 int /*<<< orphan*/  MC_VM_MX_L1_TLB_CNTL ; 
 int /*<<< orphan*/  PAGE_TABLE_BLOCK_SIZE ; 
 int /*<<< orphan*/  PAGE_TABLE_DEPTH ; 
 int /*<<< orphan*/  RANGE_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  SYSTEM_ACCESS_MODE ; 
 int /*<<< orphan*/  SYSTEM_APERTURE_UNMAPPED_ACCESS ; 
 int /*<<< orphan*/  VM_CONTEXT0_CNTL ; 
 int /*<<< orphan*/  VM_CONTEXT1_CNTL ; 
 int /*<<< orphan*/  VM_L2_CNTL ; 
 int /*<<< orphan*/  VM_L2_CNTL2 ; 
 int /*<<< orphan*/  VM_L2_CNTL3 ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int amdgpu_bo_gpu_offset (int /*<<< orphan*/ *) ; 
 int amdgpu_gart_table_vram_pin (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_vm_fault_stop ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gmc_v7_0_flush_gpu_tlb (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmc_v7_0_set_fault_enable_default (struct amdgpu_device*,int) ; 
 int mmCHUB_CONTROL ; 
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

__attribute__((used)) static int gmc_v7_0_gart_enable(struct amdgpu_device *adev)
{
	uint64_t table_addr;
	int r, i;
	u32 tmp, field;

	if (adev->gart.bo == NULL) {
		dev_err(adev->dev, "No VRAM object for PCIE GART.\n");
		return -EINVAL;
	}
	r = amdgpu_gart_table_vram_pin(adev);
	if (r)
		return r;

	table_addr = amdgpu_bo_gpu_offset(adev->gart.bo);

	/* Setup TLB control */
	tmp = RREG32(mmMC_VM_MX_L1_TLB_CNTL);
	tmp = REG_SET_FIELD(tmp, MC_VM_MX_L1_TLB_CNTL, ENABLE_L1_TLB, 1);
	tmp = REG_SET_FIELD(tmp, MC_VM_MX_L1_TLB_CNTL, ENABLE_L1_FRAGMENT_PROCESSING, 1);
	tmp = REG_SET_FIELD(tmp, MC_VM_MX_L1_TLB_CNTL, SYSTEM_ACCESS_MODE, 3);
	tmp = REG_SET_FIELD(tmp, MC_VM_MX_L1_TLB_CNTL, ENABLE_ADVANCED_DRIVER_MODEL, 1);
	tmp = REG_SET_FIELD(tmp, MC_VM_MX_L1_TLB_CNTL, SYSTEM_APERTURE_UNMAPPED_ACCESS, 0);
	WREG32(mmMC_VM_MX_L1_TLB_CNTL, tmp);
	/* Setup L2 cache */
	tmp = RREG32(mmVM_L2_CNTL);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL, ENABLE_L2_CACHE, 1);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL, ENABLE_L2_FRAGMENT_PROCESSING, 1);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL, ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE, 1);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL, ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE, 1);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL, EFFECTIVE_L2_QUEUE_SIZE, 7);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL, CONTEXT1_IDENTITY_ACCESS_MODE, 1);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL, ENABLE_DEFAULT_PAGE_OUT_TO_SYSTEM_MEMORY, 1);
	WREG32(mmVM_L2_CNTL, tmp);
	tmp = REG_SET_FIELD(0, VM_L2_CNTL2, INVALIDATE_ALL_L1_TLBS, 1);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL2, INVALIDATE_L2_CACHE, 1);
	WREG32(mmVM_L2_CNTL2, tmp);

	field = adev->vm_manager.fragment_size;
	tmp = RREG32(mmVM_L2_CNTL3);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL3, L2_CACHE_BIGK_ASSOCIATIVITY, 1);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL3, BANK_SELECT, field);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL3, L2_CACHE_BIGK_FRAGMENT_SIZE, field);
	WREG32(mmVM_L2_CNTL3, tmp);
	/* setup context0 */
	WREG32(mmVM_CONTEXT0_PAGE_TABLE_START_ADDR, adev->gmc.gart_start >> 12);
	WREG32(mmVM_CONTEXT0_PAGE_TABLE_END_ADDR, adev->gmc.gart_end >> 12);
	WREG32(mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR, table_addr >> 12);
	WREG32(mmVM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR,
			(u32)(adev->dummy_page_addr >> 12));
	WREG32(mmVM_CONTEXT0_CNTL2, 0);
	tmp = RREG32(mmVM_CONTEXT0_CNTL);
	tmp = REG_SET_FIELD(tmp, VM_CONTEXT0_CNTL, ENABLE_CONTEXT, 1);
	tmp = REG_SET_FIELD(tmp, VM_CONTEXT0_CNTL, PAGE_TABLE_DEPTH, 0);
	tmp = REG_SET_FIELD(tmp, VM_CONTEXT0_CNTL, RANGE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
	WREG32(mmVM_CONTEXT0_CNTL, tmp);

	WREG32(0x575, 0);
	WREG32(0x576, 0);
	WREG32(0x577, 0);

	/* empty context1-15 */
	/* FIXME start with 4G, once using 2 level pt switch to full
	 * vm size space
	 */
	/* set vm size, must be a multiple of 4 */
	WREG32(mmVM_CONTEXT1_PAGE_TABLE_START_ADDR, 0);
	WREG32(mmVM_CONTEXT1_PAGE_TABLE_END_ADDR, adev->vm_manager.max_pfn - 1);
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
	tmp = RREG32(mmVM_CONTEXT1_CNTL);
	tmp = REG_SET_FIELD(tmp, VM_CONTEXT1_CNTL, ENABLE_CONTEXT, 1);
	tmp = REG_SET_FIELD(tmp, VM_CONTEXT1_CNTL, PAGE_TABLE_DEPTH, 1);
	tmp = REG_SET_FIELD(tmp, VM_CONTEXT1_CNTL, PAGE_TABLE_BLOCK_SIZE,
			    adev->vm_manager.block_size - 9);
	WREG32(mmVM_CONTEXT1_CNTL, tmp);
	if (amdgpu_vm_fault_stop == AMDGPU_VM_FAULT_STOP_ALWAYS)
		gmc_v7_0_set_fault_enable_default(adev, false);
	else
		gmc_v7_0_set_fault_enable_default(adev, true);

	if (adev->asic_type == CHIP_KAVERI) {
		tmp = RREG32(mmCHUB_CONTROL);
		tmp &= ~BYPASS_VM;
		WREG32(mmCHUB_CONTROL, tmp);
	}

	gmc_v7_0_flush_gpu_tlb(adev, 0, 0, 0);
	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (unsigned)(adev->gmc.gart_size >> 20),
		 (unsigned long long)table_addr);
	adev->gart.ready = true;
	return 0;
}