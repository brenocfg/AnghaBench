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
struct TYPE_2__ {int disallowed_features; int thermal_support; int sclk_throttle_low_notification; int stable_pstate_sclk_dpm_percentage; int didt_mode; int sq_ramping_support; int edc_didt_support; int pcie_lane_override; int pcie_speed_override; int pcie_clock_override; int regulator_hot_gpio_support; int zrpm_start_temp; int zrpm_stop_temp; int odn_feature_enable; int perf_ui_tuning_profile_turbo; int perf_ui_tuning_profile_powerSave; int perf_ui_tuning_profile_xl; int fps_support; int disable_auto_wattman; int auto_wattman_sample_period; int auto_wattman_threshold; scalar_t__ auto_wattman_debug; scalar_t__ disable_3d_fs_detection; scalar_t__ force_workload_policy_mask; scalar_t__ disable_workload_policy; scalar_t__ disable_xlpp_tuning; scalar_t__ disable_pp_tuning; scalar_t__ disable_water_mark; scalar_t__ quick_transition_support; scalar_t__ ac_dc_switch_gpio_support; scalar_t__ psm_didt_support; scalar_t__ gc_didt_support; scalar_t__ dbr_ramping_support; scalar_t__ tcp_ramping_support; scalar_t__ td_ramping_support; scalar_t__ db_ramping_support; scalar_t__ didt_support; scalar_t__ force_dpm_high; scalar_t__ log_avfs_param; scalar_t__ skip_baco_hardware; scalar_t__ od_state_in_dc_support; } ;
struct vega12_hwmgr {TYPE_1__ registry_data; void* phy_clk_quad_eqn_c; void* phy_clk_quad_eqn_b; void* phy_clk_quad_eqn_a; void* pixel_clk_quad_eqn_c; void* pixel_clk_quad_eqn_b; void* pixel_clk_quad_eqn_a; void* disp_clk_quad_eqn_c; void* disp_clk_quad_eqn_b; void* disp_clk_quad_eqn_a; void* dcef_clk_quad_eqn_c; void* dcef_clk_quad_eqn_b; void* dcef_clk_quad_eqn_a; int /*<<< orphan*/  display_voltage_mode; int /*<<< orphan*/  lowest_uclk_reserved_for_ulv; int /*<<< orphan*/  gfx_activity_average_alpha; int /*<<< orphan*/  uclk_average_alpha; int /*<<< orphan*/  socclk_average_alpha; int /*<<< orphan*/  gfxclk_average_alpha; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
 void* PPREGKEY_VEGA12QUADRATICEQUATION_DFLT ; 
 int /*<<< orphan*/  PPVEGA12_VEGA12DISPLAYVOLTAGEMODE_DFLT ; 
 int /*<<< orphan*/  PPVEGA12_VEGA12GFXACTIVITYAVERAGEALPHA_DFLT ; 
 int /*<<< orphan*/  PPVEGA12_VEGA12GFXCLKAVERAGEALPHA_DFLT ; 
 int /*<<< orphan*/  PPVEGA12_VEGA12LOWESTUCLKRESERVEDFORULV_DFLT ; 
 int /*<<< orphan*/  PPVEGA12_VEGA12SOCCLKAVERAGEALPHA_DFLT ; 
 int /*<<< orphan*/  PPVEGA12_VEGA12UCLKCLKAVERAGEALPHA_DFLT ; 

__attribute__((used)) static void vega12_set_default_registry_data(struct pp_hwmgr *hwmgr)
{
	struct vega12_hwmgr *data =
			(struct vega12_hwmgr *)(hwmgr->backend);

	data->gfxclk_average_alpha = PPVEGA12_VEGA12GFXCLKAVERAGEALPHA_DFLT;
	data->socclk_average_alpha = PPVEGA12_VEGA12SOCCLKAVERAGEALPHA_DFLT;
	data->uclk_average_alpha = PPVEGA12_VEGA12UCLKCLKAVERAGEALPHA_DFLT;
	data->gfx_activity_average_alpha = PPVEGA12_VEGA12GFXACTIVITYAVERAGEALPHA_DFLT;
	data->lowest_uclk_reserved_for_ulv = PPVEGA12_VEGA12LOWESTUCLKRESERVEDFORULV_DFLT;

	data->display_voltage_mode = PPVEGA12_VEGA12DISPLAYVOLTAGEMODE_DFLT;
	data->dcef_clk_quad_eqn_a = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->dcef_clk_quad_eqn_b = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->dcef_clk_quad_eqn_c = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_a = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_b = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_c = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_a = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_b = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_c = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_a = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_b = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_c = PPREGKEY_VEGA12QUADRATICEQUATION_DFLT;

	data->registry_data.disallowed_features = 0x0;
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
	data->registry_data.odn_feature_enable = 1;
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
	data->registry_data.auto_wattman_threshold = 50;
}