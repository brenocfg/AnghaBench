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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  CHIP_CARRIZO 135 
#define  CHIP_FIJI 134 
#define  CHIP_POLARIS10 133 
#define  CHIP_POLARIS11 132 
#define  CHIP_POLARIS12 131 
#define  CHIP_STONEY 130 
#define  CHIP_TONGA 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  amdgpu_device_program_register_sequence (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cz_golden_settings_a11 ; 
 int /*<<< orphan*/  cz_mgcg_cgcg_init ; 
 int /*<<< orphan*/  fiji_mgcg_cgcg_init ; 
 int /*<<< orphan*/  golden_settings_fiji_a10 ; 
 int /*<<< orphan*/  golden_settings_polaris10_a11 ; 
 int /*<<< orphan*/  golden_settings_polaris11_a11 ; 
 int /*<<< orphan*/  golden_settings_tonga_a11 ; 
 int /*<<< orphan*/  stoney_golden_settings_a11 ; 
 int /*<<< orphan*/  stoney_mgcg_cgcg_init ; 
 int /*<<< orphan*/  tonga_mgcg_cgcg_init ; 

__attribute__((used)) static void sdma_v3_0_init_golden_registers(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_FIJI:
		amdgpu_device_program_register_sequence(adev,
							fiji_mgcg_cgcg_init,
							ARRAY_SIZE(fiji_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							golden_settings_fiji_a10,
							ARRAY_SIZE(golden_settings_fiji_a10));
		break;
	case CHIP_TONGA:
		amdgpu_device_program_register_sequence(adev,
							tonga_mgcg_cgcg_init,
							ARRAY_SIZE(tonga_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							golden_settings_tonga_a11,
							ARRAY_SIZE(golden_settings_tonga_a11));
		break;
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
	case CHIP_VEGAM:
		amdgpu_device_program_register_sequence(adev,
							golden_settings_polaris11_a11,
							ARRAY_SIZE(golden_settings_polaris11_a11));
		break;
	case CHIP_POLARIS10:
		amdgpu_device_program_register_sequence(adev,
							golden_settings_polaris10_a11,
							ARRAY_SIZE(golden_settings_polaris10_a11));
		break;
	case CHIP_CARRIZO:
		amdgpu_device_program_register_sequence(adev,
							cz_mgcg_cgcg_init,
							ARRAY_SIZE(cz_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							cz_golden_settings_a11,
							ARRAY_SIZE(cz_golden_settings_a11));
		break;
	case CHIP_STONEY:
		amdgpu_device_program_register_sequence(adev,
							stoney_mgcg_cgcg_init,
							ARRAY_SIZE(stoney_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							stoney_golden_settings_a11,
							ARRAY_SIZE(stoney_golden_settings_a11));
		break;
	default:
		break;
	}
}