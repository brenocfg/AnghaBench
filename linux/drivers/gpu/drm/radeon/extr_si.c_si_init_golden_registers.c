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
struct radeon_device {int family; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  CHIP_HAINAN 132 
#define  CHIP_OLAND 131 
#define  CHIP_PITCAIRN 130 
#define  CHIP_TAHITI 129 
#define  CHIP_VERDE 128 
 int /*<<< orphan*/  hainan_golden_registers ; 
 int /*<<< orphan*/  hainan_golden_registers2 ; 
 int /*<<< orphan*/  hainan_mgcg_cgcg_init ; 
 int /*<<< orphan*/  oland_golden_registers ; 
 int /*<<< orphan*/  oland_golden_rlc_registers ; 
 int /*<<< orphan*/  oland_mgcg_cgcg_init ; 
 int /*<<< orphan*/  pitcairn_golden_registers ; 
 int /*<<< orphan*/  pitcairn_golden_rlc_registers ; 
 int /*<<< orphan*/  pitcairn_mgcg_cgcg_init ; 
 int /*<<< orphan*/  radeon_program_register_sequence (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  tahiti_golden_registers ; 
 int /*<<< orphan*/  tahiti_golden_registers2 ; 
 int /*<<< orphan*/  tahiti_golden_rlc_registers ; 
 int /*<<< orphan*/  tahiti_mgcg_cgcg_init ; 
 int /*<<< orphan*/  verde_golden_registers ; 
 int /*<<< orphan*/  verde_golden_rlc_registers ; 
 int /*<<< orphan*/  verde_mgcg_cgcg_init ; 
 int /*<<< orphan*/  verde_pg_init ; 

__attribute__((used)) static void si_init_golden_registers(struct radeon_device *rdev)
{
	switch (rdev->family) {
	case CHIP_TAHITI:
		radeon_program_register_sequence(rdev,
						 tahiti_golden_registers,
						 (const u32)ARRAY_SIZE(tahiti_golden_registers));
		radeon_program_register_sequence(rdev,
						 tahiti_golden_rlc_registers,
						 (const u32)ARRAY_SIZE(tahiti_golden_rlc_registers));
		radeon_program_register_sequence(rdev,
						 tahiti_mgcg_cgcg_init,
						 (const u32)ARRAY_SIZE(tahiti_mgcg_cgcg_init));
		radeon_program_register_sequence(rdev,
						 tahiti_golden_registers2,
						 (const u32)ARRAY_SIZE(tahiti_golden_registers2));
		break;
	case CHIP_PITCAIRN:
		radeon_program_register_sequence(rdev,
						 pitcairn_golden_registers,
						 (const u32)ARRAY_SIZE(pitcairn_golden_registers));
		radeon_program_register_sequence(rdev,
						 pitcairn_golden_rlc_registers,
						 (const u32)ARRAY_SIZE(pitcairn_golden_rlc_registers));
		radeon_program_register_sequence(rdev,
						 pitcairn_mgcg_cgcg_init,
						 (const u32)ARRAY_SIZE(pitcairn_mgcg_cgcg_init));
		break;
	case CHIP_VERDE:
		radeon_program_register_sequence(rdev,
						 verde_golden_registers,
						 (const u32)ARRAY_SIZE(verde_golden_registers));
		radeon_program_register_sequence(rdev,
						 verde_golden_rlc_registers,
						 (const u32)ARRAY_SIZE(verde_golden_rlc_registers));
		radeon_program_register_sequence(rdev,
						 verde_mgcg_cgcg_init,
						 (const u32)ARRAY_SIZE(verde_mgcg_cgcg_init));
		radeon_program_register_sequence(rdev,
						 verde_pg_init,
						 (const u32)ARRAY_SIZE(verde_pg_init));
		break;
	case CHIP_OLAND:
		radeon_program_register_sequence(rdev,
						 oland_golden_registers,
						 (const u32)ARRAY_SIZE(oland_golden_registers));
		radeon_program_register_sequence(rdev,
						 oland_golden_rlc_registers,
						 (const u32)ARRAY_SIZE(oland_golden_rlc_registers));
		radeon_program_register_sequence(rdev,
						 oland_mgcg_cgcg_init,
						 (const u32)ARRAY_SIZE(oland_mgcg_cgcg_init));
		break;
	case CHIP_HAINAN:
		radeon_program_register_sequence(rdev,
						 hainan_golden_registers,
						 (const u32)ARRAY_SIZE(hainan_golden_registers));
		radeon_program_register_sequence(rdev,
						 hainan_golden_registers2,
						 (const u32)ARRAY_SIZE(hainan_golden_registers2));
		radeon_program_register_sequence(rdev,
						 hainan_mgcg_cgcg_init,
						 (const u32)ARRAY_SIZE(hainan_mgcg_cgcg_init));
		break;
	default:
		break;
	}
}