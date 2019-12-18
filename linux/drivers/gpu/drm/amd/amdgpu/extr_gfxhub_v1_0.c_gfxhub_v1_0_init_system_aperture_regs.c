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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int vram_base_offset; } ;
struct TYPE_5__ {int agp_start; int agp_end; int fb_end; int vram_start; int /*<<< orphan*/  fb_start; } ;
struct TYPE_4__ {int gpu_addr; } ;
struct amdgpu_device {scalar_t__ asic_type; int rev_id; int dummy_page_addr; TYPE_3__ vm_manager; TYPE_2__ gmc; TYPE_1__ vram_scratch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVE_PAGE_MIGRATION_PTE_READ_RETRY ; 
 scalar_t__ CHIP_RAVEN ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  VM_L2_PROTECTION_FAULT_CNTL2 ; 
 int /*<<< orphan*/  WREG32_FIELD15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15_RLC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max (int,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmMC_VM_AGP_BASE ; 
 int /*<<< orphan*/  mmMC_VM_AGP_BOT ; 
 int /*<<< orphan*/  mmMC_VM_AGP_TOP ; 
 int /*<<< orphan*/  mmMC_VM_SYSTEM_APERTURE_DEFAULT_ADDR_LSB ; 
 int /*<<< orphan*/  mmMC_VM_SYSTEM_APERTURE_DEFAULT_ADDR_MSB ; 
 int /*<<< orphan*/  mmMC_VM_SYSTEM_APERTURE_HIGH_ADDR ; 
 int /*<<< orphan*/  mmMC_VM_SYSTEM_APERTURE_LOW_ADDR ; 
 int /*<<< orphan*/  mmVM_L2_PROTECTION_FAULT_DEFAULT_ADDR_HI32 ; 
 int /*<<< orphan*/  mmVM_L2_PROTECTION_FAULT_DEFAULT_ADDR_LO32 ; 

__attribute__((used)) static void gfxhub_v1_0_init_system_aperture_regs(struct amdgpu_device *adev)
{
	uint64_t value;

	/* Program the AGP BAR */
	WREG32_SOC15_RLC(GC, 0, mmMC_VM_AGP_BASE, 0);
	WREG32_SOC15_RLC(GC, 0, mmMC_VM_AGP_BOT, adev->gmc.agp_start >> 24);
	WREG32_SOC15_RLC(GC, 0, mmMC_VM_AGP_TOP, adev->gmc.agp_end >> 24);

	/* Program the system aperture low logical page number. */
	WREG32_SOC15_RLC(GC, 0, mmMC_VM_SYSTEM_APERTURE_LOW_ADDR,
		     min(adev->gmc.fb_start, adev->gmc.agp_start) >> 18);

	if (adev->asic_type == CHIP_RAVEN && adev->rev_id >= 0x8)
		/*
		 * Raven2 has a HW issue that it is unable to use the vram which
		 * is out of MC_VM_SYSTEM_APERTURE_HIGH_ADDR. So here is the
		 * workaround that increase system aperture high address (add 1)
		 * to get rid of the VM fault and hardware hang.
		 */
		WREG32_SOC15_RLC(GC, 0, mmMC_VM_SYSTEM_APERTURE_HIGH_ADDR,
			     max((adev->gmc.fb_end >> 18) + 0x1,
				 adev->gmc.agp_end >> 18));
	else
		WREG32_SOC15_RLC(GC, 0, mmMC_VM_SYSTEM_APERTURE_HIGH_ADDR,
			     max(adev->gmc.fb_end, adev->gmc.agp_end) >> 18);

	/* Set default page address. */
	value = adev->vram_scratch.gpu_addr - adev->gmc.vram_start
		+ adev->vm_manager.vram_base_offset;
	WREG32_SOC15(GC, 0, mmMC_VM_SYSTEM_APERTURE_DEFAULT_ADDR_LSB,
		     (u32)(value >> 12));
	WREG32_SOC15(GC, 0, mmMC_VM_SYSTEM_APERTURE_DEFAULT_ADDR_MSB,
		     (u32)(value >> 44));

	/* Program "protection fault". */
	WREG32_SOC15(GC, 0, mmVM_L2_PROTECTION_FAULT_DEFAULT_ADDR_LO32,
		     (u32)(adev->dummy_page_addr >> 12));
	WREG32_SOC15(GC, 0, mmVM_L2_PROTECTION_FAULT_DEFAULT_ADDR_HI32,
		     (u32)((u64)adev->dummy_page_addr >> 44));

	WREG32_FIELD15(GC, 0, VM_L2_PROTECTION_FAULT_CNTL2,
		       ACTIVE_PAGE_MIGRATION_PTE_READ_RETRY, 1);
}