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
struct smu8_smumgr {unsigned long scratch_buffer_length; int /*<<< orphan*/  toc_entry_clock_table; TYPE_1__* scratch_buffer; } ;
struct pp_hwmgr {struct smu8_smumgr* smu_backend; } ;
struct TYPE_2__ {scalar_t__ firmware_ID; int /*<<< orphan*/  mc_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_ClkTableXferToSmu ; 
 int /*<<< orphan*/  PPSMC_MSG_ExecuteJob ; 
 int /*<<< orphan*/  PPSMC_MSG_SetClkTableAddrHi ; 
 int /*<<< orphan*/  PPSMC_MSG_SetClkTableAddrLo ; 
 scalar_t__ SMU8_SCRATCH_ENTRY_SMU8_FUSION_CLKTABLE ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu8_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu8_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_upload_pptable_settings(struct pp_hwmgr *hwmgr)
{
	struct smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	unsigned long i;

	for (i = 0; i < smu8_smu->scratch_buffer_length; i++) {
		if (smu8_smu->scratch_buffer[i].firmware_ID
				== SMU8_SCRATCH_ENTRY_SMU8_FUSION_CLKTABLE)
			break;
	}

	smu8_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetClkTableAddrHi,
				upper_32_bits(smu8_smu->scratch_buffer[i].mc_addr));

	smu8_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetClkTableAddrLo,
				lower_32_bits(smu8_smu->scratch_buffer[i].mc_addr));

	smu8_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_ExecuteJob,
				smu8_smu->toc_entry_clock_table);

	smu8_send_msg_to_smc(hwmgr, PPSMC_MSG_ClkTableXferToSmu);

	return 0;
}