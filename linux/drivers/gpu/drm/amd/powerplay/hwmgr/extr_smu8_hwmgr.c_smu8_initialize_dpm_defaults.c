#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cpu_cc6_disable; int cpu_pstate_disable; int nb_pstate_switch_disable; scalar_t__ cpu_pstate_separation_time; } ;
struct smu8_hwmgr {int gfx_ramp_step; int gfx_ramp_delay; int mgcg_cgtt_local0; int mgcg_cgtt_local1; int clock_slow_down_freq; int skip_clock_slow_down; int enable_nb_ps_policy; int voting_rights_clients; int static_screen_threshold; int bapm_enabled; int gfx_power_gating_threshold; int vce_slow_sclk_threshold; int dce_slow_sclk_threshold; int disable_driver_thermal_policy; int override_dynamic_mgpg; TYPE_1__ cc6_settings; scalar_t__ disable_gfx_power_gating_in_uvd; scalar_t__ tdr_clock; scalar_t__ thermal_auto_throttling_treshold; scalar_t__ disable_nb_ps3_in_battery; scalar_t__ voltage_drop_threshold; scalar_t__ ddi_power_gating_disabled; scalar_t__ voltage_drop_in_dce_power_gating; } ;
struct TYPE_4__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {TYPE_2__ platform_descriptor; struct amdgpu_device* adev; struct smu8_hwmgr* backend; } ;
struct amdgpu_device {int pg_flags; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_UVD ; 
 int AMD_PG_SUPPORT_VCE ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ABM ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DisableVoltageIsland ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DynamicM3Arbiter ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DynamicPatchPowerState ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DynamicUVDState ; 
 int /*<<< orphan*/  PHM_PlatformCaps_NonABMSupportInPPLib ; 
 int /*<<< orphan*/  PHM_PlatformCaps_UVDDPM ; 
 int /*<<< orphan*/  PHM_PlatformCaps_UVDPowerGating ; 
 int /*<<< orphan*/  PHM_PlatformCaps_VCEDPM ; 
 int /*<<< orphan*/  PHM_PlatformCaps_VCEPowerGating ; 
 int /*<<< orphan*/  phm_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phm_cap_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_initialize_dpm_defaults(struct pp_hwmgr *hwmgr)
{
	struct smu8_hwmgr *data = hwmgr->backend;
	struct amdgpu_device *adev = hwmgr->adev;

	data->gfx_ramp_step = 256*25/100;
	data->gfx_ramp_delay = 1; /* by default, we delay 1us */

	data->mgcg_cgtt_local0 = 0x00000000;
	data->mgcg_cgtt_local1 = 0x00000000;
	data->clock_slow_down_freq = 25000;
	data->skip_clock_slow_down = 1;
	data->enable_nb_ps_policy = 1; /* disable until UNB is ready, Enabled */
	data->voltage_drop_in_dce_power_gating = 0; /* disable until fully verified */
	data->voting_rights_clients = 0x00C00033;
	data->static_screen_threshold = 8;
	data->ddi_power_gating_disabled = 0;
	data->bapm_enabled = 1;
	data->voltage_drop_threshold = 0;
	data->gfx_power_gating_threshold = 500;
	data->vce_slow_sclk_threshold = 20000;
	data->dce_slow_sclk_threshold = 30000;
	data->disable_driver_thermal_policy = 1;
	data->disable_nb_ps3_in_battery = 0;

	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
							PHM_PlatformCaps_ABM);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				    PHM_PlatformCaps_NonABMSupportInPPLib);

	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_DynamicM3Arbiter);

	data->override_dynamic_mgpg = 1;

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				  PHM_PlatformCaps_DynamicPatchPowerState);

	data->thermal_auto_throttling_treshold = 0;
	data->tdr_clock = 0;
	data->disable_gfx_power_gating_in_uvd = 0;

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_DynamicUVDState);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_UVDDPM);
	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_VCEDPM);

	data->cc6_settings.cpu_cc6_disable = false;
	data->cc6_settings.cpu_pstate_disable = false;
	data->cc6_settings.nb_pstate_switch_disable = false;
	data->cc6_settings.cpu_pstate_separation_time = 0;

	phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				   PHM_PlatformCaps_DisableVoltageIsland);

	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
		      PHM_PlatformCaps_UVDPowerGating);
	phm_cap_unset(hwmgr->platform_descriptor.platformCaps,
		      PHM_PlatformCaps_VCEPowerGating);

	if (adev->pg_flags & AMD_PG_SUPPORT_UVD)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			      PHM_PlatformCaps_UVDPowerGating);
	if (adev->pg_flags & AMD_PG_SUPPORT_VCE)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			      PHM_PlatformCaps_VCEPowerGating);


	return 0;
}