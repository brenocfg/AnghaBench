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
struct smu7_hwmgr {scalar_t__ apply_avfs_cks_off_voltage; } ;
struct pp_hwmgr {int /*<<< orphan*/  avfs_supported; scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_ApplyAvfsCksOffVoltage ; 
 int /*<<< orphan*/  PPSMC_MSG_EnableAvfs ; 
 int smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

int vegam_thermal_avfs_enable(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	int ret;

	if (!hwmgr->avfs_supported)
		return 0;

	ret = smum_send_msg_to_smc(hwmgr, PPSMC_MSG_EnableAvfs);
	if (!ret) {
		if (data->apply_avfs_cks_off_voltage)
			ret = smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ApplyAvfsCksOffVoltage);
	}

	return ret;
}