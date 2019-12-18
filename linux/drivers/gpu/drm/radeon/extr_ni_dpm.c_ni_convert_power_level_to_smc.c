#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rv7xx_power_info {scalar_t__ mclk_stutter_mode_threshold; scalar_t__ mclk_edc_enable_threshold; scalar_t__ mem_gddr5; scalar_t__ pcie_gen2; } ;
struct rv7xx_pl {int flags; scalar_t__ mclk; int /*<<< orphan*/  vddci; int /*<<< orphan*/  vddc; int /*<<< orphan*/  sclk; } ;
struct radeon_device {int dummy; } ;
struct ni_power_info {scalar_t__ mclk_rtt_mode_threshold; } ;
struct evergreen_power_info {scalar_t__ mclk_edc_wr_enable_threshold; int /*<<< orphan*/  vddci_voltage_table; scalar_t__ vddci_control; int /*<<< orphan*/  vddc_voltage_table; int /*<<< orphan*/  uvd_enabled; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
struct TYPE_5__ {int gen2PCIE; int strobeMode; int /*<<< orphan*/  mvdd; TYPE_2__ vddci; int /*<<< orphan*/  std_vddc; TYPE_2__ vddc; int /*<<< orphan*/  mclk; int /*<<< orphan*/  mcFlags; int /*<<< orphan*/  sclk; } ;
typedef  TYPE_1__ NISLANDS_SMC_HW_PERFORMANCE_LEVEL ;

/* Variables and functions */
 int ATOM_PPLIB_R600_FLAGS_PCIEGEN2 ; 
 int /*<<< orphan*/  DC_STUTTER_CNTL ; 
 int DC_STUTTER_ENABLE_A ; 
 int DC_STUTTER_ENABLE_B ; 
 int /*<<< orphan*/  MC_SEQ_MISC5 ; 
 int /*<<< orphan*/  MC_SEQ_MISC6 ; 
 int /*<<< orphan*/  MC_SEQ_MISC7 ; 
 int /*<<< orphan*/  NISLANDS_SMC_MC_EDC_RD_FLAG ; 
 int /*<<< orphan*/  NISLANDS_SMC_MC_EDC_WR_FLAG ; 
 int /*<<< orphan*/  NISLANDS_SMC_MC_RTT_ENABLE ; 
 int /*<<< orphan*/  NISLANDS_SMC_MC_STUTTER_EN ; 
 int NISLANDS_SMC_STROBE_ENABLE ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int cypress_get_mclk_frequency_ratio (struct radeon_device*,scalar_t__,int) ; 
 int cypress_get_strobe_mode_settings (struct radeon_device*,scalar_t__) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 
 int ni_get_std_voltage_value (struct radeon_device*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ni_populate_mclk_value (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ni_populate_mvdd_value (struct radeon_device*,scalar_t__,int /*<<< orphan*/ *) ; 
 int ni_populate_sclk_value (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ni_populate_std_voltage_value (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ni_populate_voltage_value (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int ni_convert_power_level_to_smc(struct radeon_device *rdev,
					 struct rv7xx_pl *pl,
					 NISLANDS_SMC_HW_PERFORMANCE_LEVEL *level)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	int ret;
	bool dll_state_on;
	u16 std_vddc;
	u32 tmp = RREG32(DC_STUTTER_CNTL);

	level->gen2PCIE = pi->pcie_gen2 ?
		((pl->flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2) ? 1 : 0) : 0;

	ret = ni_populate_sclk_value(rdev, pl->sclk, &level->sclk);
	if (ret)
		return ret;

	level->mcFlags =  0;
	if (pi->mclk_stutter_mode_threshold &&
	    (pl->mclk <= pi->mclk_stutter_mode_threshold) &&
	    !eg_pi->uvd_enabled &&
	    (tmp & DC_STUTTER_ENABLE_A) &&
	    (tmp & DC_STUTTER_ENABLE_B))
		level->mcFlags |= NISLANDS_SMC_MC_STUTTER_EN;

	if (pi->mem_gddr5) {
		if (pl->mclk > pi->mclk_edc_enable_threshold)
			level->mcFlags |= NISLANDS_SMC_MC_EDC_RD_FLAG;
		if (pl->mclk > eg_pi->mclk_edc_wr_enable_threshold)
			level->mcFlags |= NISLANDS_SMC_MC_EDC_WR_FLAG;

		level->strobeMode = cypress_get_strobe_mode_settings(rdev, pl->mclk);

		if (level->strobeMode & NISLANDS_SMC_STROBE_ENABLE) {
			if (cypress_get_mclk_frequency_ratio(rdev, pl->mclk, true) >=
			    ((RREG32(MC_SEQ_MISC7) >> 16) & 0xf))
				dll_state_on = ((RREG32(MC_SEQ_MISC5) >> 1) & 0x1) ? true : false;
			else
				dll_state_on = ((RREG32(MC_SEQ_MISC6) >> 1) & 0x1) ? true : false;
		} else {
			dll_state_on = false;
			if (pl->mclk > ni_pi->mclk_rtt_mode_threshold)
				level->mcFlags |= NISLANDS_SMC_MC_RTT_ENABLE;
		}

		ret = ni_populate_mclk_value(rdev, pl->sclk, pl->mclk,
					     &level->mclk,
					     (level->strobeMode & NISLANDS_SMC_STROBE_ENABLE) != 0,
					     dll_state_on);
	} else
		ret = ni_populate_mclk_value(rdev, pl->sclk, pl->mclk, &level->mclk, 1, 1);

	if (ret)
		return ret;

	ret = ni_populate_voltage_value(rdev, &eg_pi->vddc_voltage_table,
					pl->vddc, &level->vddc);
	if (ret)
		return ret;

	ret = ni_get_std_voltage_value(rdev, &level->vddc, &std_vddc);
	if (ret)
		return ret;

	ni_populate_std_voltage_value(rdev, std_vddc,
				      level->vddc.index, &level->std_vddc);

	if (eg_pi->vddci_control) {
		ret = ni_populate_voltage_value(rdev, &eg_pi->vddci_voltage_table,
						pl->vddci, &level->vddci);
		if (ret)
			return ret;
	}

	ni_populate_mvdd_value(rdev, pl->mclk, &level->mvdd);

	return ret;
}