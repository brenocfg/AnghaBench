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
typedef  scalar_t__ u32 ;
struct amdgpu_device {int asic_type; int rev_id; } ;

/* Variables and functions */
 scalar_t__ const ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  CHIP_ARCTURUS 133 
#define  CHIP_RAVEN 132 
#define  CHIP_RENOIR 131 
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  golden_settings_gc_9_0 ; 
 int /*<<< orphan*/  golden_settings_gc_9_0_vg10 ; 
 int /*<<< orphan*/  golden_settings_gc_9_0_vg20 ; 
 int /*<<< orphan*/  golden_settings_gc_9_1 ; 
 int /*<<< orphan*/  golden_settings_gc_9_1_rn ; 
 int /*<<< orphan*/  golden_settings_gc_9_1_rv1 ; 
 int /*<<< orphan*/  golden_settings_gc_9_1_rv2 ; 
 int /*<<< orphan*/  golden_settings_gc_9_2_1 ; 
 int /*<<< orphan*/  golden_settings_gc_9_2_1_vg12 ; 
 int /*<<< orphan*/  golden_settings_gc_9_4_1_arct ; 
 int /*<<< orphan*/  golden_settings_gc_9_x_common ; 
 int /*<<< orphan*/  soc15_program_register_sequence (struct amdgpu_device*,int /*<<< orphan*/ ,scalar_t__ const) ; 

__attribute__((used)) static void gfx_v9_0_init_golden_registers(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_VEGA10:
		soc15_program_register_sequence(adev,
						golden_settings_gc_9_0,
						ARRAY_SIZE(golden_settings_gc_9_0));
		soc15_program_register_sequence(adev,
						golden_settings_gc_9_0_vg10,
						ARRAY_SIZE(golden_settings_gc_9_0_vg10));
		break;
	case CHIP_VEGA12:
		soc15_program_register_sequence(adev,
						golden_settings_gc_9_2_1,
						ARRAY_SIZE(golden_settings_gc_9_2_1));
		soc15_program_register_sequence(adev,
						golden_settings_gc_9_2_1_vg12,
						ARRAY_SIZE(golden_settings_gc_9_2_1_vg12));
		break;
	case CHIP_VEGA20:
		soc15_program_register_sequence(adev,
						golden_settings_gc_9_0,
						ARRAY_SIZE(golden_settings_gc_9_0));
		soc15_program_register_sequence(adev,
						golden_settings_gc_9_0_vg20,
						ARRAY_SIZE(golden_settings_gc_9_0_vg20));
		break;
	case CHIP_ARCTURUS:
		soc15_program_register_sequence(adev,
						golden_settings_gc_9_4_1_arct,
						ARRAY_SIZE(golden_settings_gc_9_4_1_arct));
		break;
	case CHIP_RAVEN:
		soc15_program_register_sequence(adev, golden_settings_gc_9_1,
						ARRAY_SIZE(golden_settings_gc_9_1));
		if (adev->rev_id >= 8)
			soc15_program_register_sequence(adev,
							golden_settings_gc_9_1_rv2,
							ARRAY_SIZE(golden_settings_gc_9_1_rv2));
		else
			soc15_program_register_sequence(adev,
							golden_settings_gc_9_1_rv1,
							ARRAY_SIZE(golden_settings_gc_9_1_rv1));
		break;
	 case CHIP_RENOIR:
		soc15_program_register_sequence(adev,
						golden_settings_gc_9_1_rn,
						ARRAY_SIZE(golden_settings_gc_9_1_rn));
		return; /* for renoir, don't need common goldensetting */
	default:
		break;
	}

	if (adev->asic_type != CHIP_ARCTURUS)
		soc15_program_register_sequence(adev, golden_settings_gc_9_x_common,
						(const u32)ARRAY_SIZE(golden_settings_gc_9_x_common));
}