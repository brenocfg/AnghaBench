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
typedef  int uint32_t ;
struct TYPE_2__ {int pcie_dpm_enable_mask; int sclk_dpm_enable_mask; int mclk_dpm_enable_mask; } ;
struct smu7_hwmgr {TYPE_1__ dpm_level_enable_mask; int /*<<< orphan*/  mclk_dpm_key_disabled; int /*<<< orphan*/  sclk_dpm_key_disabled; int /*<<< orphan*/  pcie_dpm_key_disabled; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_MCLKDPM_SetEnabledMask ; 
 int /*<<< orphan*/  PPSMC_MSG_PCIeDPM_ForceLevel ; 
 int /*<<< orphan*/  PPSMC_MSG_SCLKDPM_SetEnabledMask ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu7_force_dpm_highest(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	uint32_t level, tmp;

	if (!data->pcie_dpm_key_disabled) {
		if (data->dpm_level_enable_mask.pcie_dpm_enable_mask) {
			level = 0;
			tmp = data->dpm_level_enable_mask.pcie_dpm_enable_mask;
			while (tmp >>= 1)
				level++;

			if (level)
				smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_PCIeDPM_ForceLevel, level);
		}
	}

	if (!data->sclk_dpm_key_disabled) {
		if (data->dpm_level_enable_mask.sclk_dpm_enable_mask) {
			level = 0;
			tmp = data->dpm_level_enable_mask.sclk_dpm_enable_mask;
			while (tmp >>= 1)
				level++;

			if (level)
				smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SCLKDPM_SetEnabledMask,
						(1 << level));
		}
	}

	if (!data->mclk_dpm_key_disabled) {
		if (data->dpm_level_enable_mask.mclk_dpm_enable_mask) {
			level = 0;
			tmp = data->dpm_level_enable_mask.mclk_dpm_enable_mask;
			while (tmp >>= 1)
				level++;

			if (level)
				smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_MCLKDPM_SetEnabledMask,
						(1 << level));
		}
	}

	return 0;
}