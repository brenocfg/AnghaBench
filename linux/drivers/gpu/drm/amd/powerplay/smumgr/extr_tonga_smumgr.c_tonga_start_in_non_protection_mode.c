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
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  FIRMWARE_FLAGS ; 
 int /*<<< orphan*/  INTERRUPTS_ENABLED ; 
 int /*<<< orphan*/  PHM_WAIT_VFPF_INDIRECT_FIELD (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHM_WAIT_VFPF_INDIRECT_FIELD_UNEQUAL (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHM_WRITE_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RCU_UC_EVENTS ; 
 int /*<<< orphan*/  SMC_IND ; 
 int /*<<< orphan*/  SMC_SYSCON_CLOCK_CNTL_0 ; 
 int /*<<< orphan*/  SMC_SYSCON_RESET_CNTL ; 
 int /*<<< orphan*/  boot_seq_done ; 
 int /*<<< orphan*/  cgs_write_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_disable ; 
 int /*<<< orphan*/  ixFIRMWARE_FLAGS ; 
 int /*<<< orphan*/  rst_reg ; 
 int /*<<< orphan*/  smu7_program_jump_on_start (struct pp_hwmgr*) ; 
 int smu7_upload_smu_firmware_image (struct pp_hwmgr*) ; 

__attribute__((used)) static int tonga_start_in_non_protection_mode(struct pp_hwmgr *hwmgr)
{
	int result = 0;

	/* wait for smc boot up */
	PHM_WAIT_VFPF_INDIRECT_FIELD_UNEQUAL(hwmgr, SMC_IND,
		RCU_UC_EVENTS, boot_seq_done, 0);

	/*Clear firmware interrupt enable flag*/
	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
		ixFIRMWARE_FLAGS, 0);


	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_RESET_CNTL, rst_reg, 1);

	result = smu7_upload_smu_firmware_image(hwmgr);

	if (result != 0)
		return result;

	/* Set smc instruct start point at 0x0 */
	smu7_program_jump_on_start(hwmgr);


	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_CLOCK_CNTL_0, ck_disable, 0);

	/*De-assert reset*/
	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_RESET_CNTL, rst_reg, 0);

	/* Wait for firmware to initialize */
	PHM_WAIT_VFPF_INDIRECT_FIELD(hwmgr, SMC_IND,
		FIRMWARE_FLAGS, INTERRUPTS_ENABLED, 1);

	return result;
}