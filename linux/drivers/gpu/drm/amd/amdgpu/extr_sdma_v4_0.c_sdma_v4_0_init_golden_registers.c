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
struct amdgpu_device {int asic_type; int rev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  CHIP_ARCTURUS 133 
#define  CHIP_RAVEN 132 
#define  CHIP_RENOIR 131 
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  golden_settings_sdma0_4_2 ; 
 int /*<<< orphan*/  golden_settings_sdma0_4_2_init ; 
 int /*<<< orphan*/  golden_settings_sdma1_4_2 ; 
 int /*<<< orphan*/  golden_settings_sdma_4 ; 
 int /*<<< orphan*/  golden_settings_sdma_4_1 ; 
 int /*<<< orphan*/  golden_settings_sdma_4_3 ; 
 int /*<<< orphan*/  golden_settings_sdma_arct ; 
 int /*<<< orphan*/  golden_settings_sdma_rv1 ; 
 int /*<<< orphan*/  golden_settings_sdma_rv2 ; 
 int /*<<< orphan*/  golden_settings_sdma_vg10 ; 
 int /*<<< orphan*/  golden_settings_sdma_vg12 ; 
 int /*<<< orphan*/  soc15_program_register_sequence (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdma_v4_0_init_golden_registers(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_VEGA10:
		soc15_program_register_sequence(adev,
						golden_settings_sdma_4,
						ARRAY_SIZE(golden_settings_sdma_4));
		soc15_program_register_sequence(adev,
						golden_settings_sdma_vg10,
						ARRAY_SIZE(golden_settings_sdma_vg10));
		break;
	case CHIP_VEGA12:
		soc15_program_register_sequence(adev,
						golden_settings_sdma_4,
						ARRAY_SIZE(golden_settings_sdma_4));
		soc15_program_register_sequence(adev,
						golden_settings_sdma_vg12,
						ARRAY_SIZE(golden_settings_sdma_vg12));
		break;
	case CHIP_VEGA20:
		soc15_program_register_sequence(adev,
						golden_settings_sdma0_4_2_init,
						ARRAY_SIZE(golden_settings_sdma0_4_2_init));
		soc15_program_register_sequence(adev,
						golden_settings_sdma0_4_2,
						ARRAY_SIZE(golden_settings_sdma0_4_2));
		soc15_program_register_sequence(adev,
						golden_settings_sdma1_4_2,
						ARRAY_SIZE(golden_settings_sdma1_4_2));
		break;
	case CHIP_ARCTURUS:
		soc15_program_register_sequence(adev,
						golden_settings_sdma_arct,
						ARRAY_SIZE(golden_settings_sdma_arct));
		break;
	case CHIP_RAVEN:
		soc15_program_register_sequence(adev,
						golden_settings_sdma_4_1,
						ARRAY_SIZE(golden_settings_sdma_4_1));
		if (adev->rev_id >= 8)
			soc15_program_register_sequence(adev,
							golden_settings_sdma_rv2,
							ARRAY_SIZE(golden_settings_sdma_rv2));
		else
			soc15_program_register_sequence(adev,
							golden_settings_sdma_rv1,
							ARRAY_SIZE(golden_settings_sdma_rv1));
		break;
	case CHIP_RENOIR:
		soc15_program_register_sequence(adev,
						golden_settings_sdma_4_3,
						ARRAY_SIZE(golden_settings_sdma_4_3));
		break;
	default:
		break;
	}
}