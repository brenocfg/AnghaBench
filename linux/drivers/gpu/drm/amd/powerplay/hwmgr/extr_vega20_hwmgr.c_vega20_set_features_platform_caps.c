#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ custom_fan_support; scalar_t__ quick_transition_support; scalar_t__ ac_dc_switch_gpio_support; scalar_t__ psm_didt_support; scalar_t__ gc_didt_support; scalar_t__ edc_didt_support; scalar_t__ dbr_ramping_support; scalar_t__ tcp_ramping_support; scalar_t__ td_ramping_support; scalar_t__ db_ramping_support; scalar_t__ sq_ramping_support; scalar_t__ didt_support; scalar_t__ sclk_throttle_low_notification; scalar_t__ force_dpm_high; scalar_t__ fuzzy_fan_control_support; scalar_t__ thermal_support; scalar_t__ od8_feature_enable; scalar_t__ od_state_in_dc_support; } ;
struct vega20_hwmgr {scalar_t__ vddci_control; int lowest_uclk_reserved_for_ulv; TYPE_3__ registry_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  platformCaps; } ;
struct TYPE_5__ {scalar_t__ usTMax; } ;
struct TYPE_6__ {TYPE_1__ advanceFanControlParameters; } ;
struct pp_hwmgr {TYPE_4__ platform_descriptor; TYPE_2__ thermal_controller; struct amdgpu_device* adev; scalar_t__ backend; } ;
struct amdgpu_device {int pg_flags; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_UVD ; 
 int AMD_PG_SUPPORT_VCE ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ActivityReporting ; 
 int /*<<< orphan*/  PHM_PlatformCaps_AutomaticDCTransition ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ControlVDDCI ; 
 int /*<<< orphan*/  PHM_PlatformCaps_CustomFanControlSupport ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DBRRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DBRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DiDtEDCEnable ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DiDtSupport ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DynamicPowerManagement ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DynamicUVDState ; 
 int /*<<< orphan*/  PHM_PlatformCaps_EnableSMU7ThermalManagement ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ExclusiveModeAlwaysHigh ; 
 int /*<<< orphan*/  PHM_PlatformCaps_Falcon_QuickTransition ; 
 int /*<<< orphan*/  PHM_PlatformCaps_FanSpeedInTableIsRPM ; 
 int /*<<< orphan*/  PHM_PlatformCaps_GCEDC ; 
 int /*<<< orphan*/  PHM_PlatformCaps_LowestUclkReservedForUlv ; 
 int /*<<< orphan*/  PHM_PlatformCaps_OD8inACSupport ; 
 int /*<<< orphan*/  PHM_PlatformCaps_OD8inDCSupport ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ODFuzzyFanControlSupport ; 
 int /*<<< orphan*/  PHM_PlatformCaps_PSM ; 
 int /*<<< orphan*/  PHM_PlatformCaps_PowerContainment ; 
 int /*<<< orphan*/  PHM_PlatformCaps_RegulatorHot ; 
 int /*<<< orphan*/  PHM_PlatformCaps_SMC ; 
 int /*<<< orphan*/  PHM_PlatformCaps_SMCtoPPLIBAcdcGpioScheme ; 
 int /*<<< orphan*/  PHM_PlatformCaps_SQRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_SclkThrottleLowNotification ; 
 int /*<<< orphan*/  PHM_PlatformCaps_TCPRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_TDRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_TablelessHardwareInterface ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ThermalPolicyDelay ; 
 int /*<<< orphan*/  PHM_PlatformCaps_UVDPowerGating ; 
 int /*<<< orphan*/  PHM_PlatformCaps_UnTabledHardwareInterface ; 
 int /*<<< orphan*/  PHM_PlatformCaps_VCEPowerGating ; 
 int PPVEGA20_VEGA20LOWESTUCLKRESERVEDFORULV_DFLT ; 
 scalar_t__ VEGA20_VOLTAGE_CONTROL_NONE ; 
 int /*<<< orphan*/  phm_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phm_cap_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega20_set_features_platform_caps(struct pp_hwmgr *hwmgr)
{
	struct vega20_hwmgr *data =
			(struct vega20_hwmgr *)(hwmgr->backend);
	struct amdgpu_device *adev = hwmgr->adev;

	if (data->vddci_control == VEGA20_VOLTAGE_CONTROL_NONE)
		phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_ControlVDDCI);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_TablelessHardwareInterface);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_EnableSMU7ThermalManagement);

	if (adev->pg_flags & AMD_PG_SUPPORT_UVD)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_UVDPowerGating);

	if (adev->pg_flags & AMD_PG_SUPPORT_VCE)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_VCEPowerGating);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_UnTabledHardwareInterface);

	if (data->registry_data.od8_feature_enable)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_OD8inACSupport);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_ActivityReporting);
	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_FanSpeedInTableIsRPM);

	if (data->registry_data.od_state_in_dc_support) {
		if (data->registry_data.od8_feature_enable)
			phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_OD8inDCSupport);
	}

	if (data->registry_data.thermal_support &&
	    data->registry_data.fuzzy_fan_control_support &&
	    hwmgr->thermal_controller.advanceFanControlParameters.usTMax)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_ODFuzzyFanControlSupport);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_DynamicPowerManagement);
	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_SMC);
	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_ThermalPolicyDelay);

	if (data->registry_data.force_dpm_high)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_ExclusiveModeAlwaysHigh);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_DynamicUVDState);

	if (data->registry_data.sclk_throttle_low_notification)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_SclkThrottleLowNotification);

	/* power tune caps */
	/* assume disabled */
	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_PowerContainment);
	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_DiDtSupport);
	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_SQRamping);
	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_DBRamping);
	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_TDRamping);
	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_TCPRamping);
	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_DBRRamping);
	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_DiDtEDCEnable);
	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_GCEDC);
	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_PSM);

	if (data->registry_data.didt_support) {
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_DiDtSupport);
		if (data->registry_data.sq_ramping_support)
			phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_SQRamping);
		if (data->registry_data.db_ramping_support)
			phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_DBRamping);
		if (data->registry_data.td_ramping_support)
			phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_TDRamping);
		if (data->registry_data.tcp_ramping_support)
			phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_TCPRamping);
		if (data->registry_data.dbr_ramping_support)
			phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_DBRRamping);
		if (data->registry_data.edc_didt_support)
			phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_DiDtEDCEnable);
		if (data->registry_data.gc_didt_support)
			phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_GCEDC);
		if (data->registry_data.psm_didt_support)
			phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_PSM);
	}

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_RegulatorHot);

	if (data->registry_data.ac_dc_switch_gpio_support) {
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_AutomaticDCTransition);
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_SMCtoPPLIBAcdcGpioScheme);
	}

	if (data->registry_data.quick_transition_support) {
		phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_AutomaticDCTransition);
		phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_SMCtoPPLIBAcdcGpioScheme);
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_Falcon_QuickTransition);
	}

	if (data->lowest_uclk_reserved_for_ulv != PPVEGA20_VEGA20LOWESTUCLKRESERVEDFORULV_DFLT) {
		phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_LowestUclkReservedForUlv);
		if (data->lowest_uclk_reserved_for_ulv == 1)
			phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_LowestUclkReservedForUlv);
	}

	if (data->registry_data.custom_fan_support)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_CustomFanControlSupport);

	return 0;
}