#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct rv7xx_power_info {int mclk_strobe_mode_threshold; int mclk_edc_enable_threshold; int power_gating; int gfx_clock_gating; int mg_clock_gating; int mgcgtssm; int dynamic_pcie_gen2; int thermal_protection; int display_gap; int dcodt; int ulps; int /*<<< orphan*/  sram_end; scalar_t__ mclk_stutter_mode_threshold; int /*<<< orphan*/  vrc; int /*<<< orphan*/  pasi; int /*<<< orphan*/  asi; void* mvdd_control; void* voltage_control; void* lmp; void* lhp; void* rmp; void* rlp; scalar_t__ ref_div; scalar_t__ max_vddc_in_table; scalar_t__ min_vddc_in_table; scalar_t__ acpi_vddc; } ;
struct TYPE_30__ {scalar_t__ sclk; scalar_t__ mclk; } ;
struct TYPE_26__ {int /*<<< orphan*/ * values; scalar_t__ count; } ;
struct TYPE_25__ {int /*<<< orphan*/  values; int /*<<< orphan*/  count; } ;
struct TYPE_23__ {int count; TYPE_13__* entries; } ;
struct TYPE_17__ {int mclk_sclk_ratio; int vddc_vddci_delta; int min_vddc_for_pcie_gen2; int sclk_mclk_delta; TYPE_9__ max_clock_voltage_on_ac; TYPE_9__ max_clock_voltage_on_dc; TYPE_5__ valid_mclk_values; TYPE_4__ valid_sclk_values; TYPE_2__ vddc_dependency_on_dispclk; } ;
struct TYPE_18__ {scalar_t__ voltage_response_time; scalar_t__ backbias_response_time; TYPE_10__ dyn_state; struct ni_power_info* priv; } ;
struct TYPE_19__ {scalar_t__ int_thermal_type; TYPE_11__ dpm; } ;
struct radeon_device {TYPE_12__ pm; TYPE_8__* pdev; } ;
struct radeon_clock_voltage_dependency_entry {int dummy; } ;
struct TYPE_27__ {int at; int bt; int av; int bv; } ;
struct TYPE_28__ {TYPE_6__ leakage_coefficients; } ;
struct TYPE_22__ {int supported; } ;
struct evergreen_power_info {int smu_uvd_hs; int mclk_edc_wr_enable_threshold; int ls_clock_gating; int sclk_deep_sleep; int dynamic_ac_timing; int abm; int mcls; int light_sleep; int memory_transition; int pcie_performance_request; int dll_default_on; void* vddci_control; TYPE_3__* ats; scalar_t__ acpi_vddci; TYPE_1__ ulv; struct rv7xx_power_info rv7xx; } ;
struct ni_power_info {int mclk_rtt_mode_threshold; int enable_power_containment; int enable_cac; int enable_sq_ramping; int driver_calculate_cac_leakage; int cac_configuration_required; int support_cac_long_term_average; int use_power_boost_limit; scalar_t__ lts_truncate; scalar_t__ lta_window_size; TYPE_14__* cac_weights; TYPE_7__ cac_data; struct evergreen_power_info eg; } ;
struct atom_clock_dividers {scalar_t__ ref_div; } ;
struct TYPE_29__ {int device; } ;
struct TYPE_24__ {void* lmp; void* lhp; void* rmp; void* rlp; } ;
struct TYPE_21__ {scalar_t__ lts_truncate; scalar_t__ l2_lta_window_size; scalar_t__ enable_power_containment_by_default; } ;
struct TYPE_20__ {int clk; int v; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 void* BTC_LHP_UVD_DFLT ; 
 void* BTC_LMP_UVD_DFLT ; 
 void* BTC_RLP_UVD_DFLT ; 
 void* BTC_RMP_UVD_DFLT ; 
 int /*<<< orphan*/  COMPUTE_ENGINE_PLL_PARAM ; 
 int /*<<< orphan*/  CYPRESS_HASI_DFLT ; 
 int /*<<< orphan*/  CYPRESS_VRC_DFLT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ R600_BACKBIASRESPONSETIME_DFLT ; 
 scalar_t__ R600_REFERENCEDIVIDER_DFLT ; 
 scalar_t__ R600_VOLTAGERESPONSETIME_DFLT ; 
 int /*<<< orphan*/  RV770_ASI_DFLT ; 
 void* RV770_LHP_DFLT ; 
 void* RV770_LMP_DFLT ; 
 void* RV770_RLP_DFLT ; 
 void* RV770_RMP_DFLT ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_MVDDC ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDC ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDCI ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 scalar_t__ THERMAL_TYPE_NONE ; 
 int /*<<< orphan*/  btc_valid_sclk ; 
 TYPE_14__ cac_weights_cayman_le ; 
 TYPE_14__ cac_weights_cayman_pro ; 
 TYPE_14__ cac_weights_cayman_xt ; 
 TYPE_13__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct ni_power_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ni_parse_power_table (struct radeon_device*) ; 
 int /*<<< orphan*/  ni_patch_dependency_tables_based_on_leakage (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_free_extended_power_table (struct radeon_device*) ; 
 int r600_get_platform_caps (struct radeon_device*) ; 
 int r600_parse_extended_power_table (struct radeon_device*) ; 
 int radeon_acpi_is_pcie_performance_request_supported (struct radeon_device*) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct atom_clock_dividers*) ; 
 void* radeon_atom_is_voltage_gpio (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv770_get_engine_memory_ss (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_get_max_vddc (struct radeon_device*) ; 

int ni_dpm_init(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi;
	struct evergreen_power_info *eg_pi;
	struct ni_power_info *ni_pi;
	struct atom_clock_dividers dividers;
	int ret;

	ni_pi = kzalloc(sizeof(struct ni_power_info), GFP_KERNEL);
	if (ni_pi == NULL)
		return -ENOMEM;
	rdev->pm.dpm.priv = ni_pi;
	eg_pi = &ni_pi->eg;
	pi = &eg_pi->rv7xx;

	rv770_get_max_vddc(rdev);

	eg_pi->ulv.supported = false;
	pi->acpi_vddc = 0;
	eg_pi->acpi_vddci = 0;
	pi->min_vddc_in_table = 0;
	pi->max_vddc_in_table = 0;

	ret = r600_get_platform_caps(rdev);
	if (ret)
		return ret;

	ret = ni_parse_power_table(rdev);
	if (ret)
		return ret;
	ret = r600_parse_extended_power_table(rdev);
	if (ret)
		return ret;

	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries =
		kcalloc(4,
			sizeof(struct radeon_clock_voltage_dependency_entry),
			GFP_KERNEL);
	if (!rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries) {
		r600_free_extended_power_table(rdev);
		return -ENOMEM;
	}
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.count = 4;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[0].clk = 0;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[0].v = 0;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[1].clk = 36000;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[1].v = 720;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[2].clk = 54000;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[2].v = 810;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[3].clk = 72000;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[3].v = 900;

	ni_patch_dependency_tables_based_on_leakage(rdev);

	if (rdev->pm.dpm.voltage_response_time == 0)
		rdev->pm.dpm.voltage_response_time = R600_VOLTAGERESPONSETIME_DFLT;
	if (rdev->pm.dpm.backbias_response_time == 0)
		rdev->pm.dpm.backbias_response_time = R600_BACKBIASRESPONSETIME_DFLT;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     0, false, &dividers);
	if (ret)
		pi->ref_div = dividers.ref_div + 1;
	else
		pi->ref_div = R600_REFERENCEDIVIDER_DFLT;

	pi->rlp = RV770_RLP_DFLT;
	pi->rmp = RV770_RMP_DFLT;
	pi->lhp = RV770_LHP_DFLT;
	pi->lmp = RV770_LMP_DFLT;

	eg_pi->ats[0].rlp = RV770_RLP_DFLT;
	eg_pi->ats[0].rmp = RV770_RMP_DFLT;
	eg_pi->ats[0].lhp = RV770_LHP_DFLT;
	eg_pi->ats[0].lmp = RV770_LMP_DFLT;

	eg_pi->ats[1].rlp = BTC_RLP_UVD_DFLT;
	eg_pi->ats[1].rmp = BTC_RMP_UVD_DFLT;
	eg_pi->ats[1].lhp = BTC_LHP_UVD_DFLT;
	eg_pi->ats[1].lmp = BTC_LMP_UVD_DFLT;

	eg_pi->smu_uvd_hs = true;

	if (rdev->pdev->device == 0x6707) {
		pi->mclk_strobe_mode_threshold = 55000;
		pi->mclk_edc_enable_threshold = 55000;
		eg_pi->mclk_edc_wr_enable_threshold = 55000;
	} else {
		pi->mclk_strobe_mode_threshold = 40000;
		pi->mclk_edc_enable_threshold = 40000;
		eg_pi->mclk_edc_wr_enable_threshold = 40000;
	}
	ni_pi->mclk_rtt_mode_threshold = eg_pi->mclk_edc_wr_enable_threshold;

	pi->voltage_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, 0);

	pi->mvdd_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_MVDDC, 0);

	eg_pi->vddci_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_VDDCI, 0);

	rv770_get_engine_memory_ss(rdev);

	pi->asi = RV770_ASI_DFLT;
	pi->pasi = CYPRESS_HASI_DFLT;
	pi->vrc = CYPRESS_VRC_DFLT;

	pi->power_gating = false;

	pi->gfx_clock_gating = true;

	pi->mg_clock_gating = true;
	pi->mgcgtssm = true;
	eg_pi->ls_clock_gating = false;
	eg_pi->sclk_deep_sleep = false;

	pi->dynamic_pcie_gen2 = true;

	if (rdev->pm.int_thermal_type != THERMAL_TYPE_NONE)
		pi->thermal_protection = true;
	else
		pi->thermal_protection = false;

	pi->display_gap = true;

	pi->dcodt = true;

	pi->ulps = true;

	eg_pi->dynamic_ac_timing = true;
	eg_pi->abm = true;
	eg_pi->mcls = true;
	eg_pi->light_sleep = true;
	eg_pi->memory_transition = true;
#if defined(CONFIG_ACPI)
	eg_pi->pcie_performance_request =
		radeon_acpi_is_pcie_performance_request_supported(rdev);
#else
	eg_pi->pcie_performance_request = false;
#endif

	eg_pi->dll_default_on = false;

	eg_pi->sclk_deep_sleep = false;

	pi->mclk_stutter_mode_threshold = 0;

	pi->sram_end = SMC_RAM_END;

	rdev->pm.dpm.dyn_state.mclk_sclk_ratio = 3;
	rdev->pm.dpm.dyn_state.vddc_vddci_delta = 200;
	rdev->pm.dpm.dyn_state.min_vddc_for_pcie_gen2 = 900;
	rdev->pm.dpm.dyn_state.valid_sclk_values.count = ARRAY_SIZE(btc_valid_sclk);
	rdev->pm.dpm.dyn_state.valid_sclk_values.values = btc_valid_sclk;
	rdev->pm.dpm.dyn_state.valid_mclk_values.count = 0;
	rdev->pm.dpm.dyn_state.valid_mclk_values.values = NULL;
	rdev->pm.dpm.dyn_state.sclk_mclk_delta = 12500;

	ni_pi->cac_data.leakage_coefficients.at = 516;
	ni_pi->cac_data.leakage_coefficients.bt = 18;
	ni_pi->cac_data.leakage_coefficients.av = 51;
	ni_pi->cac_data.leakage_coefficients.bv = 2957;

	switch (rdev->pdev->device) {
	case 0x6700:
	case 0x6701:
	case 0x6702:
	case 0x6703:
	case 0x6718:
		ni_pi->cac_weights = &cac_weights_cayman_xt;
		break;
	case 0x6705:
	case 0x6719:
	case 0x671D:
	case 0x671C:
	default:
		ni_pi->cac_weights = &cac_weights_cayman_pro;
		break;
	case 0x6704:
	case 0x6706:
	case 0x6707:
	case 0x6708:
	case 0x6709:
		ni_pi->cac_weights = &cac_weights_cayman_le;
		break;
	}

	if (ni_pi->cac_weights->enable_power_containment_by_default) {
		ni_pi->enable_power_containment = true;
		ni_pi->enable_cac = true;
		ni_pi->enable_sq_ramping = true;
	} else {
		ni_pi->enable_power_containment = false;
		ni_pi->enable_cac = false;
		ni_pi->enable_sq_ramping = false;
	}

	ni_pi->driver_calculate_cac_leakage = false;
	ni_pi->cac_configuration_required = true;

	if (ni_pi->cac_configuration_required) {
		ni_pi->support_cac_long_term_average = true;
		ni_pi->lta_window_size = ni_pi->cac_weights->l2_lta_window_size;
		ni_pi->lts_truncate = ni_pi->cac_weights->lts_truncate;
	} else {
		ni_pi->support_cac_long_term_average = false;
		ni_pi->lta_window_size = 0;
		ni_pi->lts_truncate = 0;
	}

	ni_pi->use_power_boost_limit = true;

	/* make sure dc limits are valid */
	if ((rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc.sclk == 0) ||
	    (rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc.mclk == 0))
		rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc =
			rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac;

	return 0;
}