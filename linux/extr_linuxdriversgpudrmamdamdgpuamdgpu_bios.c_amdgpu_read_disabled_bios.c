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
struct amdgpu_device {int flags; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int amdgpu_asic_read_disabled_bios (struct amdgpu_device*) ; 
 int igp_read_bios_from_vram (struct amdgpu_device*) ; 

__attribute__((used)) static bool amdgpu_read_disabled_bios(struct amdgpu_device *adev)
{
	if (adev->flags & AMD_IS_APU)
		return igp_read_bios_from_vram(adev);
	else
		return amdgpu_asic_read_disabled_bios(adev);
}