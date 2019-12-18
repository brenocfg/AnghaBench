#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int ucEngineClockHigh; int ucMemoryClockHigh; int /*<<< orphan*/  ulFlags; int /*<<< orphan*/  usVDDC; int /*<<< orphan*/  usMemoryClockLow; int /*<<< orphan*/  usEngineClockLow; } ;
struct TYPE_9__ {int ucEngineClockHigh; int ucMemoryClockHigh; int /*<<< orphan*/  ulFlags; int /*<<< orphan*/  usVDDCI; int /*<<< orphan*/  usVDDC; int /*<<< orphan*/  usMemoryClockLow; int /*<<< orphan*/  usEngineClockLow; } ;
union pplib_clock_info {TYPE_2__ r600; TYPE_1__ evergreen; } ;
typedef  int u32 ;
typedef  void* u16 ;
struct rv7xx_pl {int vddc; int flags; int mclk; int sclk; void* vddci; } ;
struct rv7xx_ps {struct rv7xx_pl low; struct rv7xx_pl high; struct rv7xx_pl medium; } ;
struct rv7xx_power_info {int max_vddc; int acpi_vddc; int acpi_pcie_gen2; int min_vddc_in_table; int max_vddc_in_table; } ;
struct radeon_ps {int class; int class2; } ;
struct TYPE_13__ {int sclk; int mclk; int vddc; void* vddci; } ;
struct TYPE_14__ {TYPE_5__ max_clock_voltage_on_ac; } ;
struct TYPE_15__ {TYPE_6__ dyn_state; } ;
struct TYPE_16__ {TYPE_7__ dpm; } ;
struct TYPE_12__ {int default_mclk; int default_sclk; } ;
struct radeon_device {scalar_t__ family; TYPE_8__ pm; TYPE_4__ clock; } ;
struct TYPE_11__ {int supported; struct rv7xx_pl* pl; } ;
struct evergreen_power_info {TYPE_3__ ulv; void* acpi_vddci; } ;

/* Variables and functions */
 int ATOM_PPLIB_CLASSIFICATION2_ULV ; 
 int ATOM_PPLIB_CLASSIFICATION_ACPI ; 
 int ATOM_PPLIB_CLASSIFICATION_BOOT ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_MASK ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE ; 
 int ATOM_PPLIB_R600_FLAGS_PCIEGEN2 ; 
 scalar_t__ CHIP_BARTS ; 
 scalar_t__ CHIP_CEDAR ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atombios_get_default_voltages (struct radeon_device*,void**,void**,void**) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 struct rv7xx_ps* rv770_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void rv7xx_parse_pplib_clock_info(struct radeon_device *rdev,
					 struct radeon_ps *rps, int index,
					 union pplib_clock_info *clock_info)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct rv7xx_ps *ps = rv770_get_ps(rps);
	u32 sclk, mclk;
	struct rv7xx_pl *pl;

	switch (index) {
	case 0:
		pl = &ps->low;
		break;
	case 1:
		pl = &ps->medium;
		break;
	case 2:
	default:
		pl = &ps->high;
		break;
	}

	if (rdev->family >= CHIP_CEDAR) {
		sclk = le16_to_cpu(clock_info->evergreen.usEngineClockLow);
		sclk |= clock_info->evergreen.ucEngineClockHigh << 16;
		mclk = le16_to_cpu(clock_info->evergreen.usMemoryClockLow);
		mclk |= clock_info->evergreen.ucMemoryClockHigh << 16;

		pl->vddc = le16_to_cpu(clock_info->evergreen.usVDDC);
		pl->vddci = le16_to_cpu(clock_info->evergreen.usVDDCI);
		pl->flags = le32_to_cpu(clock_info->evergreen.ulFlags);
	} else {
		sclk = le16_to_cpu(clock_info->r600.usEngineClockLow);
		sclk |= clock_info->r600.ucEngineClockHigh << 16;
		mclk = le16_to_cpu(clock_info->r600.usMemoryClockLow);
		mclk |= clock_info->r600.ucMemoryClockHigh << 16;

		pl->vddc = le16_to_cpu(clock_info->r600.usVDDC);
		pl->flags = le32_to_cpu(clock_info->r600.ulFlags);
	}

	pl->mclk = mclk;
	pl->sclk = sclk;

	/* patch up vddc if necessary */
	if (pl->vddc == 0xff01) {
		if (pi->max_vddc)
			pl->vddc = pi->max_vddc;
	}

	if (rps->class & ATOM_PPLIB_CLASSIFICATION_ACPI) {
		pi->acpi_vddc = pl->vddc;
		if (rdev->family >= CHIP_CEDAR)
			eg_pi->acpi_vddci = pl->vddci;
		if (ps->low.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2)
			pi->acpi_pcie_gen2 = true;
		else
			pi->acpi_pcie_gen2 = false;
	}

	if (rps->class2 & ATOM_PPLIB_CLASSIFICATION2_ULV) {
		if (rdev->family >= CHIP_BARTS) {
			eg_pi->ulv.supported = true;
			eg_pi->ulv.pl = pl;
		}
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