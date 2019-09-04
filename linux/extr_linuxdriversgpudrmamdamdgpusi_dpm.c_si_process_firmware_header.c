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
struct si_power_info {void* papm_cfg_table_start; int /*<<< orphan*/  sram_end; void* spll_table_start; void* dte_table_start; void* cac_table_start; void* arb_table_start; void* fan_table_start; void* mc_reg_table_start; void* soft_regs_start; void* state_table_start; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SISLANDS_SMC_FIRMWARE_HEADER_CacConfigTable ; 
 scalar_t__ SISLANDS_SMC_FIRMWARE_HEADER_DteConfiguration ; 
 scalar_t__ SISLANDS_SMC_FIRMWARE_HEADER_LOCATION ; 
 scalar_t__ SISLANDS_SMC_FIRMWARE_HEADER_PAPMParameters ; 
 scalar_t__ SISLANDS_SMC_FIRMWARE_HEADER_fanTable ; 
 scalar_t__ SISLANDS_SMC_FIRMWARE_HEADER_mcArbDramAutoRefreshTable ; 
 scalar_t__ SISLANDS_SMC_FIRMWARE_HEADER_mcRegisterTable ; 
 scalar_t__ SISLANDS_SMC_FIRMWARE_HEADER_softRegisters ; 
 scalar_t__ SISLANDS_SMC_FIRMWARE_HEADER_spllTable ; 
 scalar_t__ SISLANDS_SMC_FIRMWARE_HEADER_stateTable ; 
 int amdgpu_si_read_smc_sram_dword (struct amdgpu_device*,scalar_t__,void**,int /*<<< orphan*/ ) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int si_process_firmware_header(struct amdgpu_device *adev)
{
	struct si_power_info *si_pi = si_get_pi(adev);
	u32 tmp;
	int ret;

	ret = amdgpu_si_read_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_stateTable,
					    &tmp, si_pi->sram_end);
	if (ret)
		return ret;

	si_pi->state_table_start = tmp;

	ret = amdgpu_si_read_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_softRegisters,
					    &tmp, si_pi->sram_end);
	if (ret)
		return ret;

	si_pi->soft_regs_start = tmp;

	ret = amdgpu_si_read_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_mcRegisterTable,
					    &tmp, si_pi->sram_end);
	if (ret)
		return ret;

	si_pi->mc_reg_table_start = tmp;

	ret = amdgpu_si_read_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_fanTable,
					    &tmp, si_pi->sram_end);
	if (ret)
		return ret;

	si_pi->fan_table_start = tmp;

	ret = amdgpu_si_read_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_mcArbDramAutoRefreshTable,
					    &tmp, si_pi->sram_end);
	if (ret)
		return ret;

	si_pi->arb_table_start = tmp;

	ret = amdgpu_si_read_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_CacConfigTable,
					    &tmp, si_pi->sram_end);
	if (ret)
		return ret;

	si_pi->cac_table_start = tmp;

	ret = amdgpu_si_read_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_DteConfiguration,
					    &tmp, si_pi->sram_end);
	if (ret)
		return ret;

	si_pi->dte_table_start = tmp;

	ret = amdgpu_si_read_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_spllTable,
					    &tmp, si_pi->sram_end);
	if (ret)
		return ret;

	si_pi->spll_table_start = tmp;

	ret = amdgpu_si_read_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_PAPMParameters,
					    &tmp, si_pi->sram_end);
	if (ret)
		return ret;

	si_pi->papm_cfg_table_start = tmp;

	return ret;
}