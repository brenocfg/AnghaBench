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
struct amdgpu_device {int is_atom_fw; scalar_t__ asic_type; } ;

/* Variables and functions */
 scalar_t__ CHIP_VEGA10 ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ amdgpu_acpi_vfct_bios (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_atrm_get_bios (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_read_bios (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_read_bios_from_rom (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_read_disabled_bios (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_read_platform_bios (struct amdgpu_device*) ; 
 scalar_t__ igp_read_bios_from_vram (struct amdgpu_device*) ; 

bool amdgpu_get_bios(struct amdgpu_device *adev)
{
	if (amdgpu_atrm_get_bios(adev))
		goto success;

	if (amdgpu_acpi_vfct_bios(adev))
		goto success;

	if (igp_read_bios_from_vram(adev))
		goto success;

	if (amdgpu_read_bios(adev))
		goto success;

	if (amdgpu_read_bios_from_rom(adev))
		goto success;

	if (amdgpu_read_disabled_bios(adev))
		goto success;

	if (amdgpu_read_platform_bios(adev))
		goto success;

	DRM_ERROR("Unable to locate a BIOS ROM\n");
	return false;

success:
	adev->is_atom_fw = (adev->asic_type >= CHIP_VEGA10) ? true : false;
	return true;
}