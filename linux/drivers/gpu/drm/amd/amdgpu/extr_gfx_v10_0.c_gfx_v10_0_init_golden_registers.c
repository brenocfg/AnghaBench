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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {int asic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  CHIP_NAVI10 130 
#define  CHIP_NAVI12 129 
#define  CHIP_NAVI14 128 
 int /*<<< orphan*/  golden_settings_gc_10_0_nv10 ; 
 int /*<<< orphan*/  golden_settings_gc_10_1 ; 
 int /*<<< orphan*/  golden_settings_gc_10_1_1 ; 
 int /*<<< orphan*/  golden_settings_gc_10_1_2 ; 
 int /*<<< orphan*/  golden_settings_gc_10_1_2_nv12 ; 
 int /*<<< orphan*/  golden_settings_gc_10_1_nv14 ; 
 int /*<<< orphan*/  soc15_program_register_sequence (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void gfx_v10_0_init_golden_registers(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_NAVI10:
		soc15_program_register_sequence(adev,
						golden_settings_gc_10_1,
						(const u32)ARRAY_SIZE(golden_settings_gc_10_1));
		soc15_program_register_sequence(adev,
						golden_settings_gc_10_0_nv10,
						(const u32)ARRAY_SIZE(golden_settings_gc_10_0_nv10));
		break;
	case CHIP_NAVI14:
		soc15_program_register_sequence(adev,
						golden_settings_gc_10_1_1,
						(const u32)ARRAY_SIZE(golden_settings_gc_10_1_1));
		soc15_program_register_sequence(adev,
						golden_settings_gc_10_1_nv14,
						(const u32)ARRAY_SIZE(golden_settings_gc_10_1_nv14));
		break;
	case CHIP_NAVI12:
		soc15_program_register_sequence(adev,
						golden_settings_gc_10_1_2,
						(const u32)ARRAY_SIZE(golden_settings_gc_10_1_2));
		soc15_program_register_sequence(adev,
						golden_settings_gc_10_1_2_nv12,
						(const u32)ARRAY_SIZE(golden_settings_gc_10_1_2_nv12));
		break;
	default:
		break;
	}
}