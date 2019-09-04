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
struct TYPE_8__ {int ucEngineClockHigh; int ucMemoryClockHigh; int /*<<< orphan*/  ucPCIEGen; int /*<<< orphan*/  ulFlags; int /*<<< orphan*/  usVDDCI; int /*<<< orphan*/  usVDDC; int /*<<< orphan*/  usMemoryClockLow; int /*<<< orphan*/  usEngineClockLow; } ;
union pplib_clock_info {TYPE_1__ si; } ;
typedef  void* u16 ;
struct rv7xx_pl {int sclk; int mclk; scalar_t__ vddc; void* vddci; int /*<<< orphan*/  pcie_gen; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {int supported; int one_pcie_lane_in_ulv; int /*<<< orphan*/  cg_ulv_control; int /*<<< orphan*/  cg_ulv_parameter; int /*<<< orphan*/  volt_change_delay; struct rv7xx_pl pl; } ;
struct si_power_info {void* mvdd_bootup_value; TYPE_2__ ulv; int /*<<< orphan*/  acpi_pcie_gen; int /*<<< orphan*/  boot_pcie_gen; int /*<<< orphan*/  sys_pcie_mask; } ;
struct rv7xx_power_info {scalar_t__ acpi_vddc; scalar_t__ min_vddc_in_table; scalar_t__ max_vddc_in_table; } ;
struct radeon_ps {int class; int class2; } ;
struct TYPE_11__ {int sclk; int mclk; scalar_t__ vddc; void* vddci; } ;
struct TYPE_12__ {TYPE_4__ max_clock_voltage_on_ac; } ;
struct TYPE_13__ {TYPE_5__ dyn_state; } ;
struct TYPE_14__ {TYPE_6__ dpm; } ;
struct TYPE_10__ {int default_mclk; int default_sclk; } ;
struct radeon_device {TYPE_7__ pm; TYPE_3__ clock; } ;
struct ni_ps {int performance_level_count; struct rv7xx_pl* performance_levels; } ;
struct evergreen_power_info {void* acpi_vddci; } ;

/* Variables and functions */
 int ATOM_PPLIB_CLASSIFICATION2_ULV ; 
 int ATOM_PPLIB_CLASSIFICATION_ACPI ; 
 int ATOM_PPLIB_CLASSIFICATION_BOOT ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_MASK ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE ; 
 int /*<<< orphan*/  SISLANDS_CGULVCONTROL_DFLT ; 
 int /*<<< orphan*/  SISLANDS_CGULVPARAMETER_DFLT ; 
 int /*<<< orphan*/  SISLANDS_ULVVOLTAGECHANGEDELAY_DFLT ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 
 int /*<<< orphan*/  r600_get_pcie_gen_support (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atombios_get_default_voltages (struct radeon_device*,void**,void**,void**) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int si_get_leakage_voltage_from_leakage_index (struct radeon_device*,scalar_t__,void**) ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void si_parse_pplib_clock_info(struct radeon_device *rdev,
				      struct radeon_ps *rps, int index,
				      union pplib_clock_info *clock_info)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct si_power_info *si_pi = si_get_pi(rdev);
	struct ni_ps *ps = ni_get_ps(rps);
	u16 leakage_voltage;
	struct rv7xx_pl *pl = &ps->performance_levels[index];
	int ret;

	ps->performance_level_count = index + 1;

	pl->sclk = le16_to_cpu(clock_info->si.usEngineClockLow);
	pl->sclk |= clock_info->si.ucEngineClockHigh << 16;
	pl->mclk = le16_to_cpu(clock_info->si.usMemoryClockLow);
	pl->mclk |= clock_info->si.ucMemoryClockHigh << 16;

	pl->vddc = le16_to_cpu(clock_info->si.usVDDC);
	pl->vddci = le16_to_cpu(clock_info->si.usVDDCI);
	pl->flags = le32_to_cpu(clock_info->si.ulFlags);
	pl->pcie_gen = r600_get_pcie_gen_support(rdev,
						 si_pi->sys_pcie_mask,
						 si_pi->boot_pcie_gen,
						 clock_info->si.ucPCIEGen);

	/* patch up vddc if necessary */
	ret = si_get_leakage_voltage_from_leakage_index(rdev, pl->vddc,
							&leakage_voltage);
	if (ret == 0)
		pl->vddc = leakage_voltage;

	if (rps->class & ATOM_PPLIB_CLASSIFICATION_ACPI) {
		pi->acpi_vddc = pl->vddc;
		eg_pi->acpi_vddci = pl->vddci;
		si_pi->acpi_pcie_gen = pl->pcie_gen;
	}

	if ((rps->class2 & ATOM_PPLIB_CLASSIFICATION2_ULV) &&
	    index == 0) {
		/* XXX disable for A0 tahiti */
		si_pi->ulv.supported = false;
		si_pi->ulv.pl = *pl;
		si_pi->ulv.one_pcie_lane_in_ulv = false;
		si_pi->ulv.volt_change_delay = SISLANDS_ULVVOLTAGECHANGEDELAY_DFLT;
		si_pi->ulv.cg_ulv_parameter = SISLANDS_CGULVPARAMETER_DFLT;
		si_pi->ulv.cg_ulv_control = SISLANDS_CGULVCONTROL_DFLT;
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
		si_pi->mvdd_bootup_value = mvdd;
	}

	if ((rps->class & ATOM_PPLIB_CLASSIFICATION_UI_MASK) ==
	    ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE) {
		rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac.sclk = pl->sclk;
		rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac.mclk = pl->mclk;
		rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac.vddc = pl->vddc;
		rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac.vddci = pl->vddci;
	}
}