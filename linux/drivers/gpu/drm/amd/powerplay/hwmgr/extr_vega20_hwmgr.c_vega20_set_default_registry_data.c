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
struct TYPE_2__ {int disallowed_features; int thermal_support; int sclk_throttle_low_notification; int stable_pstate_sclk_dpm_percentage; int didt_mode; int sq_ramping_support; int edc_didt_support; int pcie_lane_override; int pcie_speed_override; int pcie_clock_override; int regulator_hot_gpio_support; int zrpm_start_temp; int zrpm_stop_temp; int od8_feature_enable; int perf_ui_tuning_profile_turbo; int perf_ui_tuning_profile_powerSave; int perf_ui_tuning_profile_xl; int fps_support; int disable_auto_wattman; int auto_wattman_sample_period; int auto_wattman_threshold; int gfxoff_controlled_by_driver; scalar_t__ fclk_gfxclk_ratio; scalar_t__ auto_wattman_debug; scalar_t__ disable_3d_fs_detection; scalar_t__ force_workload_policy_mask; scalar_t__ disable_workload_policy; scalar_t__ disable_xlpp_tuning; scalar_t__ disable_pp_tuning; scalar_t__ disable_water_mark; scalar_t__ quick_transition_support; scalar_t__ ac_dc_switch_gpio_support; scalar_t__ psm_didt_support; scalar_t__ gc_didt_support; scalar_t__ dbr_ramping_support; scalar_t__ tcp_ramping_support; scalar_t__ td_ramping_support; scalar_t__ db_ramping_support; scalar_t__ didt_support; scalar_t__ force_dpm_high; scalar_t__ log_avfs_param; scalar_t__ skip_baco_hardware; scalar_t__ od_state_in_dc_support; } ;
struct vega20_hwmgr {int gfxoff_allowed; scalar_t__ counter_gfxoff; TYPE_1__ registry_data; void* phy_clk_quad_eqn_c; void* phy_clk_quad_eqn_b; void* phy_clk_quad_eqn_a; void* pixel_clk_quad_eqn_c; void* pixel_clk_quad_eqn_b; void* pixel_clk_quad_eqn_a; void* disp_clk_quad_eqn_c; void* disp_clk_quad_eqn_b; void* disp_clk_quad_eqn_a; void* dcef_clk_quad_eqn_c; void* dcef_clk_quad_eqn_b; void* dcef_clk_quad_eqn_a; int /*<<< orphan*/  display_voltage_mode; int /*<<< orphan*/  lowest_uclk_reserved_for_ulv; int /*<<< orphan*/  gfx_activity_average_alpha; int /*<<< orphan*/  uclk_average_alpha; int /*<<< orphan*/  socclk_average_alpha; int /*<<< orphan*/  gfxclk_average_alpha; } ;
struct pp_hwmgr {int smu_version; int feature_mask; scalar_t__ backend; } ;

/* Variables and functions */
 int FEATURE_DPM_DCEFCLK_MASK ; 
 int FEATURE_DPM_GFXCLK_MASK ; 
 int FEATURE_DPM_LINK_MASK ; 
 int FEATURE_DPM_SOCCLK_MASK ; 
 int FEATURE_DPM_UCLK_MASK ; 
 int FEATURE_DS_GFXCLK_MASK ; 
 int FEATURE_ECC_MASK ; 
 int FEATURE_ULV_MASK ; 
 void* PPREGKEY_VEGA20QUADRATICEQUATION_DFLT ; 
 int /*<<< orphan*/  PPSMC_MSG_GetSmuVersion ; 
 int /*<<< orphan*/  PPVEGA20_VEGA20DISPLAYVOLTAGEMODE_DFLT ; 
 int /*<<< orphan*/  PPVEGA20_VEGA20GFXACTIVITYAVERAGEALPHA_DFLT ; 
 int /*<<< orphan*/  PPVEGA20_VEGA20GFXCLKAVERAGEALPHA_DFLT ; 
 int /*<<< orphan*/  PPVEGA20_VEGA20LOWESTUCLKRESERVEDFORULV_DFLT ; 
 int /*<<< orphan*/  PPVEGA20_VEGA20SOCCLKAVERAGEALPHA_DFLT ; 
 int /*<<< orphan*/  PPVEGA20_VEGA20UCLKCLKAVERAGEALPHA_DFLT ; 
 int PP_DCEFCLK_DPM_MASK ; 
 int PP_MCLK_DPM_MASK ; 
 int PP_PCIE_DPM_MASK ; 
 int PP_SCLK_DEEP_SLEEP_MASK ; 
 int PP_SCLK_DPM_MASK ; 
 int PP_SOCCLK_DPM_MASK ; 
 int PP_ULV_MASK ; 
 int smum_get_argument (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vega20_set_default_registry_data(struct pp_hwmgr *hwmgr)
{
	struct vega20_hwmgr *data =
			(struct vega20_hwmgr *)(hwmgr->backend);

	data->gfxclk_average_alpha = PPVEGA20_VEGA20GFXCLKAVERAGEALPHA_DFLT;
	data->socclk_average_alpha = PPVEGA20_VEGA20SOCCLKAVERAGEALPHA_DFLT;
	data->uclk_average_alpha = PPVEGA20_VEGA20UCLKCLKAVERAGEALPHA_DFLT;
	data->gfx_activity_average_alpha = PPVEGA20_VEGA20GFXACTIVITYAVERAGEALPHA_DFLT;
	data->lowest_uclk_reserved_for_ulv = PPVEGA20_VEGA20LOWESTUCLKRESERVEDFORULV_DFLT;

	data->display_voltage_mode = PPVEGA20_VEGA20DISPLAYVOLTAGEMODE_DFLT;
	data->dcef_clk_quad_eqn_a = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->dcef_clk_quad_eqn_b = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->dcef_clk_quad_eqn_c = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_a = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_b = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_c = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_a = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_b = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_c = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_a = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_b = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_c = PPREGKEY_VEGA20QUADRATICEQUATION_DFLT;

	/*
	 * Disable the following features for now:
	 *   GFXCLK DS
	 *   SOCLK DS
	 *   LCLK DS
	 *   DCEFCLK DS
	 *   FCLK DS
	 *   MP1CLK DS
	 *   MP0CLK DS
	 */
	data->registry_data.disallowed_features = 0xE0041C00;
	/* ECC feature should be disabled on old SMUs */
	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetSmuVersion);
	hwmgr->smu_version = smum_get_argument(hwmgr);
	if (hwmgr->smu_version < 0x282100)
		data->registry_data.disallowed_features |= FEATURE_ECC_MASK;

	if (!(hwmgr->feature_mask & PP_PCIE_DPM_MASK))
		data->registry_data.disallowed_features |= FEATURE_DPM_LINK_MASK;

	if (!(hwmgr->feature_mask & PP_SCLK_DPM_MASK))
		data->registry_data.disallowed_features |= FEATURE_DPM_GFXCLK_MASK;

	if (!(hwmgr->feature_mask & PP_SOCCLK_DPM_MASK))
		data->registry_data.disallowed_features |= FEATURE_DPM_SOCCLK_MASK;

	if (!(hwmgr->feature_mask & PP_MCLK_DPM_MASK))
		data->registry_data.disallowed_features |= FEATURE_DPM_UCLK_MASK;

	if (!(hwmgr->feature_mask & PP_DCEFCLK_DPM_MASK))
		data->registry_data.disallowed_features |= FEATURE_DPM_DCEFCLK_MASK;

	if (!(hwmgr->feature_mask & PP_ULV_MASK))
		data->registry_data.disallowed_features |= FEATURE_ULV_MASK;

	if (!(hwmgr->feature_mask & PP_SCLK_DEEP_SLEEP_MASK))
		data->registry_data.disallowed_features |= FEATURE_DS_GFXCLK_MASK;

	data->registry_data.od_state_in_dc_support = 0;
	data->registry_data.thermal_support = 1;
	data->registry_data.skip_baco_hardware = 0;

	data->registry_data.log_avfs_param = 0;
	data->registry_data.sclk_throttle_low_notification = 1;
	data->registry_data.force_dpm_high = 0;
	data->registry_data.stable_pstate_sclk_dpm_percentage = 75;

	data->registry_data.didt_support = 0;
	if (data->registry_data.didt_support) {
		data->registry_data.didt_mode = 6;
		data->registry_data.sq_ramping_support = 1;
		data->registry_data.db_ramping_support = 0;
		data->registry_data.td_ramping_support = 0;
		data->registry_data.tcp_ramping_support = 0;
		data->registry_data.dbr_ramping_support = 0;
		data->registry_data.edc_didt_support = 1;
		data->registry_data.gc_didt_support = 0;
		data->registry_data.psm_didt_support = 0;
	}

	data->registry_data.pcie_lane_override = 0xff;
	data->registry_data.pcie_speed_override = 0xff;
	data->registry_data.pcie_clock_override = 0xffffffff;
	data->registry_data.regulator_hot_gpio_support = 1;
	data->registry_data.ac_dc_switch_gpio_support = 0;
	data->registry_data.quick_transition_support = 0;
	data->registry_data.zrpm_start_temp = 0xffff;
	data->registry_data.zrpm_stop_temp = 0xffff;
	data->registry_data.od8_feature_enable = 1;
	data->registry_data.disable_water_mark = 0;
	data->registry_data.disable_pp_tuning = 0;
	data->registry_data.disable_xlpp_tuning = 0;
	data->registry_data.disable_workload_policy = 0;
	data->registry_data.perf_ui_tuning_profile_turbo = 0x19190F0F;
	data->registry_data.perf_ui_tuning_profile_powerSave = 0x19191919;
	data->registry_data.perf_ui_tuning_profile_xl = 0x00000F0A;
	data->registry_data.force_workload_policy_mask = 0;
	data->registry_data.disable_3d_fs_detection = 0;
	data->registry_data.fps_support = 1;
	data->registry_data.disable_auto_wattman = 1;
	data->registry_data.auto_wattman_debug = 0;
	data->registry_data.auto_wattman_sample_period = 100;
	data->registry_data.fclk_gfxclk_ratio = 0;
	data->registry_data.auto_wattman_threshold = 50;
	data->registry_data.gfxoff_controlled_by_driver = 1;
	data->gfxoff_allowed = false;
	data->counter_gfxoff = 0;
}