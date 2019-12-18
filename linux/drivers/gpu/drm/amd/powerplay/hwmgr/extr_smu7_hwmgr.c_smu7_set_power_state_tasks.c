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
struct smu7_hwmgr {int apply_optimized_settings; } ;
struct TYPE_2__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {TYPE_1__ platform_descriptor; scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_PlatformCaps_PCIEPerformanceRequest ; 
 int /*<<< orphan*/  PP_ASSERT_WITH_CODE (int,char*,int) ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smu7_find_dpm_states_clocks_in_dpm_table (struct pp_hwmgr*,void const*) ; 
 int smu7_freeze_sclk_mclk_dpm (struct pp_hwmgr*) ; 
 int smu7_generate_dpm_level_enable_mask (struct pp_hwmgr*,void const*) ; 
 int smu7_notify_link_speed_change_after_state_change (struct pp_hwmgr*,void const*) ; 
 int smu7_notify_smc_display (struct pp_hwmgr*) ; 
 int smu7_populate_and_upload_sclk_mclk_dpm_levels (struct pp_hwmgr*,void const*) ; 
 int smu7_request_link_speed_change_before_state_change (struct pp_hwmgr*,void const*) ; 
 int smu7_unfreeze_sclk_mclk_dpm (struct pp_hwmgr*) ; 
 int smu7_update_avfs (struct pp_hwmgr*) ; 
 int smu7_upload_dpm_level_enable_mask (struct pp_hwmgr*) ; 
 int smum_update_sclk_threshold (struct pp_hwmgr*) ; 

__attribute__((used)) static int smu7_set_power_state_tasks(struct pp_hwmgr *hwmgr, const void *input)
{
	int tmp_result, result = 0;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	tmp_result = smu7_find_dpm_states_clocks_in_dpm_table(hwmgr, input);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to find DPM states clocks in DPM table!",
			result = tmp_result);

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_PCIEPerformanceRequest)) {
		tmp_result =
			smu7_request_link_speed_change_before_state_change(hwmgr, input);
		PP_ASSERT_WITH_CODE((0 == tmp_result),
				"Failed to request link speed change before state change!",
				result = tmp_result);
	}

	tmp_result = smu7_freeze_sclk_mclk_dpm(hwmgr);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to freeze SCLK MCLK DPM!", result = tmp_result);

	tmp_result = smu7_populate_and_upload_sclk_mclk_dpm_levels(hwmgr, input);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to populate and upload SCLK MCLK DPM levels!",
			result = tmp_result);

	tmp_result = smu7_update_avfs(hwmgr);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to update avfs voltages!",
			result = tmp_result);

	tmp_result = smu7_generate_dpm_level_enable_mask(hwmgr, input);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to generate DPM level enabled mask!",
			result = tmp_result);

	tmp_result = smum_update_sclk_threshold(hwmgr);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to update SCLK threshold!",
			result = tmp_result);

	tmp_result = smu7_notify_smc_display(hwmgr);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to notify smc display settings!",
			result = tmp_result);

	tmp_result = smu7_unfreeze_sclk_mclk_dpm(hwmgr);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to unfreeze SCLK MCLK DPM!",
			result = tmp_result);

	tmp_result = smu7_upload_dpm_level_enable_mask(hwmgr);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to upload DPM level enabled mask!",
			result = tmp_result);

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_PCIEPerformanceRequest)) {
		tmp_result =
			smu7_notify_link_speed_change_after_state_change(hwmgr, input);
		PP_ASSERT_WITH_CODE((0 == tmp_result),
				"Failed to notify link speed change after state change!",
				result = tmp_result);
	}
	data->apply_optimized_settings = false;
	return result;
}