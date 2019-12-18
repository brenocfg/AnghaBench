#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ucEngineClockHigh; int ucMemoryClockHigh; int /*<<< orphan*/  ulFlags; int /*<<< orphan*/  usVDDCI; int /*<<< orphan*/  usVDDC; int /*<<< orphan*/  usMemoryClockLow; int /*<<< orphan*/  usEngineClockLow; } ;
union pplib_clock_info {TYPE_1__ evergreen; } ;
typedef  void* u16 ;
struct rv7xx_power_info {int max_vddc; int acpi_vddc; int acpi_pcie_gen2; int min_vddc_in_table; int max_vddc_in_table; } ;
struct rv7xx_pl {int sclk; int mclk; int vddc; int flags; void* vddci; } ;
struct radeon_ps {int class; int class2; } ;
struct TYPE_11__ {int sclk; int mclk; int vddc; void* vddci; } ;
struct TYPE_12__ {TYPE_4__ max_clock_voltage_on_ac; } ;
struct TYPE_13__ {TYPE_5__ dyn_state; } ;
struct TYPE_14__ {TYPE_6__ dpm; } ;
struct TYPE_10__ {int default_mclk; int default_sclk; } ;
struct radeon_device {TYPE_7__ pm; TYPE_3__ clock; } ;
struct ni_ps {int performance_level_count; struct rv7xx_pl* performance_levels; } ;
struct TYPE_9__ {int supported; struct rv7xx_pl* pl; } ;
struct evergreen_power_info {TYPE_2__ ulv; void* acpi_vddci; } ;

/* Variables and functions */
 int ATOM_PPLIB_CLASSIFICATION2_ULV ; 
 int ATOM_PPLIB_CLASSIFICATION_ACPI ; 
 int ATOM_PPLIB_CLASSIFICATION_BOOT ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_MASK ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE ; 
 int ATOM_PPLIB_R600_FLAGS_PCIEGEN2 ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 
 int /*<<< orphan*/  radeon_atombios_get_default_voltages (struct radeon_device*,void**,void**,void**) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void ni_parse_pplib_clock_info(struct radeon_device *rdev,
				      struct radeon_ps *rps, int index,
				      union pplib_clock_info *clock_info)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct ni_ps *ps = ni_get_ps(rps);
	struct rv7xx_pl *pl = &ps->performance_levels[index];

	ps->performance_level_count = index + 1;

	pl->sclk = le16_to_cpu(clock_info->evergreen.usEngineClockLow);
	pl->sclk |= clock_info->evergreen.ucEngineClockHigh << 16;
	pl->mclk = le16_to_cpu(clock_info->evergreen.usMemoryClockLow);
	pl->mclk |= clock_info->evergreen.ucMemoryClockHigh << 16;

	pl->vddc = le16_to_cpu(clock_info->evergreen.usVDDC);
	pl->vddci = le16_to_cpu(clock_info->evergreen.usVDDCI);
	pl->flags = le32_to_cpu(clock_info->evergreen.ulFlags);

	/* patch up vddc if necessary */
	if (pl->vddc == 0xff01) {
		if (pi->max_vddc)
			pl->vddc = pi->max_vddc;
	}

	if (rps->class & ATOM_PPLIB_CLASSIFICATION_ACPI) {
		pi->acpi_vddc = pl->vddc;
		eg_pi->acpi_vddci = pl->vddci;
		if (ps->performance_levels[0].flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2)
			pi->acpi_pcie_gen2 = true;
		else
			pi->acpi_pcie_gen2 = false;
	}

	if (rps->class2 & ATOM_PPLIB_CLASSIFICATION2_ULV) {
		eg_pi->ulv.supported = true;
		eg_pi->ulv.pl = pl;
	}

	if (pi->min_vddc_in_table > pl->vddc)
		pi->min_vddc_in_table = pl->vddc;

	if (pi->max_vddc_in_table < pl->vddc)
		pi->max_vddc_in_table = pl->vddc;

	/* patch up boot state */
	if (rps->class & ATOM_PPLIB_CLASSIFICATION_BOOT) {
		u16 vddc, vddci, mvdd;
		radeon_atombios_get_default_voltages(rdev, &vddc, &vddci, &mvdd);
		pl->mclk = rdev->clock.default_mclk;
		pl->sclk = rdev->clock.default_sclk;
		pl->vddc = vddc;
		pl->vddci = vddci;
	}

	if ((rps->class & ATOM_PPLIB_CLASSIFICATION_UI_MASK) ==
	    ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE) {
		rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac.sclk = pl->sclk;
		rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac.mclk = pl->mclk;
		rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac.vddc = pl->vddc;
		rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac.vddci = pl->vddci;
	}
}