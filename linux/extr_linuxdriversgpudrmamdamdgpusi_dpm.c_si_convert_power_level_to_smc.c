#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct si_power_info {scalar_t__ force_pcie_gen; int /*<<< orphan*/  max_cu; scalar_t__ vddc_phase_shed_control; } ;
struct rv7xx_power_info {scalar_t__ mclk_stutter_mode_threshold; scalar_t__ mclk_edc_enable_threshold; } ;
struct rv7xx_pl {scalar_t__ mclk; int /*<<< orphan*/  sclk; int /*<<< orphan*/  vddc; int /*<<< orphan*/  vddci; scalar_t__ pcie_gen; } ;
struct evergreen_power_info {scalar_t__ mclk_edc_wr_enable_threshold; int /*<<< orphan*/  vddci_voltage_table; scalar_t__ vddci_control; int /*<<< orphan*/  vddc_voltage_table; int /*<<< orphan*/  uvd_enabled; scalar_t__ pcie_performance_request; } ;
struct TYPE_11__ {int /*<<< orphan*/  phase_shedding_limits_table; } ;
struct TYPE_12__ {int new_active_crtc_count; TYPE_2__ dyn_state; } ;
struct TYPE_13__ {TYPE_3__ dpm; } ;
struct TYPE_10__ {scalar_t__ vram_type; } ;
struct amdgpu_device {TYPE_4__ pm; TYPE_1__ gmc; } ;
struct TYPE_15__ {int /*<<< orphan*/  index; } ;
struct TYPE_14__ {int strobeMode; int /*<<< orphan*/  mvdd; int /*<<< orphan*/  MaxPoweredUpCU; TYPE_6__ vddc; TYPE_6__ vddci; int /*<<< orphan*/  std_vddc; int /*<<< orphan*/  mclk; int /*<<< orphan*/  mcFlags; int /*<<< orphan*/  sclk; void* gen2PCIE; } ;
typedef  TYPE_5__ SISLANDS_SMC_HW_PERFORMANCE_LEVEL ;

/* Variables and functions */
 scalar_t__ AMDGPU_PCIE_GEN_INVALID ; 
 scalar_t__ AMDGPU_VRAM_TYPE_GDDR5 ; 
 int /*<<< orphan*/  DPG_PIPE_STUTTER_CONTROL ; 
 int /*<<< orphan*/  MC_SEQ_MISC5 ; 
 int /*<<< orphan*/  MC_SEQ_MISC6 ; 
 int /*<<< orphan*/  MC_SEQ_MISC7 ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SISLANDS_SMC_MC_EDC_RD_FLAG ; 
 int /*<<< orphan*/  SISLANDS_SMC_MC_EDC_WR_FLAG ; 
 int /*<<< orphan*/  SISLANDS_SMC_MC_PG_EN ; 
 int /*<<< orphan*/  SISLANDS_SMC_MC_STUTTER_EN ; 
 int SISLANDS_SMC_STROBE_ENABLE ; 
 int STUTTER_ENABLE ; 
 struct evergreen_power_info* evergreen_get_pi (struct amdgpu_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct amdgpu_device*) ; 
 int si_get_mclk_frequency_ratio (scalar_t__,int) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 
 int si_get_std_voltage_value (struct amdgpu_device*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 void* si_get_strobe_mode_settings (struct amdgpu_device*,scalar_t__) ; 
 int si_populate_mclk_value (struct amdgpu_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int) ; 
 int si_populate_mvdd_value (struct amdgpu_device*,scalar_t__,int /*<<< orphan*/ *) ; 
 int si_populate_phase_shedding_value (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_6__*) ; 
 int si_populate_sclk_value (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int si_populate_std_voltage_value (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int si_populate_voltage_value (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*) ; 

__attribute__((used)) static int si_convert_power_level_to_smc(struct amdgpu_device *adev,
					 struct rv7xx_pl *pl,
					 SISLANDS_SMC_HW_PERFORMANCE_LEVEL *level)
{
	struct rv7xx_power_info *pi = rv770_get_pi(adev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(adev);
	struct si_power_info *si_pi = si_get_pi(adev);
	int ret;
	bool dll_state_on;
	u16 std_vddc;
	bool gmc_pg = false;

	if (eg_pi->pcie_performance_request &&
	    (si_pi->force_pcie_gen != AMDGPU_PCIE_GEN_INVALID))
		level->gen2PCIE = (u8)si_pi->force_pcie_gen;
	else
		level->gen2PCIE = (u8)pl->pcie_gen;

	ret = si_populate_sclk_value(adev, pl->sclk, &level->sclk);
	if (ret)
		return ret;

	level->mcFlags =  0;

	if (pi->mclk_stutter_mode_threshold &&
	    (pl->mclk <= pi->mclk_stutter_mode_threshold) &&
	    !eg_pi->uvd_enabled &&
	    (RREG32(DPG_PIPE_STUTTER_CONTROL) & STUTTER_ENABLE) &&
	    (adev->pm.dpm.new_active_crtc_count <= 2)) {
		level->mcFlags |= SISLANDS_SMC_MC_STUTTER_EN;

		if (gmc_pg)
			level->mcFlags |= SISLANDS_SMC_MC_PG_EN;
	}

	if (adev->gmc.vram_type == AMDGPU_VRAM_TYPE_GDDR5) {
		if (pl->mclk > pi->mclk_edc_enable_threshold)
			level->mcFlags |= SISLANDS_SMC_MC_EDC_RD_FLAG;

		if (pl->mclk > eg_pi->mclk_edc_wr_enable_threshold)
			level->mcFlags |= SISLANDS_SMC_MC_EDC_WR_FLAG;

		level->strobeMode = si_get_strobe_mode_settings(adev, pl->mclk);

		if (level->strobeMode & SISLANDS_SMC_STROBE_ENABLE) {
			if (si_get_mclk_frequency_ratio(pl->mclk, true) >=
			    ((RREG32(MC_SEQ_MISC7) >> 16) & 0xf))
				dll_state_on = ((RREG32(MC_SEQ_MISC5) >> 1) & 0x1) ? true : false;
			else
				dll_state_on = ((RREG32(MC_SEQ_MISC6) >> 1) & 0x1) ? true : false;
		} else {
			dll_state_on = false;
		}
	} else {
		level->strobeMode = si_get_strobe_mode_settings(adev,
								pl->mclk);

		dll_state_on = ((RREG32(MC_SEQ_MISC5) >> 1) & 0x1) ? true : false;
	}

	ret = si_populate_mclk_value(adev,
				     pl->sclk,
				     pl->mclk,
				     &level->mclk,
				     (level->strobeMode & SISLANDS_SMC_STROBE_ENABLE) != 0, dll_state_on);
	if (ret)
		return ret;

	ret = si_populate_voltage_value(adev,
					&eg_pi->vddc_voltage_table,
					pl->vddc, &level->vddc);
	if (ret)
		return ret;


	ret = si_get_std_voltage_value(adev, &level->vddc, &std_vddc);
	if (ret)
		return ret;

	ret = si_populate_std_voltage_value(adev, std_vddc,
					    level->vddc.index, &level->std_vddc);
	if (ret)
		return ret;

	if (eg_pi->vddci_control) {
		ret = si_populate_voltage_value(adev, &eg_pi->vddci_voltage_table,
						pl->vddci, &level->vddci);
		if (ret)
			return ret;
	}

	if (si_pi->vddc_phase_shed_control) {
		ret = si_populate_phase_shedding_value(adev,
						       &adev->pm.dpm.dyn_state.phase_shedding_limits_table,
						       pl->vddc,
						       pl->sclk,
						       pl->mclk,
						       &level->vddc);
		if (ret)
			return ret;
	}

	level->MaxPoweredUpCU = si_pi->max_cu;

	ret = si_populate_mvdd_value(adev, pl->mclk, &level->mvdd);

	return ret;
}