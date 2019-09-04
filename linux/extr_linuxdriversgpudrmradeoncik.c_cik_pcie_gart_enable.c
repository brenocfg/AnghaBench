#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int table_addr; int ready; int /*<<< orphan*/ * robj; } ;
struct TYPE_7__ {int gtt_start; int gtt_end; int gtt_size; } ;
struct TYPE_6__ {int addr; } ;
struct TYPE_5__ {int max_pfn; int* saved_table_addr; } ;
struct radeon_device {scalar_t__ family; TYPE_4__ gart; TYPE_3__ mc; int /*<<< orphan*/  srbm_mutex; TYPE_2__ dummy_page; TYPE_1__ vm_manager; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BANK_SELECT (int) ; 
 int BYPASS_VM ; 
 scalar_t__ CHIP_KAVERI ; 
 int CHUB_CONTROL ; 
 int CONTEXT1_IDENTITY_ACCESS_MODE (int) ; 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int,unsigned long long) ; 
 int DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT ; 
 int EFFECTIVE_L2_QUEUE_SIZE (int) ; 
 int EINVAL ; 
 int ENABLE_ADVANCED_DRIVER_MODEL ; 
 int ENABLE_CONTEXT ; 
 int ENABLE_L1_FRAGMENT_PROCESSING ; 
 int ENABLE_L1_TLB ; 
 int ENABLE_L2_CACHE ; 
 int ENABLE_L2_FRAGMENT_PROCESSING ; 
 int ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE ; 
 int ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE ; 
 int INVALIDATE_ALL_L1_TLBS ; 
 int INVALIDATE_L2_CACHE ; 
 int L2_CACHE_BIGK_ASSOCIATIVITY ; 
 int L2_CACHE_BIGK_FRAGMENT_SIZE (int) ; 
 int MC_VM_MX_L1_TLB_CNTL ; 
 int PAGE_TABLE_BLOCK_SIZE (scalar_t__) ; 
 int PAGE_TABLE_DEPTH (int) ; 
 int PDE0_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT ; 
 int RANGE_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT ; 
 int READ_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int READ_PROTECTION_FAULT_ENABLE_INTERRUPT ; 
 int RREG32 (int) ; 
 int SDMA0_GFX_APE1_CNTL ; 
 int SDMA0_GFX_VIRTUAL_ADDR ; 
 int SDMA0_REGISTER_OFFSET ; 
 int SDMA1_REGISTER_OFFSET ; 
 int SH_MEM_APE1_BASE ; 
 int SH_MEM_APE1_LIMIT ; 
 int SH_MEM_BASES ; 
 int SH_MEM_CONFIG ; 
 int SH_MEM_CONFIG_GFX_DEFAULT ; 
 int SYSTEM_ACCESS_MODE_NOT_IN_SYS ; 
 int SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU ; 
 int VALID_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int VALID_PROTECTION_FAULT_ENABLE_INTERRUPT ; 
 int VM_CONTEXT0_CNTL ; 
 int VM_CONTEXT0_CNTL2 ; 
 int VM_CONTEXT0_PAGE_TABLE_BASE_ADDR ; 
 int VM_CONTEXT0_PAGE_TABLE_END_ADDR ; 
 int VM_CONTEXT0_PAGE_TABLE_START_ADDR ; 
 int VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR ; 
 int VM_CONTEXT1_CNTL ; 
 int VM_CONTEXT1_CNTL2 ; 
 int VM_CONTEXT1_PAGE_TABLE_END_ADDR ; 
 int VM_CONTEXT1_PAGE_TABLE_START_ADDR ; 
 int VM_CONTEXT1_PROTECTION_FAULT_DEFAULT_ADDR ; 
 int VM_CONTEXT8_PAGE_TABLE_BASE_ADDR ; 
 int VM_L2_CNTL ; 
 int VM_L2_CNTL2 ; 
 int VM_L2_CNTL3 ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int WRITE_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT ; 
 int /*<<< orphan*/  cik_pcie_gart_tlb_flush (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_srbm_select (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int radeon_gart_table_vram_pin (struct radeon_device*) ; 
 scalar_t__ radeon_vm_block_size ; 

__attribute__((used)) static int cik_pcie_gart_enable(struct radeon_device *rdev)
{
	int r, i;

	if (rdev->gart.robj == NULL) {
		dev_err(rdev->dev, "No VRAM object for PCIE GART.\n");
		return -EINVAL;
	}
	r = radeon_gart_table_vram_pin(rdev);
	if (r)
		return r;
	/* Setup TLB control */
	WREG32(MC_VM_MX_L1_TLB_CNTL,
	       (0xA << 7) |
	       ENABLE_L1_TLB |
	       ENABLE_L1_FRAGMENT_PROCESSING |
	       SYSTEM_ACCESS_MODE_NOT_IN_SYS |
	       ENABLE_ADVANCED_DRIVER_MODEL |
	       SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU);
	/* Setup L2 cache */
	WREG32(VM_L2_CNTL, ENABLE_L2_CACHE |
	       ENABLE_L2_FRAGMENT_PROCESSING |
	       ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE |
	       ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE |
	       EFFECTIVE_L2_QUEUE_SIZE(7) |
	       CONTEXT1_IDENTITY_ACCESS_MODE(1));
	WREG32(VM_L2_CNTL2, INVALIDATE_ALL_L1_TLBS | INVALIDATE_L2_CACHE);
	WREG32(VM_L2_CNTL3, L2_CACHE_BIGK_ASSOCIATIVITY |
	       BANK_SELECT(4) |
	       L2_CACHE_BIGK_FRAGMENT_SIZE(4));
	/* setup context0 */
	WREG32(VM_CONTEXT0_PAGE_TABLE_START_ADDR, rdev->mc.gtt_start >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_END_ADDR, rdev->mc.gtt_end >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR, rdev->gart.table_addr >> 12);
	WREG32(VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR,
			(u32)(rdev->dummy_page.addr >> 12));
	WREG32(VM_CONTEXT0_CNTL2, 0);
	WREG32(VM_CONTEXT0_CNTL, (ENABLE_CONTEXT | PAGE_TABLE_DEPTH(0) |
				  RANGE_PROTECTION_FAULT_ENABLE_DEFAULT));

	WREG32(0x15D4, 0);
	WREG32(0x15D8, 0);
	WREG32(0x15DC, 0);

	/* restore context1-15 */
	/* set vm size, must be a multiple of 4 */
	WREG32(VM_CONTEXT1_PAGE_TABLE_START_ADDR, 0);
	WREG32(VM_CONTEXT1_PAGE_TABLE_END_ADDR, rdev->vm_manager.max_pfn - 1);
	for (i = 1; i < 16; i++) {
		if (i < 8)
			WREG32(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (i << 2),
			       rdev->vm_manager.saved_table_addr[i]);
		else
			WREG32(VM_CONTEXT8_PAGE_TABLE_BASE_ADDR + ((i - 8) << 2),
			       rdev->vm_manager.saved_table_addr[i]);
	}

	/* enable context1-15 */
	WREG32(VM_CONTEXT1_PROTECTION_FAULT_DEFAULT_ADDR,
	       (u32)(rdev->dummy_page.addr >> 12));
	WREG32(VM_CONTEXT1_CNTL2, 4);
	WREG32(VM_CONTEXT1_CNTL, ENABLE_CONTEXT | PAGE_TABLE_DEPTH(1) |
				PAGE_TABLE_BLOCK_SIZE(radeon_vm_block_size - 9) |
				RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT |
				RANGE_PROTECTION_FAULT_ENABLE_DEFAULT |
				DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT |
				DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT |
				PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT |
				PDE0_PROTECTION_FAULT_ENABLE_DEFAULT |
				VALID_PROTECTION_FAULT_ENABLE_INTERRUPT |
				VALID_PROTECTION_FAULT_ENABLE_DEFAULT |
				READ_PROTECTION_FAULT_ENABLE_INTERRUPT |
				READ_PROTECTION_FAULT_ENABLE_DEFAULT |
				WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT |
				WRITE_PROTECTION_FAULT_ENABLE_DEFAULT);

	if (rdev->family == CHIP_KAVERI) {
		u32 tmp = RREG32(CHUB_CONTROL);
		tmp &= ~BYPASS_VM;
		WREG32(CHUB_CONTROL, tmp);
	}

	/* XXX SH_MEM regs */
	/* where to put LDS, scratch, GPUVM in FSA64 space */
	mutex_lock(&rdev->srbm_mutex);
	for (i = 0; i < 16; i++) {
		cik_srbm_select(rdev, 0, 0, 0, i);
		/* CP and shaders */
		WREG32(SH_MEM_CONFIG, SH_MEM_CONFIG_GFX_DEFAULT);
		WREG32(SH_MEM_APE1_BASE, 1);
		WREG32(SH_MEM_APE1_LIMIT, 0);
		WREG32(SH_MEM_BASES, 0);
		/* SDMA GFX */
		WREG32(SDMA0_GFX_VIRTUAL_ADDR + SDMA0_REGISTER_OFFSET, 0);
		WREG32(SDMA0_GFX_APE1_CNTL + SDMA0_REGISTER_OFFSET, 0);
		WREG32(SDMA0_GFX_VIRTUAL_ADDR + SDMA1_REGISTER_OFFSET, 0);
		WREG32(SDMA0_GFX_APE1_CNTL + SDMA1_REGISTER_OFFSET, 0);
		/* XXX SDMA RLC - todo */
	}
	cik_srbm_select(rdev, 0, 0, 0, 0);
	mutex_unlock(&rdev->srbm_mutex);

	cik_pcie_gart_tlb_flush(rdev);
	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (unsigned)(rdev->mc.gtt_size >> 20),
		 (unsigned long long)rdev->gart.table_addr);
	rdev->gart.ready = true;
	return 0;
}