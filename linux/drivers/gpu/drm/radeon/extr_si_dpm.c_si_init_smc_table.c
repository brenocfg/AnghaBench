#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_12__ {scalar_t__ vddc; } ;
struct si_ulv_param {int /*<<< orphan*/  cg_ulv_parameter; int /*<<< orphan*/  cg_ulv_control; TYPE_4__ pl; scalar_t__ supported; } ;
struct TYPE_13__ {int /*<<< orphan*/  initialState; int /*<<< orphan*/  ULVState; int /*<<< orphan*/  driverState; int /*<<< orphan*/  systemFlags; int /*<<< orphan*/  extraFlags; int /*<<< orphan*/  thermalProtectType; } ;
struct si_power_info {int /*<<< orphan*/  sram_end; int /*<<< orphan*/  state_table_start; TYPE_5__ smc_statetable; struct si_ulv_param ulv; } ;
struct rv7xx_power_info {scalar_t__ mem_gddr5; } ;
struct radeon_ps {int dummy; } ;
struct TYPE_10__ {int platform_caps; int /*<<< orphan*/  backbias_response_time; struct radeon_ps* boot_ps; } ;
struct TYPE_11__ {int int_thermal_type; TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; TYPE_1__* pdev; } ;
struct TYPE_9__ {int device; } ;
typedef  TYPE_5__ SISLANDS_SMC_STATETABLE ;

/* Variables and functions */
 int ATOM_PP_PLATFORM_CAP_HARDWAREDC ; 
 int ATOM_PP_PLATFORM_CAP_REGULATOR_HOT ; 
 int ATOM_PP_PLATFORM_CAP_REVERT_GPIO5_POLARITY ; 
 int ATOM_PP_PLATFORM_CAP_STEPVDDC ; 
 int ATOM_PP_PLATFORM_CAP_VRHOT_GPIO_CONFIGURABLE ; 
 int /*<<< orphan*/  CG_ULV_CONTROL ; 
 int /*<<< orphan*/  CG_ULV_PARAMETER ; 
 int /*<<< orphan*/  PPSMC_EXTRAFLAGS_AC2DC_GPIO5_POLARITY_HIGH ; 
 int /*<<< orphan*/  PPSMC_SYSTEMFLAG_GDDR5 ; 
 int /*<<< orphan*/  PPSMC_SYSTEMFLAG_GPIO_DC ; 
 int /*<<< orphan*/  PPSMC_SYSTEMFLAG_REGULATOR_HOT ; 
 int /*<<< orphan*/  PPSMC_SYSTEMFLAG_REGULATOR_HOT_PROG_GPIO ; 
 int /*<<< orphan*/  PPSMC_SYSTEMFLAG_STEPVDDC ; 
 int /*<<< orphan*/  PPSMC_THERMAL_PROTECT_TYPE_EXTERNAL ; 
 int /*<<< orphan*/  PPSMC_THERMAL_PROTECT_TYPE_INTERNAL ; 
 int /*<<< orphan*/  PPSMC_THERMAL_PROTECT_TYPE_NONE ; 
 int /*<<< orphan*/  SISLANDS_INITIAL_STATE_ARB_INDEX ; 
 int /*<<< orphan*/  SI_SMC_SOFT_REGISTER_non_ulv_pcie_link_width ; 
 int /*<<< orphan*/  SI_SMC_SOFT_REGISTER_vr_hot_gpio ; 
#define  THERMAL_TYPE_EMC2103_WITH_INTERNAL 130 
#define  THERMAL_TYPE_NONE 129 
#define  THERMAL_TYPE_SI 128 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_get_pcie_lanes (struct radeon_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int si_copy_bytes_to_smc (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int si_do_program_memory_timing_parameters (struct radeon_device*,struct radeon_ps*,int /*<<< orphan*/ ) ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 
 int si_populate_smc_acpi_state (struct radeon_device*,TYPE_5__*) ; 
 int si_populate_smc_initial_state (struct radeon_device*,struct radeon_ps*,TYPE_5__*) ; 
 int /*<<< orphan*/  si_populate_smc_voltage_tables (struct radeon_device*,TYPE_5__*) ; 
 int si_populate_ulv_state (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int si_program_ulv_memory_timing_parameters (struct radeon_device*) ; 
 int /*<<< orphan*/  si_write_smc_soft_register (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si_init_smc_table(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct si_power_info *si_pi = si_get_pi(rdev);
	struct radeon_ps *radeon_boot_state = rdev->pm.dpm.boot_ps;
	const struct si_ulv_param *ulv = &si_pi->ulv;
	SISLANDS_SMC_STATETABLE  *table = &si_pi->smc_statetable;
	int ret;
	u32 lane_width;
	u32 vr_hot_gpio;

	si_populate_smc_voltage_tables(rdev, table);

	switch (rdev->pm.int_thermal_type) {
	case THERMAL_TYPE_SI:
	case THERMAL_TYPE_EMC2103_WITH_INTERNAL:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_INTERNAL;
		break;
	case THERMAL_TYPE_NONE:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_NONE;
		break;
	default:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_EXTERNAL;
		break;
	}

	if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_HARDWAREDC)
		table->systemFlags |= PPSMC_SYSTEMFLAG_GPIO_DC;

	if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_REGULATOR_HOT) {
		if ((rdev->pdev->device != 0x6818) && (rdev->pdev->device != 0x6819))
			table->systemFlags |= PPSMC_SYSTEMFLAG_REGULATOR_HOT;
	}

	if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_STEPVDDC)
		table->systemFlags |= PPSMC_SYSTEMFLAG_STEPVDDC;

	if (pi->mem_gddr5)
		table->systemFlags |= PPSMC_SYSTEMFLAG_GDDR5;

	if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_REVERT_GPIO5_POLARITY)
		table->extraFlags |= PPSMC_EXTRAFLAGS_AC2DC_GPIO5_POLARITY_HIGH;

	if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_VRHOT_GPIO_CONFIGURABLE) {
		table->systemFlags |= PPSMC_SYSTEMFLAG_REGULATOR_HOT_PROG_GPIO;
		vr_hot_gpio = rdev->pm.dpm.backbias_response_time;
		si_write_smc_soft_register(rdev, SI_SMC_SOFT_REGISTER_vr_hot_gpio,
					   vr_hot_gpio);
	}

	ret = si_populate_smc_initial_state(rdev, radeon_boot_state, table);
	if (ret)
		return ret;

	ret = si_populate_smc_acpi_state(rdev, table);
	if (ret)
		return ret;

	table->driverState = table->initialState;

	ret = si_do_program_memory_timing_parameters(rdev, radeon_boot_state,
						     SISLANDS_INITIAL_STATE_ARB_INDEX);
	if (ret)
		return ret;

	if (ulv->supported && ulv->pl.vddc) {
		ret = si_populate_ulv_state(rdev, &table->ULVState);
		if (ret)
			return ret;

		ret = si_program_ulv_memory_timing_parameters(rdev);
		if (ret)
			return ret;

		WREG32(CG_ULV_CONTROL, ulv->cg_ulv_control);
		WREG32(CG_ULV_PARAMETER, ulv->cg_ulv_parameter);

		lane_width = radeon_get_pcie_lanes(rdev);
		si_write_smc_soft_register(rdev, SI_SMC_SOFT_REGISTER_non_ulv_pcie_link_width, lane_width);
	} else {
		table->ULVState = table->initialState;
	}

	return si_copy_bytes_to_smc(rdev, si_pi->state_table_start,
				    (u8 *)table, sizeof(SISLANDS_SMC_STATETABLE),
				    si_pi->sram_end);
}