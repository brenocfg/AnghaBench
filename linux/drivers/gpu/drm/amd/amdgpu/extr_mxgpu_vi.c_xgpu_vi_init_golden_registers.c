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
 int /*<<< orphan*/  BUG_ON (char*) ; 
#define  CHIP_FIJI 129 
#define  CHIP_TONGA 128 
 int /*<<< orphan*/  amdgpu_device_program_register_sequence (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgpu_fiji_golden_common_all ; 
 int /*<<< orphan*/  xgpu_fiji_golden_settings_a10 ; 
 int /*<<< orphan*/  xgpu_fiji_mgcg_cgcg_init ; 
 int /*<<< orphan*/  xgpu_tonga_golden_common_all ; 
 int /*<<< orphan*/  xgpu_tonga_golden_settings_a11 ; 
 int /*<<< orphan*/  xgpu_tonga_mgcg_cgcg_init ; 

void xgpu_vi_init_golden_registers(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_FIJI:
		amdgpu_device_program_register_sequence(adev,
							xgpu_fiji_mgcg_cgcg_init,
							ARRAY_SIZE(
								xgpu_fiji_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							xgpu_fiji_golden_settings_a10,
							ARRAY_SIZE(
								xgpu_fiji_golden_settings_a10));
		amdgpu_device_program_register_sequence(adev,
							xgpu_fiji_golden_common_all,
							ARRAY_SIZE(
								xgpu_fiji_golden_common_all));
		break;
	case CHIP_TONGA:
		amdgpu_device_program_register_sequence(adev,
							xgpu_tonga_mgcg_cgcg_init,
							ARRAY_SIZE(
								xgpu_tonga_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							xgpu_tonga_golden_settings_a11,
							ARRAY_SIZE(
								xgpu_tonga_golden_settings_a11));
		amdgpu_device_program_register_sequence(adev,
							xgpu_tonga_golden_common_all,
							ARRAY_SIZE(
								xgpu_tonga_golden_common_all));
		break;
	default:
		BUG_ON("Doesn't support chip type.\n");
		break;
	}
}