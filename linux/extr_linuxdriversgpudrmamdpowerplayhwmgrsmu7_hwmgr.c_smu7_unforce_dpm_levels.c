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
struct smu7_hwmgr {int /*<<< orphan*/  pcie_dpm_key_disabled; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_PCIeDPM_UnForceLevel ; 
 int smu7_upload_dpm_level_enable_mask (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smum_is_dpm_running (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_unforce_dpm_levels(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	if (!smum_is_dpm_running(hwmgr))
		return -EINVAL;

	if (!data->pcie_dpm_key_disabled) {
		smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_PCIeDPM_UnForceLevel);
	}

	return smu7_upload_dpm_level_enable_mask(hwmgr);
}