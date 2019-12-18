#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rv7xx_power_info {scalar_t__ mclk_stutter_mode_threshold; scalar_t__ mclk_edc_enable_threshold; scalar_t__ mem_gddr5; scalar_t__ pcie_gen2; } ;
struct rv7xx_pl {int flags; scalar_t__ mclk; int /*<<< orphan*/  vddci; int /*<<< orphan*/  vddc; int /*<<< orphan*/  sclk; } ;
struct radeon_device {int dummy; } ;
struct evergreen_power_info {scalar_t__ mclk_edc_wr_enable_threshold; int dll_default_on; int /*<<< orphan*/  vddci_voltage_table; scalar_t__ vddci_control; int /*<<< orphan*/  vddc_voltage_table; scalar_t__ sclk_deep_sleep; int /*<<< orphan*/  uvd_enabled; } ;
struct TYPE_3__ {int gen2PCIE; int gen2XSP; int backbias; int strobeMode; int /*<<< orphan*/  mvdd; int /*<<< orphan*/  vddci; int /*<<< orphan*/  vddc; int /*<<< orphan*/  mclk; int /*<<< orphan*/  mcFlags; int /*<<< orphan*/  stateFlags; int /*<<< orphan*/  sclk; int /*<<< orphan*/  displayWatermark; } ;
typedef  TYPE_1__ RV770_SMC_HW_PERFORMANCE_LEVEL ;

/* Variables and functions */
 int ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE ; 
 int ATOM_PPLIB_R600_FLAGS_PCIEGEN2 ; 
 int /*<<< orphan*/  MC_SEQ_MISC5 ; 
 int /*<<< orphan*/  MC_SEQ_MISC6 ; 
 int /*<<< orphan*/  MC_SEQ_MISC7 ; 
 int /*<<< orphan*/  PPSMC_STATEFLAG_AUTO_PULSE_SKIP ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_MC_EDC_RD_FLAG ; 
 int /*<<< orphan*/  SMC_MC_EDC_WR_FLAG ; 
 int /*<<< orphan*/  SMC_MC_STUTTER_EN ; 
 int SMC_STROBE_ENABLE ; 
 int cypress_get_mclk_frequency_ratio (struct radeon_device*,scalar_t__,int) ; 
 int cypress_get_strobe_mode_settings (struct radeon_device*,scalar_t__) ; 
 int cypress_populate_mclk_value (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int) ; 
 int cypress_populate_mvdd_value (struct radeon_device*,scalar_t__,int /*<<< orphan*/ *) ; 
 int cypress_populate_voltage_value (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 int rv740_populate_sclk_value (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

int cypress_convert_power_level_to_smc(struct radeon_device *rdev,
				       struct rv7xx_pl *pl,
				       RV770_SMC_HW_PERFORMANCE_LEVEL *level,
				       u8 watermark_level)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	int ret;
	bool dll_state_on;

	level->gen2PCIE = pi->pcie_gen2 ?
		((pl->flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2) ? 1 : 0) : 0;
	level->gen2XSP  = (pl->flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2) ? 1 : 0;
	level->backbias = (pl->flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE) ? 1 : 0;
	level->displayWatermark = watermark_level;

	ret = rv740_populate_sclk_value(rdev, pl->sclk, &level->sclk);
	if (ret)
		return ret;

	level->mcFlags =  0;
	if (pi->mclk_stutter_mode_threshold &&
	    (pl->mclk <= pi->mclk_stutter_mode_threshold) &&
	    !eg_pi->uvd_enabled) {
		level->mcFlags |= SMC_MC_STUTTER_EN;
		if (eg_pi->sclk_deep_sleep)
			level->stateFlags |= PPSMC_STATEFLAG_AUTO_PULSE_SKIP;
		else
			level->stateFlags &= ~PPSMC_STATEFLAG_AUTO_PULSE_SKIP;
	}

	if (pi->mem_gddr5) {
		if (pl->mclk > pi->mclk_edc_enable_threshold)
			level->mcFlags |= SMC_MC_EDC_RD_FLAG;

		if (pl->mclk > eg_pi->mclk_edc_wr_enable_threshold)
			level->mcFlags |= SMC_MC_EDC_WR_FLAG;

		level->strobeMode = cypress_get_strobe_mode_settings(rdev, pl->mclk);

		if (level->strobeMode & SMC_STROBE_ENABLE) {
			if (cypress_get_mclk_frequency_ratio(rdev, pl->mclk, true) >=
			    ((RREG32(MC_SEQ_MISC7) >> 16) & 0xf))
				dll_state_on = ((RREG32(MC_SEQ_MISC5) >> 1) & 0x1) ? true : false;
			else
				dll_state_on = ((RREG32(MC_SEQ_MISC6) >> 1) & 0x1) ? true : false;
		} else
			dll_state_on = eg_pi->dll_default_on;

		ret = cypress_populate_mclk_value(rdev,
						  pl->sclk,
						  pl->mclk,
						  &level->mclk,
						  (level->strobeMode & SMC_STROBE_ENABLE) != 0,
						  dll_state_on);
	} else {
		ret = cypress_populate_mclk_value(rdev,
						  pl->sclk,
						  pl->mclk,
						  &level->mclk,
						  true,
						  true);
	}
	if (ret)
		return ret;

	ret = cypress_populate_voltage_value(rdev,
					     &eg_pi->vddc_voltage_table,
					     pl->vddc,
					     &level->vddc);
	if (ret)
		return ret;

	if (eg_pi->vddci_control) {
		ret = cypress_populate_voltage_value(rdev,
						     &eg_pi->vddci_voltage_table,
						     pl->vddci,
						     &level->vddci);
		if (ret)
			return ret;
	}

	ret = cypress_populate_mvdd_value(rdev, pl->mclk, &level->mvdd);

	return ret;
}