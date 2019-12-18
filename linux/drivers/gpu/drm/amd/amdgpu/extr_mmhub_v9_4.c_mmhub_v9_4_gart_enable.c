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
 int /*<<< orphan*/  MMHUB ; 
 int MMHUB_INSTANCE_REGISTER_OFFSET ; 
 int MMHUB_NUM_INSTANCES ; 
 int /*<<< orphan*/  WREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmVMSHAREDVC0_MC_VM_FB_LOCATION_BASE ; 
 int /*<<< orphan*/  mmVMSHAREDVC0_MC_VM_FB_LOCATION_TOP ; 
 int /*<<< orphan*/  mmhub_v9_4_disable_identity_aperture (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mmhub_v9_4_enable_system_domain (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mmhub_v9_4_init_cache_regs (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mmhub_v9_4_init_gart_aperture_regs (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mmhub_v9_4_init_system_aperture_regs (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mmhub_v9_4_init_tlb_regs (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mmhub_v9_4_program_invalidation (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mmhub_v9_4_setup_vmid_config (struct amdgpu_device*,int) ; 

int mmhub_v9_4_gart_enable(struct amdgpu_device *adev)
{
	int i;

	for (i = 0; i < MMHUB_NUM_INSTANCES; i++) {
		if (amdgpu_sriov_vf(adev)) {
			/*
			 * MC_VM_FB_LOCATION_BASE/TOP is NULL for VF, becuase
			 * they are VF copy registers so vbios post doesn't
			 * program them, for SRIOV driver need to program them
			 */
			WREG32_SOC15_OFFSET(MMHUB, 0,
				     mmVMSHAREDVC0_MC_VM_FB_LOCATION_BASE,
				     i * MMHUB_INSTANCE_REGISTER_OFFSET,
				     adev->gmc.vram_start >> 24);
			WREG32_SOC15_OFFSET(MMHUB, 0,
				     mmVMSHAREDVC0_MC_VM_FB_LOCATION_TOP,
				     i * MMHUB_INSTANCE_REGISTER_OFFSET,
				     adev->gmc.vram_end >> 24);
		}

		/* GART Enable. */
		mmhub_v9_4_init_gart_aperture_regs(adev, i);
		mmhub_v9_4_init_system_aperture_regs(adev, i);
		mmhub_v9_4_init_tlb_regs(adev, i);
		mmhub_v9_4_init_cache_regs(adev, i);

		mmhub_v9_4_enable_system_domain(adev, i);
		mmhub_v9_4_disable_identity_aperture(adev, i);
		mmhub_v9_4_setup_vmid_config(adev, i);
		mmhub_v9_4_program_invalidation(adev, i);
	}

	return 0;
}