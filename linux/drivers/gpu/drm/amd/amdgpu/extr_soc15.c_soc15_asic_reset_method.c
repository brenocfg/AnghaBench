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
struct amdgpu_ras {int /*<<< orphan*/  supported; } ;
struct amdgpu_hive_info {int dummy; } ;
struct TYPE_2__ {int sos_fw_version; } ;
struct amdgpu_device {int asic_type; TYPE_1__ psp; } ;
typedef  enum amd_reset_method { ____Placeholder_amd_reset_method } amd_reset_method ;

/* Variables and functions */
 int AMD_RESET_METHOD_BACO ; 
 int AMD_RESET_METHOD_MODE1 ; 
 int AMD_RESET_METHOD_MODE2 ; 
#define  CHIP_RAVEN 131 
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 
 struct amdgpu_hive_info* amdgpu_get_xgmi_hive (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 
 int /*<<< orphan*/  soc15_asic_get_baco_capability (struct amdgpu_device*,int*) ; 

__attribute__((used)) static enum amd_reset_method
soc15_asic_reset_method(struct amdgpu_device *adev)
{
	bool baco_reset;

	switch (adev->asic_type) {
	case CHIP_RAVEN:
		return AMD_RESET_METHOD_MODE2;
	case CHIP_VEGA10:
	case CHIP_VEGA12:
		soc15_asic_get_baco_capability(adev, &baco_reset);
		break;
	case CHIP_VEGA20:
		if (adev->psp.sos_fw_version >= 0x80067)
			soc15_asic_get_baco_capability(adev, &baco_reset);
		else
			baco_reset = false;
		if (baco_reset) {
			struct amdgpu_hive_info *hive = amdgpu_get_xgmi_hive(adev, 0);
			struct amdgpu_ras *ras = amdgpu_ras_get_context(adev);

			if (hive || (ras && ras->supported))
				baco_reset = false;
		}
		break;
	default:
		baco_reset = false;
		break;
	}

	if (baco_reset)
		return AMD_RESET_METHOD_BACO;
	else
		return AMD_RESET_METHOD_MODE1;
}