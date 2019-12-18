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
struct amdgpu_device {int /*<<< orphan*/  in_suspend; } ;

/* Variables and functions */
#define  AMD_RESET_METHOD_BACO 129 
#define  AMD_RESET_METHOD_MODE2 128 
 int /*<<< orphan*/  amdgpu_inc_vram_lost (struct amdgpu_device*) ; 
 int soc15_asic_baco_reset (struct amdgpu_device*) ; 
 int soc15_asic_mode1_reset (struct amdgpu_device*) ; 
 int soc15_asic_reset_method (struct amdgpu_device*) ; 
 int soc15_mode2_reset (struct amdgpu_device*) ; 

__attribute__((used)) static int soc15_asic_reset(struct amdgpu_device *adev)
{
	switch (soc15_asic_reset_method(adev)) {
		case AMD_RESET_METHOD_BACO:
			if (!adev->in_suspend)
				amdgpu_inc_vram_lost(adev);
			return soc15_asic_baco_reset(adev);
		case AMD_RESET_METHOD_MODE2:
			return soc15_mode2_reset(adev);
		default:
			if (!adev->in_suspend)
				amdgpu_inc_vram_lost(adev);
			return soc15_asic_mode1_reset(adev);
	}
}