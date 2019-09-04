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
struct rv7xx_power_info {scalar_t__ mclk_strobe_mode_threshold; scalar_t__ mclk_edc_enable_threshold; scalar_t__ mem_gddr5; scalar_t__ pcie_gen2; } ;
struct rv7xx_pl {int flags; scalar_t__ mclk; int /*<<< orphan*/  vddc; int /*<<< orphan*/  sclk; } ;
struct radeon_device {scalar_t__ family; } ;
struct TYPE_3__ {int gen2PCIE; int gen2XSP; int backbias; int strobeMode; int mcFlags; int /*<<< orphan*/  mvdd; int /*<<< orphan*/  vddc; int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; int /*<<< orphan*/  displayWatermark; } ;
typedef  TYPE_1__ RV770_SMC_HW_PERFORMANCE_LEVEL ;

/* Variables and functions */
 int ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE ; 
 int ATOM_PPLIB_R600_FLAGS_PCIEGEN2 ; 
 scalar_t__ CHIP_RV710 ; 
 scalar_t__ CHIP_RV730 ; 
 scalar_t__ CHIP_RV740 ; 
 int SMC_MC_EDC_RD_FLAG ; 
 int SMC_MC_EDC_WR_FLAG ; 
 int rv730_populate_mclk_value (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int rv730_populate_sclk_value (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rv740_get_mclk_frequency_ratio (scalar_t__) ; 
 int rv740_populate_mclk_value (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int rv740_populate_sclk_value (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int rv770_populate_mclk_value (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int rv770_populate_mvdd_value (struct radeon_device*,scalar_t__,int /*<<< orphan*/ *) ; 
 int rv770_populate_sclk_value (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rv770_populate_vddc_value (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rv770_convert_power_level_to_smc(struct radeon_device *rdev,
					    struct rv7xx_pl *pl,
					    RV770_SMC_HW_PERFORMANCE_LEVEL *level,
					    u8 watermark_level)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	int ret;

	level->gen2PCIE = pi->pcie_gen2 ?
		((pl->flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2) ? 1 : 0) : 0;
	level->gen2XSP  = (pl->flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2) ? 1 : 0;
	level->backbias = (pl->flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE) ? 1 : 0;
	level->displayWatermark = watermark_level;

	if (rdev->family == CHIP_RV740)
		ret = rv740_populate_sclk_value(rdev, pl->sclk,
						&level->sclk);
	else if ((rdev->family == CHIP_RV730) || (rdev->family == CHIP_RV710))
		ret = rv730_populate_sclk_value(rdev, pl->sclk,
						&level->sclk);
	else
		ret = rv770_populate_sclk_value(rdev, pl->sclk,
						&level->sclk);
	if (ret)
		return ret;

	if (rdev->family == CHIP_RV740) {
		if (pi->mem_gddr5) {
			if (pl->mclk <= pi->mclk_strobe_mode_threshold)
				level->strobeMode =
					rv740_get_mclk_frequency_ratio(pl->mclk) | 0x10;
			else
				level->strobeMode = 0;

			if (pl->mclk > pi->mclk_edc_enable_threshold)
				level->mcFlags = SMC_MC_EDC_RD_FLAG | SMC_MC_EDC_WR_FLAG;
			else
				level->mcFlags =  0;
		}
		ret = rv740_populate_mclk_value(rdev, pl->sclk,
						pl->mclk, &level->mclk);
	} else if ((rdev->family == CHIP_RV730) || (rdev->family == CHIP_RV710))
		ret = rv730_populate_mclk_value(rdev, pl->sclk,
						pl->mclk, &level->mclk);
	else
		ret = rv770_populate_mclk_value(rdev, pl->sclk,
						pl->mclk, &level->mclk);
	if (ret)
		return ret;

	ret = rv770_populate_vddc_value(rdev, pl->vddc,
					&level->vddc);
	if (ret)
		return ret;

	ret = rv770_populate_mvdd_value(rdev, pl->mclk, &level->mvdd);

	return ret;
}