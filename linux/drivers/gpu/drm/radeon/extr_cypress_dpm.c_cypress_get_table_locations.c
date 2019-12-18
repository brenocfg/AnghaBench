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
typedef  void* u16 ;
struct rv7xx_power_info {int /*<<< orphan*/  sram_end; void* soft_regs_start; void* state_table_start; } ;
struct radeon_device {int dummy; } ;
struct evergreen_power_info {void* mc_reg_table_start; } ;

/* Variables and functions */
 scalar_t__ EVERGREEN_SMC_FIRMWARE_HEADER_LOCATION ; 
 scalar_t__ EVERGREEN_SMC_FIRMWARE_HEADER_mcRegisterTable ; 
 scalar_t__ EVERGREEN_SMC_FIRMWARE_HEADER_softRegisters ; 
 scalar_t__ EVERGREEN_SMC_FIRMWARE_HEADER_stateTable ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int rv770_read_smc_sram_dword (struct radeon_device*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 

int cypress_get_table_locations(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	u32 tmp;
	int ret;

	ret = rv770_read_smc_sram_dword(rdev,
					EVERGREEN_SMC_FIRMWARE_HEADER_LOCATION +
					EVERGREEN_SMC_FIRMWARE_HEADER_stateTable,
					&tmp, pi->sram_end);
	if (ret)
		return ret;

	pi->state_table_start = (u16)tmp;

	ret = rv770_read_smc_sram_dword(rdev,
					EVERGREEN_SMC_FIRMWARE_HEADER_LOCATION +
					EVERGREEN_SMC_FIRMWARE_HEADER_softRegisters,
					&tmp, pi->sram_end);
	if (ret)
		return ret;

	pi->soft_regs_start = (u16)tmp;

	ret = rv770_read_smc_sram_dword(rdev,
					EVERGREEN_SMC_FIRMWARE_HEADER_LOCATION +
					EVERGREEN_SMC_FIRMWARE_HEADER_mcRegisterTable,
					&tmp, pi->sram_end);
	if (ret)
		return ret;

	eg_pi->mc_reg_table_start = (u16)tmp;

	return 0;
}