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
typedef  void* u32 ;
struct radeon_device {int dummy; } ;
struct ci_power_info {void* arb_table_start; int /*<<< orphan*/  sram_end; void* fan_table_start; void* mc_reg_table_start; void* soft_regs_start; void* dpm_table_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DpmTable ; 
 int /*<<< orphan*/  FanTable ; 
 scalar_t__ SMU7_FIRMWARE_HEADER_LOCATION ; 
 int /*<<< orphan*/  SMU7_Firmware_Header ; 
 int /*<<< orphan*/  SoftRegisters ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int ci_read_smc_sram_dword (struct radeon_device*,scalar_t__,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcArbDramTimingTable ; 
 int /*<<< orphan*/  mcRegisterTable ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_process_firmware_header(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	u32 tmp;
	int ret;

	ret = ci_read_smc_sram_dword(rdev,
				     SMU7_FIRMWARE_HEADER_LOCATION +
				     offsetof(SMU7_Firmware_Header, DpmTable),
				     &tmp, pi->sram_end);
	if (ret)
		return ret;

	pi->dpm_table_start = tmp;

	ret = ci_read_smc_sram_dword(rdev,
				     SMU7_FIRMWARE_HEADER_LOCATION +
				     offsetof(SMU7_Firmware_Header, SoftRegisters),
				     &tmp, pi->sram_end);
	if (ret)
		return ret;

	pi->soft_regs_start = tmp;

	ret = ci_read_smc_sram_dword(rdev,
				     SMU7_FIRMWARE_HEADER_LOCATION +
				     offsetof(SMU7_Firmware_Header, mcRegisterTable),
				     &tmp, pi->sram_end);
	if (ret)
		return ret;

	pi->mc_reg_table_start = tmp;

	ret = ci_read_smc_sram_dword(rdev,
				     SMU7_FIRMWARE_HEADER_LOCATION +
				     offsetof(SMU7_Firmware_Header, FanTable),
				     &tmp, pi->sram_end);
	if (ret)
		return ret;

	pi->fan_table_start = tmp;

	ret = ci_read_smc_sram_dword(rdev,
				     SMU7_FIRMWARE_HEADER_LOCATION +
				     offsetof(SMU7_Firmware_Header, mcArbDramTimingTable),
				     &tmp, pi->sram_end);
	if (ret)
		return ret;

	pi->arb_table_start = tmp;

	return 0;
}