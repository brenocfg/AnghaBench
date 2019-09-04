#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct smu7_smumgr {void* ulv_setting_starts; void* arb_table_start; void* fan_table_start; void* mc_reg_table_start; void* soft_regs_start; void* dpm_table_start; } ;
struct smu7_hwmgr {void* soft_regs_start; } ;
struct TYPE_2__ {void* SMC; } ;
struct pp_hwmgr {TYPE_1__ microcode_version_info; scalar_t__ smu_backend; scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  DpmTable ; 
 int /*<<< orphan*/  FanTable ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 scalar_t__ SMU71_FIRMWARE_HEADER_LOCATION ; 
 int /*<<< orphan*/  SMU71_Firmware_Header ; 
 int /*<<< orphan*/  SoftRegisters ; 
 int /*<<< orphan*/  UlvSettings ; 
 int /*<<< orphan*/  Version ; 
 int /*<<< orphan*/  mcArbDramTimingTable ; 
 int /*<<< orphan*/  mcRegisterTable ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smu7_read_smc_sram_dword (struct pp_hwmgr*,scalar_t__,void**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iceland_process_firmware_header(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct smu7_smumgr *smu7_data = (struct smu7_smumgr *)(hwmgr->smu_backend);

	uint32_t tmp;
	int result;
	bool error = false;

	result = smu7_read_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				offsetof(SMU71_Firmware_Header, DpmTable),
				&tmp, SMC_RAM_END);

	if (0 == result) {
		smu7_data->dpm_table_start = tmp;
	}

	error |= (0 != result);

	result = smu7_read_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				offsetof(SMU71_Firmware_Header, SoftRegisters),
				&tmp, SMC_RAM_END);

	if (0 == result) {
		data->soft_regs_start = tmp;
		smu7_data->soft_regs_start = tmp;
	}

	error |= (0 != result);


	result = smu7_read_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				offsetof(SMU71_Firmware_Header, mcRegisterTable),
				&tmp, SMC_RAM_END);

	if (0 == result) {
		smu7_data->mc_reg_table_start = tmp;
	}

	result = smu7_read_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				offsetof(SMU71_Firmware_Header, FanTable),
				&tmp, SMC_RAM_END);

	if (0 == result) {
		smu7_data->fan_table_start = tmp;
	}

	error |= (0 != result);

	result = smu7_read_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				offsetof(SMU71_Firmware_Header, mcArbDramTimingTable),
				&tmp, SMC_RAM_END);

	if (0 == result) {
		smu7_data->arb_table_start = tmp;
	}

	error |= (0 != result);


	result = smu7_read_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				offsetof(SMU71_Firmware_Header, Version),
				&tmp, SMC_RAM_END);

	if (0 == result) {
		hwmgr->microcode_version_info.SMC = tmp;
	}

	error |= (0 != result);

	result = smu7_read_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				offsetof(SMU71_Firmware_Header, UlvSettings),
				&tmp, SMC_RAM_END);

	if (0 == result) {
		smu7_data->ulv_setting_starts = tmp;
	}

	error |= (0 != result);

	return error ? 1 : 0;
}