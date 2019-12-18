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
typedef  int uint32_t ;
struct amdgpu_device {scalar_t__ asic_type; scalar_t__ is_atom_fw; } ;

/* Variables and functions */
 int AMDGPU_RAS_BLOCK_MASK ; 
 scalar_t__ CHIP_VEGA20 ; 
 scalar_t__ amdgpu_atomfirmware_mem_ecc_supported (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_atomfirmware_sram_ecc_supported (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_ras_enable ; 
 int amdgpu_ras_mask ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 

__attribute__((used)) static void amdgpu_ras_check_supported(struct amdgpu_device *adev,
		uint32_t *hw_supported, uint32_t *supported)
{
	*hw_supported = 0;
	*supported = 0;

	if (amdgpu_sriov_vf(adev) ||
			adev->asic_type != CHIP_VEGA20)
		return;

	if (adev->is_atom_fw &&
			(amdgpu_atomfirmware_mem_ecc_supported(adev) ||
			 amdgpu_atomfirmware_sram_ecc_supported(adev)))
		*hw_supported = AMDGPU_RAS_BLOCK_MASK;

	*supported = amdgpu_ras_enable == 0 ?
				0 : *hw_supported & amdgpu_ras_mask;
}