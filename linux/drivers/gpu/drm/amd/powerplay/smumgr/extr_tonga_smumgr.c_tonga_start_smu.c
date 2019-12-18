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
struct TYPE_2__ {int /*<<< orphan*/  soft_regs_start; } ;
struct tonga_smumgr {TYPE_1__ smu7_data; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; scalar_t__ not_vf; struct tonga_smumgr* smu_backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 scalar_t__ PHM_READ_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SMU72_FIRMWARE_HEADER_LOCATION ; 
 int /*<<< orphan*/  SMU72_Firmware_Header ; 
 int /*<<< orphan*/  SMU_FIRMWARE ; 
 int /*<<< orphan*/  SMU_MODE ; 
 int /*<<< orphan*/  SoftRegisters ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu7_is_smc_ram_running (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_read_smc_sram_dword (struct pp_hwmgr*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int smu7_request_smu_load_fw (struct pp_hwmgr*) ; 
 int tonga_start_in_non_protection_mode (struct pp_hwmgr*) ; 
 int tonga_start_in_protection_mode (struct pp_hwmgr*) ; 

__attribute__((used)) static int tonga_start_smu(struct pp_hwmgr *hwmgr)
{
	struct tonga_smumgr *priv = hwmgr->smu_backend;
	int result;

	/* Only start SMC if SMC RAM is not running */
	if (!smu7_is_smc_ram_running(hwmgr) && hwmgr->not_vf) {
		/*Check if SMU is running in protected mode*/
		if (0 == PHM_READ_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
					SMU_FIRMWARE, SMU_MODE)) {
			result = tonga_start_in_non_protection_mode(hwmgr);
			if (result)
				return result;
		} else {
			result = tonga_start_in_protection_mode(hwmgr);
			if (result)
				return result;
		}
	}

	/* Setup SoftRegsStart here to visit the register UcodeLoadStatus
	 * to check fw loading state
	 */
	smu7_read_smc_sram_dword(hwmgr,
			SMU72_FIRMWARE_HEADER_LOCATION +
			offsetof(SMU72_Firmware_Header, SoftRegisters),
			&(priv->smu7_data.soft_regs_start), 0x40000);

	result = smu7_request_smu_load_fw(hwmgr);

	return result;
}