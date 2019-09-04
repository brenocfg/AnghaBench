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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ sclk_dpm_enable_mask; scalar_t__ mclk_dpm_enable_mask; scalar_t__ pcie_dpm_enable_mask; } ;
struct smu7_hwmgr {int /*<<< orphan*/  pcie_dpm_key_disabled; TYPE_1__ dpm_level_enable_mask; int /*<<< orphan*/  mclk_dpm_key_disabled; int /*<<< orphan*/  sclk_dpm_key_disabled; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
typedef  enum pp_clock_type { ____Placeholder_pp_clock_type } pp_clock_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_MCLKDPM_SetEnabledMask ; 
 int /*<<< orphan*/  PPSMC_MSG_PCIeDPM_ForceLevel ; 
 int /*<<< orphan*/  PPSMC_MSG_PCIeDPM_UnForceLevel ; 
 int /*<<< orphan*/  PPSMC_MSG_SCLKDPM_SetEnabledMask ; 
#define  PP_MCLK 130 
#define  PP_PCIE 129 
#define  PP_SCLK 128 
 int /*<<< orphan*/  ffs (scalar_t__) ; 
 int /*<<< orphan*/  fls (scalar_t__) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int smu7_force_clock_level(struct pp_hwmgr *hwmgr,
		enum pp_clock_type type, uint32_t mask)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	if (mask == 0)
		return -EINVAL;

	switch (type) {
	case PP_SCLK:
		if (!data->sclk_dpm_key_disabled)
			smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SCLKDPM_SetEnabledMask,
					data->dpm_level_enable_mask.sclk_dpm_enable_mask & mask);
		break;
	case PP_MCLK:
		if (!data->mclk_dpm_key_disabled)
			smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_MCLKDPM_SetEnabledMask,
					data->dpm_level_enable_mask.mclk_dpm_enable_mask & mask);
		break;
	case PP_PCIE:
	{
		uint32_t tmp = mask & data->dpm_level_enable_mask.pcie_dpm_enable_mask;

		if (!data->pcie_dpm_key_disabled) {
			if (fls(tmp) != ffs(tmp))
				smum_send_msg_to_smc(hwmgr, PPSMC_MSG_PCIeDPM_UnForceLevel);
			else
				smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_PCIeDPM_ForceLevel,
					fls(tmp) - 1);
		}
		break;
	}
	default:
		break;
	}

	return 0;
}