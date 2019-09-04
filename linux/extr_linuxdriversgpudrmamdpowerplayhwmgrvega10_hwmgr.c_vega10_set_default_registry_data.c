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
struct TYPE_2__ {int sclk_dpm_key_disabled; int socclk_dpm_key_disabled; int mclk_dpm_key_disabled; int pcie_dpm_key_disabled; int dcefclk_dpm_key_disabled; int power_containment_support; int enable_pkg_pwr_tracking_feature; int enable_tdc_limit_feature; int clock_stretcher_support; int ulv_support; int sclk_deep_sleep_support; int fan_control_support; int thermal_support; int fw_ctf_enabled; int avfs_support; int led_dpm_enabled; int vr0hot_enabled; int vr1hot_enabled; int regulator_hot_gpio_support; int didt_support; int didt_mode; int sq_ramping_support; int edc_didt_support; scalar_t__ psm_didt_support; scalar_t__ gc_didt_support; scalar_t__ dbr_ramping_support; scalar_t__ tcp_ramping_support; scalar_t__ td_ramping_support; scalar_t__ db_ramping_support; scalar_t__ disable_water_mark; } ;
struct vega10_hwmgr {int /*<<< orphan*/  gfx_activity_average_alpha; int /*<<< orphan*/  uclk_average_alpha; int /*<<< orphan*/  socclk_average_alpha; int /*<<< orphan*/  gfxclk_average_alpha; void* phy_clk_quad_eqn_c; void* phy_clk_quad_eqn_b; void* phy_clk_quad_eqn_a; void* pixel_clk_quad_eqn_c; void* pixel_clk_quad_eqn_b; void* pixel_clk_quad_eqn_a; void* disp_clk_quad_eqn_c; void* disp_clk_quad_eqn_b; void* disp_clk_quad_eqn_a; void* dcef_clk_quad_eqn_c; void* dcef_clk_quad_eqn_b; void* dcef_clk_quad_eqn_a; int /*<<< orphan*/  display_voltage_mode; TYPE_1__ registry_data; } ;
struct pp_hwmgr {int feature_mask; struct vega10_hwmgr* backend; } ;

/* Variables and functions */
 void* PPREGKEY_VEGA10QUADRATICEQUATION_DFLT ; 
 int /*<<< orphan*/  PPVEGA10_VEGA10DISPLAYVOLTAGEMODE_DFLT ; 
 int /*<<< orphan*/  PPVEGA10_VEGA10GFXACTIVITYAVERAGEALPHA_DFLT ; 
 int /*<<< orphan*/  PPVEGA10_VEGA10GFXCLKAVERAGEALPHA_DFLT ; 
 int /*<<< orphan*/  PPVEGA10_VEGA10SOCCLKAVERAGEALPHA_DFLT ; 
 int /*<<< orphan*/  PPVEGA10_VEGA10UCLKCLKAVERAGEALPHA_DFLT ; 
 int PP_CLOCK_STRETCH_MASK ; 
 int PP_DCEFCLK_DPM_MASK ; 
 int PP_MCLK_DPM_MASK ; 
 int PP_PCIE_DPM_MASK ; 
 int PP_POWER_CONTAINMENT_MASK ; 
 int PP_SCLK_DEEP_SLEEP_MASK ; 
 int PP_SCLK_DPM_MASK ; 
 int PP_SOCCLK_DPM_MASK ; 
 int PP_ULV_MASK ; 

__attribute__((used)) static void vega10_set_default_registry_data(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;

	data->registry_data.sclk_dpm_key_disabled =
			hwmgr->feature_mask & PP_SCLK_DPM_MASK ? false : true;
	data->registry_data.socclk_dpm_key_disabled =
			hwmgr->feature_mask & PP_SOCCLK_DPM_MASK ? false : true;
	data->registry_data.mclk_dpm_key_disabled =
			hwmgr->feature_mask & PP_MCLK_DPM_MASK ? false : true;
	data->registry_data.pcie_dpm_key_disabled =
			hwmgr->feature_mask & PP_PCIE_DPM_MASK ? false : true;

	data->registry_data.dcefclk_dpm_key_disabled =
			hwmgr->feature_mask & PP_DCEFCLK_DPM_MASK ? false : true;

	if (hwmgr->feature_mask & PP_POWER_CONTAINMENT_MASK) {
		data->registry_data.power_containment_support = 1;
		data->registry_data.enable_pkg_pwr_tracking_feature = 1;
		data->registry_data.enable_tdc_limit_feature = 1;
	}

	data->registry_data.clock_stretcher_support =
			hwmgr->feature_mask & PP_CLOCK_STRETCH_MASK ? true : false;

	data->registry_data.ulv_support =
			hwmgr->feature_mask & PP_ULV_MASK ? true : false;

	data->registry_data.sclk_deep_sleep_support =
			hwmgr->feature_mask & PP_SCLK_DEEP_SLEEP_MASK ? true : false;

	data->registry_data.disable_water_mark = 0;

	data->registry_data.fan_control_support = 1;
	data->registry_data.thermal_support = 1;
	data->registry_data.fw_ctf_enabled = 1;

	data->registry_data.avfs_support = 1;
	data->registry_data.led_dpm_enabled = 1;

	data->registry_data.vr0hot_enabled = 1;
	data->registry_data.vr1hot_enabled = 1;
	data->registry_data.regulator_hot_gpio_support = 1;

	data->registry_data.didt_support = 1;
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

	data->display_voltage_mode = PPVEGA10_VEGA10DISPLAYVOLTAGEMODE_DFLT;
	data->dcef_clk_quad_eqn_a = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->dcef_clk_quad_eqn_b = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->dcef_clk_quad_eqn_c = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_a = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_b = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->disp_clk_quad_eqn_c = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_a = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_b = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->pixel_clk_quad_eqn_c = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_a = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_b = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;
	data->phy_clk_quad_eqn_c = PPREGKEY_VEGA10QUADRATICEQUATION_DFLT;

	data->gfxclk_average_alpha = PPVEGA10_VEGA10GFXCLKAVERAGEALPHA_DFLT;
	data->socclk_average_alpha = PPVEGA10_VEGA10SOCCLKAVERAGEALPHA_DFLT;
	data->uclk_average_alpha = PPVEGA10_VEGA10UCLKCLKAVERAGEALPHA_DFLT;
	data->gfx_activity_average_alpha = PPVEGA10_VEGA10GFXACTIVITYAVERAGEALPHA_DFLT;
}