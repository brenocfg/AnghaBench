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
struct smu7_smumgr {scalar_t__ avfs_btc_param; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; scalar_t__ smu_backend; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_PerformBtc ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCP_MEC_CNTL ; 
 int /*<<< orphan*/  mmGRBM_SOFT_RESET ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ smu7_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fiji_start_avfs_btc(struct pp_hwmgr *hwmgr)
{
	int result = 0;
	struct smu7_smumgr *smu_data = (struct smu7_smumgr *)(hwmgr->smu_backend);

	if (0 != smu_data->avfs_btc_param) {
		if (0 != smu7_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_PerformBtc, smu_data->avfs_btc_param)) {
			pr_info("[AVFS][Fiji_PerformBtc] PerformBTC SMU msg failed");
			result = -EINVAL;
		}
	}
	/* Soft-Reset to reset the engine before loading uCode */
	 /* halt */
	cgs_write_register(hwmgr->device, mmCP_MEC_CNTL, 0x50000000);
	/* reset everything */
	cgs_write_register(hwmgr->device, mmGRBM_SOFT_RESET, 0xffffffff);
	/* clear reset */
	cgs_write_register(hwmgr->device, mmGRBM_SOFT_RESET, 0);

	return result;
}