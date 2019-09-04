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
typedef  int uint32_t ;
struct smu8_smumgr {int dummy; } ;
struct pp_hwmgr {int /*<<< orphan*/ * device; struct smu8_smumgr* smu_backend; } ;
struct cgs_firmware_info {int /*<<< orphan*/  mc_addr; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATC ; 
 int /*<<< orphan*/  CACHE_POLICY ; 
 int /*<<< orphan*/  CGS_UCODE_ID_CP_MEC ; 
 int /*<<< orphan*/  CP_CPC_IC_BASE_CNTL ; 
 int /*<<< orphan*/  CP_CPC_IC_BASE_HI ; 
 int /*<<< orphan*/  CP_CPC_IC_BASE_LO ; 
 int /*<<< orphan*/  CP_MEC_CNTL ; 
 int EINVAL ; 
 int /*<<< orphan*/  IC_BASE_HI ; 
 int /*<<< orphan*/  IC_BASE_LO ; 
 int /*<<< orphan*/  MEC_ME1_HALT ; 
 int /*<<< orphan*/  MEC_ME2_HALT ; 
 int /*<<< orphan*/  MTYPE ; 
 int PHM_FIELD_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PHM_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VMID ; 
 int cgs_get_firmware_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cgs_firmware_info*) ; 
 int cgs_read_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCP_CPC_IC_BASE_CNTL ; 
 int /*<<< orphan*/  mmCP_CPC_IC_BASE_HI ; 
 int /*<<< orphan*/  mmCP_CPC_IC_BASE_LO ; 
 int /*<<< orphan*/  mmCP_MEC_CNTL ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_load_mec_firmware(struct pp_hwmgr *hwmgr)
{
	uint32_t reg_data;
	uint32_t tmp;
	int ret = 0;
	struct cgs_firmware_info info = {0};
	struct smu8_smumgr *smu8_smu;

	if (hwmgr == NULL || hwmgr->device == NULL)
		return -EINVAL;

	smu8_smu = hwmgr->smu_backend;
	ret = cgs_get_firmware_info(hwmgr->device,
						CGS_UCODE_ID_CP_MEC, &info);

	if (ret)
		return -EINVAL;

	/* Disable MEC parsing/prefetching */
	tmp = cgs_read_register(hwmgr->device,
					mmCP_MEC_CNTL);
	tmp = PHM_SET_FIELD(tmp, CP_MEC_CNTL, MEC_ME1_HALT, 1);
	tmp = PHM_SET_FIELD(tmp, CP_MEC_CNTL, MEC_ME2_HALT, 1);
	cgs_write_register(hwmgr->device, mmCP_MEC_CNTL, tmp);

	tmp = cgs_read_register(hwmgr->device,
					mmCP_CPC_IC_BASE_CNTL);

	tmp = PHM_SET_FIELD(tmp, CP_CPC_IC_BASE_CNTL, VMID, 0);
	tmp = PHM_SET_FIELD(tmp, CP_CPC_IC_BASE_CNTL, ATC, 0);
	tmp = PHM_SET_FIELD(tmp, CP_CPC_IC_BASE_CNTL, CACHE_POLICY, 0);
	tmp = PHM_SET_FIELD(tmp, CP_CPC_IC_BASE_CNTL, MTYPE, 1);
	cgs_write_register(hwmgr->device, mmCP_CPC_IC_BASE_CNTL, tmp);

	reg_data = lower_32_bits(info.mc_addr) &
			PHM_FIELD_MASK(CP_CPC_IC_BASE_LO, IC_BASE_LO);
	cgs_write_register(hwmgr->device, mmCP_CPC_IC_BASE_LO, reg_data);

	reg_data = upper_32_bits(info.mc_addr) &
			PHM_FIELD_MASK(CP_CPC_IC_BASE_HI, IC_BASE_HI);
	cgs_write_register(hwmgr->device, mmCP_CPC_IC_BASE_HI, reg_data);

	return 0;
}