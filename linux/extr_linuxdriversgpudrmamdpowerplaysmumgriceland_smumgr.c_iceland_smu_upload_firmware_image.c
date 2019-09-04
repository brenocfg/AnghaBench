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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct pp_hwmgr {int /*<<< orphan*/ * device; int /*<<< orphan*/  smu_version; } ;
struct cgs_firmware_info {int image_size; int /*<<< orphan*/  ucode_start_address; scalar_t__ kptr; int /*<<< orphan*/  version; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int EINVAL ; 
 int ICELAND_SMC_SIZE ; 
 int /*<<< orphan*/  PHM_WAIT_INDIRECT_FIELD_UNEQUAL (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCU_UC_EVENTS ; 
 int /*<<< orphan*/  SMC_IND ; 
 int /*<<< orphan*/  UCODE_ID_SMU ; 
 int /*<<< orphan*/  boot_seq_done ; 
 int /*<<< orphan*/  cgs_get_firmware_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cgs_firmware_info*) ; 
 int cgs_read_ind_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgs_write_ind_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iceland_reset_smc (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  iceland_stop_smc_clock (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  iceland_upload_smc_firmware_data (struct pp_hwmgr*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixSMC_SYSCON_MISC_CNTL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  smu7_convert_fw_type_to_cgs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iceland_smu_upload_firmware_image(struct pp_hwmgr *hwmgr)
{
	uint32_t val;
	struct cgs_firmware_info info = {0};

	if (hwmgr == NULL || hwmgr->device == NULL)
		return -EINVAL;

	/* load SMC firmware */
	cgs_get_firmware_info(hwmgr->device,
		smu7_convert_fw_type_to_cgs(UCODE_ID_SMU), &info);

	if (info.image_size & 3) {
		pr_err("[ powerplay ] SMC ucode is not 4 bytes aligned\n");
		return -EINVAL;
	}

	if (info.image_size > ICELAND_SMC_SIZE) {
		pr_err("[ powerplay ] SMC address is beyond the SMC RAM area\n");
		return -EINVAL;
	}
	hwmgr->smu_version = info.version;
	/* wait for smc boot up */
	PHM_WAIT_INDIRECT_FIELD_UNEQUAL(hwmgr, SMC_IND,
					 RCU_UC_EVENTS, boot_seq_done, 0);

	/* clear firmware interrupt enable flag */
	val = cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC,
				    ixSMC_SYSCON_MISC_CNTL);
	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
			       ixSMC_SYSCON_MISC_CNTL, val | 1);

	/* stop smc clock */
	iceland_stop_smc_clock(hwmgr);

	/* reset smc */
	iceland_reset_smc(hwmgr);
	iceland_upload_smc_firmware_data(hwmgr, info.image_size,
				(uint8_t *)info.kptr, ICELAND_SMC_SIZE,
				info.ucode_start_address);

	return 0;
}