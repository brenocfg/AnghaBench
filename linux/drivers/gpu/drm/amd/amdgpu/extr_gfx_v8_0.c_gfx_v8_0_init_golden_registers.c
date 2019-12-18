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
struct amdgpu_device {int asic_type; TYPE_1__* pdev; } ;
struct TYPE_2__ {int revision; int subsystem_device; int subsystem_vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  CHIP_CARRIZO 136 
#define  CHIP_FIJI 135 
#define  CHIP_POLARIS10 134 
#define  CHIP_POLARIS11 133 
#define  CHIP_POLARIS12 132 
#define  CHIP_STONEY 131 
#define  CHIP_TONGA 130 
#define  CHIP_TOPAZ 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_atombios_i2c_channel_trans (struct amdgpu_device*,int,int,int,int) ; 
 int /*<<< orphan*/  amdgpu_device_program_register_sequence (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cz_golden_common_all ; 
 int /*<<< orphan*/  cz_golden_settings_a11 ; 
 int /*<<< orphan*/  cz_mgcg_cgcg_init ; 
 int /*<<< orphan*/  fiji_golden_common_all ; 
 int /*<<< orphan*/  fiji_mgcg_cgcg_init ; 
 int /*<<< orphan*/  golden_settings_fiji_a10 ; 
 int /*<<< orphan*/  golden_settings_iceland_a11 ; 
 int /*<<< orphan*/  golden_settings_polaris10_a11 ; 
 int /*<<< orphan*/  golden_settings_polaris11_a11 ; 
 int /*<<< orphan*/  golden_settings_tonga_a11 ; 
 int /*<<< orphan*/  golden_settings_vegam_a11 ; 
 int /*<<< orphan*/  iceland_golden_common_all ; 
 int /*<<< orphan*/  iceland_mgcg_cgcg_init ; 
 int /*<<< orphan*/  ixCG_ACLK_CNTL ; 
 int /*<<< orphan*/  polaris10_golden_common_all ; 
 int /*<<< orphan*/  polaris11_golden_common_all ; 
 int /*<<< orphan*/  stoney_golden_common_all ; 
 int /*<<< orphan*/  stoney_golden_settings_a11 ; 
 int /*<<< orphan*/  stoney_mgcg_cgcg_init ; 
 int /*<<< orphan*/  tonga_golden_common_all ; 
 int /*<<< orphan*/  tonga_mgcg_cgcg_init ; 
 int /*<<< orphan*/  vegam_golden_common_all ; 

__attribute__((used)) static void gfx_v8_0_init_golden_registers(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		amdgpu_device_program_register_sequence(adev,
							iceland_mgcg_cgcg_init,
							ARRAY_SIZE(iceland_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							golden_settings_iceland_a11,
							ARRAY_SIZE(golden_settings_iceland_a11));
		amdgpu_device_program_register_sequence(adev,
							iceland_golden_common_all,
							ARRAY_SIZE(iceland_golden_common_all));
		break;
	case CHIP_FIJI:
		amdgpu_device_program_register_sequence(adev,
							fiji_mgcg_cgcg_init,
							ARRAY_SIZE(fiji_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							golden_settings_fiji_a10,
							ARRAY_SIZE(golden_settings_fiji_a10));
		amdgpu_device_program_register_sequence(adev,
							fiji_golden_common_all,
							ARRAY_SIZE(fiji_golden_common_all));
		break;

	case CHIP_TONGA:
		amdgpu_device_program_register_sequence(adev,
							tonga_mgcg_cgcg_init,
							ARRAY_SIZE(tonga_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							golden_settings_tonga_a11,
							ARRAY_SIZE(golden_settings_tonga_a11));
		amdgpu_device_program_register_sequence(adev,
							tonga_golden_common_all,
							ARRAY_SIZE(tonga_golden_common_all));
		break;
	case CHIP_VEGAM:
		amdgpu_device_program_register_sequence(adev,
							golden_settings_vegam_a11,
							ARRAY_SIZE(golden_settings_vegam_a11));
		amdgpu_device_program_register_sequence(adev,
							vegam_golden_common_all,
							ARRAY_SIZE(vegam_golden_common_all));
		break;
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
		amdgpu_device_program_register_sequence(adev,
							golden_settings_polaris11_a11,
							ARRAY_SIZE(golden_settings_polaris11_a11));
		amdgpu_device_program_register_sequence(adev,
							polaris11_golden_common_all,
							ARRAY_SIZE(polaris11_golden_common_all));
		break;
	case CHIP_POLARIS10:
		amdgpu_device_program_register_sequence(adev,
							golden_settings_polaris10_a11,
							ARRAY_SIZE(golden_settings_polaris10_a11));
		amdgpu_device_program_register_sequence(adev,
							polaris10_golden_common_all,
							ARRAY_SIZE(polaris10_golden_common_all));
		WREG32_SMC(ixCG_ACLK_CNTL, 0x0000001C);
		if (adev->pdev->revision == 0xc7 &&
		    ((adev->pdev->subsystem_device == 0xb37 && adev->pdev->subsystem_vendor == 0x1002) ||
		     (adev->pdev->subsystem_device == 0x4a8 && adev->pdev->subsystem_vendor == 0x1043) ||
		     (adev->pdev->subsystem_device == 0x9480 && adev->pdev->subsystem_vendor == 0x1682))) {
			amdgpu_atombios_i2c_channel_trans(adev, 0x10, 0x96, 0x1E, 0xDD);
			amdgpu_atombios_i2c_channel_trans(adev, 0x10, 0x96, 0x1F, 0xD0);
		}
		break;
	case CHIP_CARRIZO:
		amdgpu_device_program_register_sequence(adev,
							cz_mgcg_cgcg_init,
							ARRAY_SIZE(cz_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							cz_golden_settings_a11,
							ARRAY_SIZE(cz_golden_settings_a11));
		amdgpu_device_program_register_sequence(adev,
							cz_golden_common_all,
							ARRAY_SIZE(cz_golden_common_all));
		break;
	case CHIP_STONEY:
		amdgpu_device_program_register_sequence(adev,
							stoney_mgcg_cgcg_init,
							ARRAY_SIZE(stoney_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							stoney_golden_settings_a11,
							ARRAY_SIZE(stoney_golden_settings_a11));
		amdgpu_device_program_register_sequence(adev,
							stoney_golden_common_all,
							ARRAY_SIZE(stoney_golden_common_all));
		break;
	default:
		break;
	}
}