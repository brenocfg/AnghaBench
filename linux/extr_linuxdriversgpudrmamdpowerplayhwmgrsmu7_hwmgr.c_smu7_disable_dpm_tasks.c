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
struct TYPE_2__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; TYPE_1__ platform_descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  CG_SPLL_SPREAD_SPECTRUM ; 
 int /*<<< orphan*/  DYN_SPREAD_SPECTRUM_EN ; 
 int /*<<< orphan*/  GENERAL_PWRMGT ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ThermalController ; 
 int /*<<< orphan*/  PHM_WRITE_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PP_ASSERT_WITH_CODE (int,char*,int) ; 
 int /*<<< orphan*/  SSEN ; 
 int /*<<< orphan*/  THERMAL_PROTECTION_DIS ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smu7_avfs_control (struct pp_hwmgr*,int) ; 
 int smu7_clear_voting_clients (struct pp_hwmgr*) ; 
 int smu7_disable_deep_sleep_master_switch (struct pp_hwmgr*) ; 
 int smu7_disable_didt_config (struct pp_hwmgr*) ; 
 int smu7_disable_power_containment (struct pp_hwmgr*) ; 
 int smu7_disable_smc_cac (struct pp_hwmgr*) ; 
 int smu7_disable_thermal_auto_throttle (struct pp_hwmgr*) ; 
 int smu7_disable_ulv (struct pp_hwmgr*) ; 
 int smu7_force_switch_to_arbf0 (struct pp_hwmgr*) ; 
 int smu7_reset_to_default (struct pp_hwmgr*) ; 
 int smu7_stop_dpm (struct pp_hwmgr*) ; 

int smu7_disable_dpm_tasks(struct pp_hwmgr *hwmgr)
{
	int tmp_result, result = 0;

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_ThermalController))
		PHM_WRITE_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				GENERAL_PWRMGT, THERMAL_PROTECTION_DIS, 1);

	tmp_result = smu7_disable_power_containment(hwmgr);
	PP_ASSERT_WITH_CODE((tmp_result == 0),
			"Failed to disable power containment!", result = tmp_result);

	tmp_result = smu7_disable_smc_cac(hwmgr);
	PP_ASSERT_WITH_CODE((tmp_result == 0),
			"Failed to disable SMC CAC!", result = tmp_result);

	tmp_result = smu7_disable_didt_config(hwmgr);
	PP_ASSERT_WITH_CODE((tmp_result == 0),
			"Failed to disable DIDT!", result = tmp_result);

	PHM_WRITE_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_SPLL_SPREAD_SPECTRUM, SSEN, 0);
	PHM_WRITE_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			GENERAL_PWRMGT, DYN_SPREAD_SPECTRUM_EN, 0);

	tmp_result = smu7_disable_thermal_auto_throttle(hwmgr);
	PP_ASSERT_WITH_CODE((tmp_result == 0),
			"Failed to disable thermal auto throttle!", result = tmp_result);

	tmp_result = smu7_avfs_control(hwmgr, false);
	PP_ASSERT_WITH_CODE((tmp_result == 0),
			"Failed to disable AVFS!", result = tmp_result);

	tmp_result = smu7_stop_dpm(hwmgr);
	PP_ASSERT_WITH_CODE((tmp_result == 0),
			"Failed to stop DPM!", result = tmp_result);

	tmp_result = smu7_disable_deep_sleep_master_switch(hwmgr);
	PP_ASSERT_WITH_CODE((tmp_result == 0),
			"Failed to disable deep sleep master switch!", result = tmp_result);

	tmp_result = smu7_disable_ulv(hwmgr);
	PP_ASSERT_WITH_CODE((tmp_result == 0),
			"Failed to disable ULV!", result = tmp_result);

	tmp_result = smu7_clear_voting_clients(hwmgr);
	PP_ASSERT_WITH_CODE((tmp_result == 0),
			"Failed to clear voting clients!", result = tmp_result);

	tmp_result = smu7_reset_to_default(hwmgr);
	PP_ASSERT_WITH_CODE((tmp_result == 0),
			"Failed to reset to default!", result = tmp_result);

	tmp_result = smu7_force_switch_to_arbf0(hwmgr);
	PP_ASSERT_WITH_CODE((tmp_result == 0),
			"Failed to force to switch arbf0!", result = tmp_result);

	return result;
}