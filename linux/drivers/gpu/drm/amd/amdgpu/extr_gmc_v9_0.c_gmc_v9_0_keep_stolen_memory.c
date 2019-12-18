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
struct amdgpu_device {int asic_type; } ;

/* Variables and functions */
#define  CHIP_ARCTURUS 133 
#define  CHIP_RAVEN 132 
#define  CHIP_RENOIR 131 
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 

__attribute__((used)) static bool gmc_v9_0_keep_stolen_memory(struct amdgpu_device *adev)
{

	/*
	 * TODO:
	 * Currently there is a bug where some memory client outside
	 * of the driver writes to first 8M of VRAM on S3 resume,
	 * this overrides GART which by default gets placed in first 8M and
	 * causes VM_FAULTS once GTT is accessed.
	 * Keep the stolen memory reservation until the while this is not solved.
	 * Also check code in gmc_v9_0_get_vbios_fb_size and gmc_v9_0_late_init
	 */
	switch (adev->asic_type) {
	case CHIP_VEGA10:
	case CHIP_RAVEN:
	case CHIP_ARCTURUS:
	case CHIP_RENOIR:
		return true;
	case CHIP_VEGA12:
	case CHIP_VEGA20:
	default:
		return false;
	}
}