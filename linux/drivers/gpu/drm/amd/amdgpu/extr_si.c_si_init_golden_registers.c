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
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_HAINAN 132 
#define  CHIP_OLAND 131 
#define  CHIP_PITCAIRN 130 
#define  CHIP_TAHITI 129 
#define  CHIP_VERDE 128 
 int /*<<< orphan*/  amdgpu_device_program_register_sequence (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hainan_golden_registers ; 
 int /*<<< orphan*/  hainan_golden_registers2 ; 
 int /*<<< orphan*/  hainan_mgcg_cgcg_init ; 
 int /*<<< orphan*/  oland_golden_registers ; 
 int /*<<< orphan*/  oland_golden_rlc_registers ; 
 int /*<<< orphan*/  oland_mgcg_cgcg_init ; 
 int /*<<< orphan*/  pitcairn_golden_registers ; 
 int /*<<< orphan*/  pitcairn_golden_rlc_registers ; 
 int /*<<< orphan*/  pitcairn_mgcg_cgcg_init ; 
 int /*<<< orphan*/  tahiti_golden_registers ; 
 int /*<<< orphan*/  tahiti_golden_registers2 ; 
 int /*<<< orphan*/  tahiti_golden_rlc_registers ; 
 int /*<<< orphan*/  tahiti_mgcg_cgcg_init ; 
 int /*<<< orphan*/  verde_golden_registers ; 
 int /*<<< orphan*/  verde_golden_rlc_registers ; 
 int /*<<< orphan*/  verde_mgcg_cgcg_init ; 
 int /*<<< orphan*/  verde_pg_init ; 

__attribute__((used)) static void si_init_golden_registers(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_TAHITI:
		amdgpu_device_program_register_sequence(adev,
							tahiti_golden_registers,
							ARRAY_SIZE(tahiti_golden_registers));
		amdgpu_device_program_register_sequence(adev,
							tahiti_golden_rlc_registers,
							ARRAY_SIZE(tahiti_golden_rlc_registers));
		amdgpu_device_program_register_sequence(adev,
							tahiti_mgcg_cgcg_init,
							ARRAY_SIZE(tahiti_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							tahiti_golden_registers2,
							ARRAY_SIZE(tahiti_golden_registers2));
		break;
	case CHIP_PITCAIRN:
		amdgpu_device_program_register_sequence(adev,
							pitcairn_golden_registers,
							ARRAY_SIZE(pitcairn_golden_registers));
		amdgpu_device_program_register_sequence(adev,
							pitcairn_golden_rlc_registers,
							ARRAY_SIZE(pitcairn_golden_rlc_registers));
		amdgpu_device_program_register_sequence(adev,
							pitcairn_mgcg_cgcg_init,
							ARRAY_SIZE(pitcairn_mgcg_cgcg_init));
		break;
	case CHIP_VERDE:
		amdgpu_device_program_register_sequence(adev,
							verde_golden_registers,
							ARRAY_SIZE(verde_golden_registers));
		amdgpu_device_program_register_sequence(adev,
							verde_golden_rlc_registers,
							ARRAY_SIZE(verde_golden_rlc_registers));
		amdgpu_device_program_register_sequence(adev,
							verde_mgcg_cgcg_init,
							ARRAY_SIZE(verde_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							verde_pg_init,
							ARRAY_SIZE(verde_pg_init));
		break;
	case CHIP_OLAND:
		amdgpu_device_program_register_sequence(adev,
							oland_golden_registers,
							ARRAY_SIZE(oland_golden_registers));
		amdgpu_device_program_register_sequence(adev,
							oland_golden_rlc_registers,
							ARRAY_SIZE(oland_golden_rlc_registers));
		amdgpu_device_program_register_sequence(adev,
							oland_mgcg_cgcg_init,
							ARRAY_SIZE(oland_mgcg_cgcg_init));
		break;
	case CHIP_HAINAN:
		amdgpu_device_program_register_sequence(adev,
							hainan_golden_registers,
							ARRAY_SIZE(hainan_golden_registers));
		amdgpu_device_program_register_sequence(adev,
							hainan_golden_registers2,
							ARRAY_SIZE(hainan_golden_registers2));
		amdgpu_device_program_register_sequence(adev,
							hainan_mgcg_cgcg_init,
							ARRAY_SIZE(hainan_mgcg_cgcg_init));
		break;


	default:
		BUG();
	}
}