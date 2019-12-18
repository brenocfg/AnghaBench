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
struct TYPE_2__ {int vram_start; int vram_end; } ;
struct amdgpu_device {TYPE_1__ gmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  WREG32_SOC15_RLC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfxhub_v1_0_disable_identity_aperture (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfxhub_v1_0_enable_system_domain (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfxhub_v1_0_init_cache_regs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfxhub_v1_0_init_gart_aperture_regs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfxhub_v1_0_init_system_aperture_regs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfxhub_v1_0_init_tlb_regs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfxhub_v1_0_program_invalidation (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfxhub_v1_0_setup_vmid_config (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmMC_VM_FB_LOCATION_BASE ; 
 int /*<<< orphan*/  mmMC_VM_FB_LOCATION_TOP ; 

int gfxhub_v1_0_gart_enable(struct amdgpu_device *adev)
{
	if (amdgpu_sriov_vf(adev)) {
		/*
		 * MC_VM_FB_LOCATION_BASE/TOP is NULL for VF, becuase they are
		 * VF copy registers so vbios post doesn't program them, for
		 * SRIOV driver need to program them
		 */
		WREG32_SOC15_RLC(GC, 0, mmMC_VM_FB_LOCATION_BASE,
			     adev->gmc.vram_start >> 24);
		WREG32_SOC15_RLC(GC, 0, mmMC_VM_FB_LOCATION_TOP,
			     adev->gmc.vram_end >> 24);
	}

	/* GART Enable. */
	gfxhub_v1_0_init_gart_aperture_regs(adev);
	gfxhub_v1_0_init_system_aperture_regs(adev);
	gfxhub_v1_0_init_tlb_regs(adev);
	gfxhub_v1_0_init_cache_regs(adev);

	gfxhub_v1_0_enable_system_domain(adev);
	gfxhub_v1_0_disable_identity_aperture(adev);
	gfxhub_v1_0_setup_vmid_config(adev);
	gfxhub_v1_0_program_invalidation(adev);

	return 0;
}