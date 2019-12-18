#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_14__ {int min; scalar_t__ max; } ;
struct TYPE_13__ {int min; scalar_t__ max; } ;
struct TYPE_12__ {void* min; void* max; } ;
struct TYPE_11__ {void* min; void* max; } ;
struct TYPE_9__ {int temperature_low; int temperature_high; int temperature_shutdown; } ;
struct TYPE_16__ {int bupdate_sclk; int sclk_down_hyst; int bupdate_mclk; int mclk_down_hyst; int /*<<< orphan*/  mclk_activity; scalar_t__ mclk_up_hyst; int /*<<< orphan*/  sclk_activity; scalar_t__ sclk_up_hyst; } ;
struct smu7_hwmgr {int dll_default_on; int mclk_dpm0_activity_target; int vddc_vddgfx_delta; int mclk_dpm_key_disabled; int sclk_dpm_key_disabled; int pcie_dpm_key_disabled; scalar_t__ vddci_control; scalar_t__ mvdd_control; int enable_tdc_limit_feature; int enable_pkg_pwr_tracking_feature; int ulv_supported; int vddc_phase_shed_control; int fast_watermark_threshold; scalar_t__ vdd_gfx_control; TYPE_6__ pcie_lane_power_saving; TYPE_5__ pcie_lane_performance; TYPE_4__ pcie_gen_power_saving; TYPE_3__ pcie_gen_performance; void* voltage_control; TYPE_1__ thermal_temp_setting; TYPE_8__ current_profile_setting; int /*<<< orphan*/  force_pcie_gen; int /*<<< orphan*/ * voting_rights_clients; int /*<<< orphan*/  static_screen_threshold_unit; int /*<<< orphan*/  static_screen_threshold; } ;
struct TYPE_15__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {int feature_mask; int workload_mask; int* workload_prority; size_t power_profile_mode; size_t default_power_profile_mode; scalar_t__ chip_id; scalar_t__ chip_family; scalar_t__ pp_table_version; TYPE_7__ platform_descriptor; scalar_t__ is_kicker; struct amdgpu_device* adev; scalar_t__ pptable; scalar_t__ backend; } ;
struct phm_ppt_v1_information {TYPE_2__* cac_dtp_table; } ;
struct amdgpu_device {int pg_flags; } ;
struct TYPE_10__ {scalar_t__ usClockStretchAmount; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FAMILY_CI ; 
 int AMD_PG_SUPPORT_UVD ; 
 int AMD_PG_SUPPORT_VCE ; 
 scalar_t__ CHIP_HAWAII ; 
 scalar_t__ CHIP_POLARIS12 ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ClockStretcher ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ControlVDDCI ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ControlVDDGFX ; 
 int /*<<< orphan*/  PHM_PlatformCaps_EnableMVDDControl ; 
 int /*<<< orphan*/  PHM_PlatformCaps_UVDPowerGating ; 
 int /*<<< orphan*/  PHM_PlatformCaps_VCEPowerGating ; 
 int PP_CLOCK_STRETCH_MASK ; 
 int PP_MCLK_DPM_MASK ; 
 void* PP_PCIEGen1 ; 
 void* PP_PCIEGen3 ; 
 int /*<<< orphan*/  PP_PCIEGenInvalid ; 
 int PP_PCIE_DPM_MASK ; 
 int PP_SCLK_DPM_MASK ; 
 size_t PP_SMC_POWER_PROFILE_FULLSCREEN3D ; 
 scalar_t__ PP_TABLE_V0 ; 
 int PP_ULV_MASK ; 
 int /*<<< orphan*/  SMU7_MCLK_TARGETACTIVITY_DFLT ; 
 int /*<<< orphan*/  SMU7_SCLK_TARGETACTIVITY_DFLT ; 
 int /*<<< orphan*/  SMU7_STATICSCREENTHRESHOLDUNIT_DFLT ; 
 int /*<<< orphan*/  SMU7_STATICSCREENTHRESHOLD_DFLT ; 
 void* SMU7_VOLTAGE_CONTROL_BY_GPIO ; 
 void* SMU7_VOLTAGE_CONTROL_BY_SVID2 ; 
 scalar_t__ SMU7_VOLTAGE_CONTROL_NONE ; 
 int /*<<< orphan*/  SMU7_VOTINGRIGHTSCLIENTS_DFLT0 ; 
 int /*<<< orphan*/  SMU7_VOTINGRIGHTSCLIENTS_DFLT1 ; 
 int /*<<< orphan*/  SMU7_VOTINGRIGHTSCLIENTS_DFLT2 ; 
 int /*<<< orphan*/  SMU7_VOTINGRIGHTSCLIENTS_DFLT3 ; 
 int /*<<< orphan*/  SMU7_VOTINGRIGHTSCLIENTS_DFLT4 ; 
 int /*<<< orphan*/  SMU7_VOTINGRIGHTSCLIENTS_DFLT5 ; 
 int /*<<< orphan*/  SMU7_VOTINGRIGHTSCLIENTS_DFLT6 ; 
 int /*<<< orphan*/  SMU7_VOTINGRIGHTSCLIENTS_DFLT7 ; 
 int /*<<< orphan*/  VOLTAGE_OBJ_GPIO_LUT ; 
 int /*<<< orphan*/  VOLTAGE_OBJ_SVID2 ; 
 int /*<<< orphan*/  VOLTAGE_TYPE_MVDDC ; 
 int /*<<< orphan*/  VOLTAGE_TYPE_VDDC ; 
 int /*<<< orphan*/  VOLTAGE_TYPE_VDDCI ; 
 int /*<<< orphan*/  VOLTAGE_TYPE_VDDGFX ; 
 int /*<<< orphan*/  atomctrl_get_svi2_info (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ atomctrl_is_voltage_controlled_by_gpio_v3 (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phm_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phm_cap_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smu7_init_dpm_defaults(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)(hwmgr->pptable);
	struct amdgpu_device *adev = hwmgr->adev;

	data->dll_default_on = false;
	data->mclk_dpm0_activity_target = 0xa;
	data->vddc_vddgfx_delta = 300;
	data->static_screen_threshold = SMU7_STATICSCREENTHRESHOLD_DFLT;
	data->static_screen_threshold_unit = SMU7_STATICSCREENTHRESHOLDUNIT_DFLT;
	data->voting_rights_clients[0] = SMU7_VOTINGRIGHTSCLIENTS_DFLT0;
	data->voting_rights_clients[1]= SMU7_VOTINGRIGHTSCLIENTS_DFLT1;
	data->voting_rights_clients[2] = SMU7_VOTINGRIGHTSCLIENTS_DFLT2;
	data->voting_rights_clients[3]= SMU7_VOTINGRIGHTSCLIENTS_DFLT3;
	data->voting_rights_clients[4]= SMU7_VOTINGRIGHTSCLIENTS_DFLT4;
	data->voting_rights_clients[5]= SMU7_VOTINGRIGHTSCLIENTS_DFLT5;
	data->voting_rights_clients[6]= SMU7_VOTINGRIGHTSCLIENTS_DFLT6;
	data->voting_rights_clients[7]= SMU7_VOTINGRIGHTSCLIENTS_DFLT7;

	data->mclk_dpm_key_disabled = hwmgr->feature_mask & PP_MCLK_DPM_MASK ? false : true;
	data->sclk_dpm_key_disabled = hwmgr->feature_mask & PP_SCLK_DPM_MASK ? false : true;
	data->pcie_dpm_key_disabled = hwmgr->feature_mask & PP_PCIE_DPM_MASK ? false : true;
	/* need to set voltage control types before EVV patching */
	data->voltage_control = SMU7_VOLTAGE_CONTROL_NONE;
	data->vddci_control = SMU7_VOLTAGE_CONTROL_NONE;
	data->mvdd_control = SMU7_VOLTAGE_CONTROL_NONE;
	data->enable_tdc_limit_feature = true;
	data->enable_pkg_pwr_tracking_feature = true;
	data->force_pcie_gen = PP_PCIEGenInvalid;
	data->ulv_supported = hwmgr->feature_mask & PP_ULV_MASK ? true : false;
	data->current_profile_setting.bupdate_sclk = 1;
	data->current_profile_setting.sclk_up_hyst = 0;
	data->current_profile_setting.sclk_down_hyst = 100;
	data->current_profile_setting.sclk_activity = SMU7_SCLK_TARGETACTIVITY_DFLT;
	data->current_profile_setting.bupdate_mclk = 1;
	data->current_profile_setting.mclk_up_hyst = 0;
	data->current_profile_setting.mclk_down_hyst = 100;
	data->current_profile_setting.mclk_activity = SMU7_MCLK_TARGETACTIVITY_DFLT;
	hwmgr->workload_mask = 1 << hwmgr->workload_prority[PP_SMC_POWER_PROFILE_FULLSCREEN3D];
	hwmgr->power_profile_mode = PP_SMC_POWER_PROFILE_FULLSCREEN3D;
	hwmgr->default_power_profile_mode = PP_SMC_POWER_PROFILE_FULLSCREEN3D;

	if (hwmgr->chip_id == CHIP_POLARIS12 || hwmgr->is_kicker) {
		uint8_t tmp1, tmp2;
		uint16_t tmp3 = 0;
		atomctrl_get_svi2_info(hwmgr, VOLTAGE_TYPE_VDDC, &tmp1, &tmp2,
						&tmp3);
		tmp3 = (tmp3 >> 5) & 0x3;
		data->vddc_phase_shed_control = ((tmp3 << 1) | (tmp3 >> 1)) & 0x3;
	} else if (hwmgr->chip_family == AMDGPU_FAMILY_CI) {
		data->vddc_phase_shed_control = 1;
	} else {
		data->vddc_phase_shed_control = 0;
	}

	if (hwmgr->chip_id  == CHIP_HAWAII) {
		data->thermal_temp_setting.temperature_low = 94500;
		data->thermal_temp_setting.temperature_high = 95000;
		data->thermal_temp_setting.temperature_shutdown = 104000;
	} else {
		data->thermal_temp_setting.temperature_low = 99500;
		data->thermal_temp_setting.temperature_high = 100000;
		data->thermal_temp_setting.temperature_shutdown = 104000;
	}

	data->fast_watermark_threshold = 100;
	if (atomctrl_is_voltage_controlled_by_gpio_v3(hwmgr,
			VOLTAGE_TYPE_VDDC, VOLTAGE_OBJ_SVID2))
		data->voltage_control = SMU7_VOLTAGE_CONTROL_BY_SVID2;
	else if (atomctrl_is_voltage_controlled_by_gpio_v3(hwmgr,
			VOLTAGE_TYPE_VDDC, VOLTAGE_OBJ_GPIO_LUT))
		data->voltage_control = SMU7_VOLTAGE_CONTROL_BY_GPIO;

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_ControlVDDGFX)) {
		if (atomctrl_is_voltage_controlled_by_gpio_v3(hwmgr,
			VOLTAGE_TYPE_VDDGFX, VOLTAGE_OBJ_SVID2)) {
			data->vdd_gfx_control = SMU7_VOLTAGE_CONTROL_BY_SVID2;
		}
	}

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_EnableMVDDControl)) {
		if (atomctrl_is_voltage_controlled_by_gpio_v3(hwmgr,
				VOLTAGE_TYPE_MVDDC, VOLTAGE_OBJ_GPIO_LUT))
			data->mvdd_control = SMU7_VOLTAGE_CONTROL_BY_GPIO;
		else if (atomctrl_is_voltage_controlled_by_gpio_v3(hwmgr,
				VOLTAGE_TYPE_MVDDC, VOLTAGE_OBJ_SVID2))
			data->mvdd_control = SMU7_VOLTAGE_CONTROL_BY_SVID2;
	}

	if (SMU7_VOLTAGE_CONTROL_NONE == data->vdd_gfx_control)
		phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_ControlVDDGFX);

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_ControlVDDCI)) {
		if (atomctrl_is_voltage_controlled_by_gpio_v3(hwmgr,
				VOLTAGE_TYPE_VDDCI, VOLTAGE_OBJ_GPIO_LUT))
			data->vddci_control = SMU7_VOLTAGE_CONTROL_BY_GPIO;
		else if (atomctrl_is_voltage_controlled_by_gpio_v3(hwmgr,
				VOLTAGE_TYPE_VDDCI, VOLTAGE_OBJ_SVID2))
			data->vddci_control = SMU7_VOLTAGE_CONTROL_BY_SVID2;
	}

	if (data->mvdd_control == SMU7_VOLTAGE_CONTROL_NONE)
		phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_EnableMVDDControl);

	if (data->vddci_control == SMU7_VOLTAGE_CONTROL_NONE)
		phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_ControlVDDCI);

	if ((hwmgr->pp_table_version != PP_TABLE_V0) && (hwmgr->feature_mask & PP_CLOCK_STRETCH_MASK)
		&& (table_info->cac_dtp_table->usClockStretchAmount != 0))
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_ClockStretcher);

	data->pcie_gen_performance.max = PP_PCIEGen1;
	data->pcie_gen_performance.min = PP_PCIEGen3;
	data->pcie_gen_power_saving.max = PP_PCIEGen1;
	data->pcie_gen_power_saving.min = PP_PCIEGen3;
	data->pcie_lane_performance.max = 0;
	data->pcie_lane_performance.min = 16;
	data->pcie_lane_power_saving.max = 0;
	data->pcie_lane_power_saving.min = 16;


	if (adev->pg_flags & AMD_PG_SUPPORT_UVD)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			      PHM_PlatformCaps_UVDPowerGating);
	if (adev->pg_flags & AMD_PG_SUPPORT_VCE)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			      PHM_PlatformCaps_VCEPowerGating);
}