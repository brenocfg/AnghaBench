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
#define  CHIP_BARTS 138 
#define  CHIP_CAICOS 137 
#define  CHIP_CEDAR 136 
#define  CHIP_CYPRESS 135 
#define  CHIP_HEMLOCK 134 
#define  CHIP_JUNIPER 133 
#define  CHIP_PALM 132 
#define  CHIP_REDWOOD 131 
#define  CHIP_SUMO 130 
#define  CHIP_SUMO2 129 
#define  CHIP_TURKS 128 
 int /*<<< orphan*/  barts_golden_registers ; 
 int /*<<< orphan*/  caicos_golden_registers ; 
 int /*<<< orphan*/  cedar_golden_registers ; 
 int /*<<< orphan*/  cedar_mgcg_init ; 
 int /*<<< orphan*/  cypress_mgcg_init ; 
 int /*<<< orphan*/  evergreen_golden_registers ; 
 int /*<<< orphan*/  evergreen_golden_registers2 ; 
 int /*<<< orphan*/  juniper_mgcg_init ; 
 int /*<<< orphan*/  radeon_program_register_sequence (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  redwood_mgcg_init ; 
 int /*<<< orphan*/  sumo_golden_registers ; 
 int /*<<< orphan*/  supersumo_golden_registers ; 
 int /*<<< orphan*/  turks_golden_registers ; 
 int /*<<< orphan*/  wrestler_golden_registers ; 

__attribute__((used)) static void evergreen_init_golden_registers(struct radeon_device *rdev)
{
	switch (rdev->family) {
	case CHIP_CYPRESS:
	case CHIP_HEMLOCK:
		radeon_program_register_sequence(rdev,
						 evergreen_golden_registers,
						 (const u32)ARRAY_SIZE(evergreen_golden_registers));
		radeon_program_register_sequence(rdev,
						 evergreen_golden_registers2,
						 (const u32)ARRAY_SIZE(evergreen_golden_registers2));
		radeon_program_register_sequence(rdev,
						 cypress_mgcg_init,
						 (const u32)ARRAY_SIZE(cypress_mgcg_init));
		break;
	case CHIP_JUNIPER:
		radeon_program_register_sequence(rdev,
						 evergreen_golden_registers,
						 (const u32)ARRAY_SIZE(evergreen_golden_registers));
		radeon_program_register_sequence(rdev,
						 evergreen_golden_registers2,
						 (const u32)ARRAY_SIZE(evergreen_golden_registers2));
		radeon_program_register_sequence(rdev,
						 juniper_mgcg_init,
						 (const u32)ARRAY_SIZE(juniper_mgcg_init));
		break;
	case CHIP_REDWOOD:
		radeon_program_register_sequence(rdev,
						 evergreen_golden_registers,
						 (const u32)ARRAY_SIZE(evergreen_golden_registers));
		radeon_program_register_sequence(rdev,
						 evergreen_golden_registers2,
						 (const u32)ARRAY_SIZE(evergreen_golden_registers2));
		radeon_program_register_sequence(rdev,
						 redwood_mgcg_init,
						 (const u32)ARRAY_SIZE(redwood_mgcg_init));
		break;
	case CHIP_CEDAR:
		radeon_program_register_sequence(rdev,
						 cedar_golden_registers,
						 (const u32)ARRAY_SIZE(cedar_golden_registers));
		radeon_program_register_sequence(rdev,
						 evergreen_golden_registers2,
						 (const u32)ARRAY_SIZE(evergreen_golden_registers2));
		radeon_program_register_sequence(rdev,
						 cedar_mgcg_init,
						 (const u32)ARRAY_SIZE(cedar_mgcg_init));
		break;
	case CHIP_PALM:
		radeon_program_register_sequence(rdev,
						 wrestler_golden_registers,
						 (const u32)ARRAY_SIZE(wrestler_golden_registers));
		break;
	case CHIP_SUMO:
		radeon_program_register_sequence(rdev,
						 supersumo_golden_registers,
						 (const u32)ARRAY_SIZE(supersumo_golden_registers));
		break;
	case CHIP_SUMO2:
		radeon_program_register_sequence(rdev,
						 supersumo_golden_registers,
						 (const u32)ARRAY_SIZE(supersumo_golden_registers));
		radeon_program_register_sequence(rdev,
						 sumo_golden_registers,
						 (const u32)ARRAY_SIZE(sumo_golden_registers));
		break;
	case CHIP_BARTS:
		radeon_program_register_sequence(rdev,
						 barts_golden_registers,
						 (const u32)ARRAY_SIZE(barts_golden_registers));
		break;
	case CHIP_TURKS:
		radeon_program_register_sequence(rdev,
						 turks_golden_registers,
						 (const u32)ARRAY_SIZE(turks_golden_registers));
		break;
	case CHIP_CAICOS:
		radeon_program_register_sequence(rdev,
						 caicos_golden_registers,
						 (const u32)ARRAY_SIZE(caicos_golden_registers));
		break;
	default:
		break;
	}
}