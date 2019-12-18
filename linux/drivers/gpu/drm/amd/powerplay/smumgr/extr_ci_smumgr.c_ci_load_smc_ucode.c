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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct pp_hwmgr {int /*<<< orphan*/  device; int /*<<< orphan*/  smu_version; int /*<<< orphan*/  is_kicker; } ;
struct cgs_firmware_info {int image_size; int ucode_start_address; scalar_t__ kptr; int /*<<< orphan*/  version; int /*<<< orphan*/  is_kicker; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_INCREMENT_IND_0 ; 
 int /*<<< orphan*/  CGS_UCODE_ID_SMU ; 
 int EINVAL ; 
 int /*<<< orphan*/  PHM_WRITE_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SMC_IND_ACCESS_CNTL ; 
 int SMC_RAM_END ; 
 int /*<<< orphan*/  cgs_get_firmware_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cgs_firmware_info*) ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmSMC_IND_DATA_0 ; 
 int /*<<< orphan*/  mmSMC_IND_INDEX_0 ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ci_load_smc_ucode(struct pp_hwmgr *hwmgr)
{
	uint32_t byte_count, start_addr;
	uint8_t *src;
	uint32_t data;

	struct cgs_firmware_info info = {0};

	cgs_get_firmware_info(hwmgr->device, CGS_UCODE_ID_SMU, &info);

	hwmgr->is_kicker = info.is_kicker;
	hwmgr->smu_version = info.version;
	byte_count = info.image_size;
	src = (uint8_t *)info.kptr;
	start_addr = info.ucode_start_address;

	if  (byte_count > SMC_RAM_END) {
		pr_err("SMC address is beyond the SMC RAM area.\n");
		return -EINVAL;
	}

	cgs_write_register(hwmgr->device, mmSMC_IND_INDEX_0, start_addr);
	PHM_WRITE_FIELD(hwmgr->device, SMC_IND_ACCESS_CNTL, AUTO_INCREMENT_IND_0, 1);

	for (; byte_count >= 4; byte_count -= 4) {
		data = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
		cgs_write_register(hwmgr->device, mmSMC_IND_DATA_0, data);
		src += 4;
	}
	PHM_WRITE_FIELD(hwmgr->device, SMC_IND_ACCESS_CNTL, AUTO_INCREMENT_IND_0, 0);

	if (0 != byte_count) {
		pr_err("SMC size must be divisible by 4\n");
		return -EINVAL;
	}

	return 0;
}