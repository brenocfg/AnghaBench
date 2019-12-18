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
struct pp_hwmgr {struct iceland_smumgr* smu_backend; } ;
struct TYPE_2__ {int /*<<< orphan*/  soft_regs_start; } ;
struct iceland_smumgr {TYPE_1__ smu7_data; } ;

/* Variables and functions */
 scalar_t__ SMU71_FIRMWARE_HEADER_LOCATION ; 
 int /*<<< orphan*/  SMU71_Firmware_Header ; 
 int /*<<< orphan*/  SoftRegisters ; 
 int /*<<< orphan*/  iceland_smu_start_smc (struct pp_hwmgr*) ; 
 int iceland_smu_upload_firmware_image (struct pp_hwmgr*) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu7_is_smc_ram_running (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_read_smc_sram_dword (struct pp_hwmgr*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int smu7_request_smu_load_fw (struct pp_hwmgr*) ; 

__attribute__((used)) static int iceland_start_smu(struct pp_hwmgr *hwmgr)
{
	struct iceland_smumgr *priv = hwmgr->smu_backend;
	int result;

	if (!smu7_is_smc_ram_running(hwmgr)) {
		result = iceland_smu_upload_firmware_image(hwmgr);
		if (result)
			return result;

		iceland_smu_start_smc(hwmgr);
	}

	/* Setup SoftRegsStart here to visit the register UcodeLoadStatus
	 * to check fw loading state
	 */
	smu7_read_smc_sram_dword(hwmgr,
			SMU71_FIRMWARE_HEADER_LOCATION +
			offsetof(SMU71_Firmware_Header, SoftRegisters),
			&(priv->smu7_data.soft_regs_start), 0x40000);

	result = smu7_request_smu_load_fw(hwmgr);

	return result;
}