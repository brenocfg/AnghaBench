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
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_START ; 
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int EINVAL ; 
 int /*<<< orphan*/  FIRMWARE_FLAGS ; 
 int /*<<< orphan*/  INTERRUPTS_ENABLED ; 
 int PHM_READ_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHM_WAIT_VFPF_INDIRECT_FIELD (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHM_WAIT_VFPF_INDIRECT_FIELD_UNEQUAL (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHM_WRITE_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RCU_UC_EVENTS ; 
 int /*<<< orphan*/  SMC_IND ; 
 int /*<<< orphan*/  SMC_SYSCON_CLOCK_CNTL_0 ; 
 int /*<<< orphan*/  SMC_SYSCON_RESET_CNTL ; 
 int /*<<< orphan*/  SMU_DONE ; 
 int /*<<< orphan*/  SMU_INPUT_DATA ; 
 int /*<<< orphan*/  SMU_PASS ; 
 int /*<<< orphan*/  SMU_STATUS ; 
 int /*<<< orphan*/  cgs_write_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_disable ; 
 int /*<<< orphan*/  ixFIRMWARE_FLAGS ; 
 int /*<<< orphan*/  ixSMU_STATUS ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rst_reg ; 
 int /*<<< orphan*/  smu7_send_msg_to_smc_offset (struct pp_hwmgr*) ; 
 int smu7_upload_smu_firmware_image (struct pp_hwmgr*) ; 

__attribute__((used)) static int tonga_start_in_protection_mode(struct pp_hwmgr *hwmgr)
{
	int result;

	/* Assert reset */
	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_RESET_CNTL, rst_reg, 1);

	result = smu7_upload_smu_firmware_image(hwmgr);
	if (result)
		return result;

	/* Clear status */
	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
		ixSMU_STATUS, 0);

	/* Enable clock */
	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_CLOCK_CNTL_0, ck_disable, 0);

	/* De-assert reset */
	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_RESET_CNTL, rst_reg, 0);

	/* Set SMU Auto Start */
	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
		SMU_INPUT_DATA, AUTO_START, 1);

	/* Clear firmware interrupt enable flag */
	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
		ixFIRMWARE_FLAGS, 0);

	PHM_WAIT_VFPF_INDIRECT_FIELD(hwmgr, SMC_IND,
		RCU_UC_EVENTS, INTERRUPTS_ENABLED, 1);

	/**
	 * Call Test SMU message with 0x20000 offset to trigger SMU start
	 */
	smu7_send_msg_to_smc_offset(hwmgr);

	/* Wait for done bit to be set */
	PHM_WAIT_VFPF_INDIRECT_FIELD_UNEQUAL(hwmgr, SMC_IND,
		SMU_STATUS, SMU_DONE, 0);

	/* Check pass/failed indicator */
	if (1 != PHM_READ_VFPF_INDIRECT_FIELD(hwmgr->device,
				CGS_IND_REG__SMC, SMU_STATUS, SMU_PASS)) {
		pr_err("SMU Firmware start failed\n");
		return -EINVAL;
	}

	/* Wait for firmware to initialize */
	PHM_WAIT_VFPF_INDIRECT_FIELD(hwmgr, SMC_IND,
		FIRMWARE_FLAGS, INTERRUPTS_ENABLED, 1);

	return 0;
}