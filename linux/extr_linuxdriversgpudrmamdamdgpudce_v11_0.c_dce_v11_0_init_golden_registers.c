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
#define  CHIP_CARRIZO 133 
#define  CHIP_POLARIS10 132 
#define  CHIP_POLARIS11 131 
#define  CHIP_POLARIS12 130 
#define  CHIP_STONEY 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  amdgpu_device_program_register_sequence (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cz_golden_settings_a11 ; 
 int /*<<< orphan*/  cz_mgcg_cgcg_init ; 
 int /*<<< orphan*/  polaris10_golden_settings_a11 ; 
 int /*<<< orphan*/  polaris11_golden_settings_a11 ; 
 int /*<<< orphan*/  stoney_golden_settings_a11 ; 

__attribute__((used)) static void dce_v11_0_init_golden_registers(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
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
							stoney_golden_settings_a11,
							ARRAY_SIZE(stoney_golden_settings_a11));
		break;
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
		amdgpu_device_program_register_sequence(adev,
							polaris11_golden_settings_a11,
							ARRAY_SIZE(polaris11_golden_settings_a11));
		break;
	case CHIP_POLARIS10:
	case CHIP_VEGAM:
		amdgpu_device_program_register_sequence(adev,
							polaris10_golden_settings_a11,
							ARRAY_SIZE(polaris10_golden_settings_a11));
		break;
	default:
		break;
	}
}