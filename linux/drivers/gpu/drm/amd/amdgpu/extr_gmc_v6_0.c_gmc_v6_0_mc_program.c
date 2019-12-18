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
typedef  int u32 ;
struct TYPE_6__ {int gpu_addr; } ;
struct TYPE_5__ {int vram_start; int vram_end; } ;
struct TYPE_4__ {scalar_t__ num_crtc; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; TYPE_3__ vram_scratch; TYPE_2__ gmc; TYPE_1__ mode_info; } ;

/* Variables and functions */
 int RREG32 (int) ; 
 int VGA_HDP_CONTROL__VGA_MEMORY_DISABLE_MASK ; 
 int VGA_VSTATUS_CNTL ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gmc_v6_0_wait_for_idle (void*) ; 
 int mmHDP_REG_COHERENCY_FLUSH_CNTL ; 
 int mmMC_VM_AGP_BASE ; 
 int mmMC_VM_AGP_BOT ; 
 int mmMC_VM_AGP_TOP ; 
 int mmMC_VM_SYSTEM_APERTURE_DEFAULT_ADDR ; 
 int mmMC_VM_SYSTEM_APERTURE_HIGH_ADDR ; 
 int mmMC_VM_SYSTEM_APERTURE_LOW_ADDR ; 
 int mmVGA_HDP_CONTROL ; 
 int mmVGA_RENDER_CONTROL ; 

__attribute__((used)) static void gmc_v6_0_mc_program(struct amdgpu_device *adev)
{
	int i, j;

	/* Initialize HDP */
	for (i = 0, j = 0; i < 32; i++, j += 0x6) {
		WREG32((0xb05 + j), 0x00000000);
		WREG32((0xb06 + j), 0x00000000);
		WREG32((0xb07 + j), 0x00000000);
		WREG32((0xb08 + j), 0x00000000);
		WREG32((0xb09 + j), 0x00000000);
	}
	WREG32(mmHDP_REG_COHERENCY_FLUSH_CNTL, 0);

	if (gmc_v6_0_wait_for_idle((void *)adev)) {
		dev_warn(adev->dev, "Wait for MC idle timedout !\n");
	}

	if (adev->mode_info.num_crtc) {
		u32 tmp;

		/* Lockout access through VGA aperture*/
		tmp = RREG32(mmVGA_HDP_CONTROL);
		tmp |= VGA_HDP_CONTROL__VGA_MEMORY_DISABLE_MASK;
		WREG32(mmVGA_HDP_CONTROL, tmp);

		/* disable VGA render */
		tmp = RREG32(mmVGA_RENDER_CONTROL);
		tmp &= ~VGA_VSTATUS_CNTL;
		WREG32(mmVGA_RENDER_CONTROL, tmp);
	}
	/* Update configuration */
	WREG32(mmMC_VM_SYSTEM_APERTURE_LOW_ADDR,
	       adev->gmc.vram_start >> 12);
	WREG32(mmMC_VM_SYSTEM_APERTURE_HIGH_ADDR,
	       adev->gmc.vram_end >> 12);
	WREG32(mmMC_VM_SYSTEM_APERTURE_DEFAULT_ADDR,
	       adev->vram_scratch.gpu_addr >> 12);
	WREG32(mmMC_VM_AGP_BASE, 0);
	WREG32(mmMC_VM_AGP_TOP, 0x0FFFFFFF);
	WREG32(mmMC_VM_AGP_BOT, 0x0FFFFFFF);

	if (gmc_v6_0_wait_for_idle((void *)adev)) {
		dev_warn(adev->dev, "Wait for MC idle timedout !\n");
	}
}