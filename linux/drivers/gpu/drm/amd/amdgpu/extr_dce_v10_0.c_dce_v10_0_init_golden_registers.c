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
#define  CHIP_FIJI 129 
#define  CHIP_TONGA 128 
 int /*<<< orphan*/  amdgpu_device_program_register_sequence (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fiji_mgcg_cgcg_init ; 
 int /*<<< orphan*/  golden_settings_fiji_a10 ; 
 int /*<<< orphan*/  golden_settings_tonga_a11 ; 
 int /*<<< orphan*/  tonga_mgcg_cgcg_init ; 

__attribute__((used)) static void dce_v10_0_init_golden_registers(struct amdgpu_device *adev)
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
	default:
		break;
	}
}