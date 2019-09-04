#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_7__ {scalar_t__ engineClock; scalar_t__ memoryClock; } ;
struct TYPE_8__ {int /*<<< orphan*/  platformCaps; scalar_t__ TDPODLimit; TYPE_2__ overdriveLimit; } ;
struct TYPE_6__ {scalar_t__ ucType; } ;
struct pp_hwmgr {TYPE_3__ platform_descriptor; TYPE_1__ thermal_controller; scalar_t__ pptable; } ;
struct phm_ppt_v3_information {scalar_t__ uc_thermal_controller_type; int /*<<< orphan*/ * smc_pptable; int /*<<< orphan*/  power_saving_clock_min; int /*<<< orphan*/  power_saving_clock_max; int /*<<< orphan*/  us_software_shutdown_temp; int /*<<< orphan*/  us_od_powersave_power_limit; int /*<<< orphan*/  us_od_turbo_power_limit; int /*<<< orphan*/  us_boost_power_limit; int /*<<< orphan*/  us_small_power_limit2; int /*<<< orphan*/  us_small_power_limit1; int /*<<< orphan*/  od_settings_min; int /*<<< orphan*/  od_settings_max; } ;
struct TYPE_9__ {scalar_t__ ucThermalControllerType; scalar_t__* ODSettingsMax; scalar_t__* ODSettingsMin; int /*<<< orphan*/  smcPPTable; int /*<<< orphan*/  PowerSavingClockMin; int /*<<< orphan*/  PowerSavingClockMax; int /*<<< orphan*/  usSoftwareShutdownTemp; int /*<<< orphan*/  usODPowerSavePowerLimit; int /*<<< orphan*/  usODTurboPowerLimit; int /*<<< orphan*/  usBoostPowerLimit; int /*<<< orphan*/  usSmallPowerLimit2; int /*<<< orphan*/  usSmallPowerLimit1; } ;
typedef  int /*<<< orphan*/  PPTable_t ;
typedef  TYPE_4__ ATOM_Vega12_POWERPLAYTABLE ;

/* Variables and functions */
 size_t ATOM_VEGA12_ODSETTING_GFXCLKFMAX ; 
 size_t ATOM_VEGA12_ODSETTING_POWERPERCENTAGE ; 
 size_t ATOM_VEGA12_ODSETTING_UCLKFMAX ; 
 scalar_t__ ATOM_VEGA12_PP_THERMALCONTROLLER_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ACOverdriveSupport ; 
 int /*<<< orphan*/  PHM_PlatformCaps_MicrocodeFanControl ; 
 int /*<<< orphan*/  PHM_PlatformCaps_PowerControl ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ThermalController ; 
 scalar_t__ VEGA12_ENGINECLOCK_HARDMAX ; 
 int append_vbios_pptable (struct pp_hwmgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_clock_limits_array (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_overdrive_settings_limits_array (struct pp_hwmgr*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  phm_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_hw_cap (struct pp_hwmgr*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_powerplay_table_information(
		struct pp_hwmgr *hwmgr,
		const ATOM_Vega12_POWERPLAYTABLE *powerplay_table)
{
	struct phm_ppt_v3_information *pptable_information =
		(struct phm_ppt_v3_information *)hwmgr->pptable;
	uint32_t disable_power_control = 0;
	int result;

	hwmgr->thermal_controller.ucType = powerplay_table->ucThermalControllerType;
	pptable_information->uc_thermal_controller_type = powerplay_table->ucThermalControllerType;

	set_hw_cap(hwmgr,
		ATOM_VEGA12_PP_THERMALCONTROLLER_NONE != hwmgr->thermal_controller.ucType,
		PHM_PlatformCaps_ThermalController);

	phm_cap_set(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_MicrocodeFanControl);

	if (powerplay_table->ODSettingsMax[ATOM_VEGA12_ODSETTING_GFXCLKFMAX] > VEGA12_ENGINECLOCK_HARDMAX)
		hwmgr->platform_descriptor.overdriveLimit.engineClock = VEGA12_ENGINECLOCK_HARDMAX;
	else
		hwmgr->platform_descriptor.overdriveLimit.engineClock = powerplay_table->ODSettingsMax[ATOM_VEGA12_ODSETTING_GFXCLKFMAX];
	hwmgr->platform_descriptor.overdriveLimit.memoryClock = powerplay_table->ODSettingsMax[ATOM_VEGA12_ODSETTING_UCLKFMAX];

	copy_overdrive_settings_limits_array(hwmgr, &pptable_information->od_settings_max, powerplay_table->ODSettingsMax);
	copy_overdrive_settings_limits_array(hwmgr, &pptable_information->od_settings_min, powerplay_table->ODSettingsMin);

	/* hwmgr->platformDescriptor.minOverdriveVDDC = 0;
	hwmgr->platformDescriptor.maxOverdriveVDDC = 0;
	hwmgr->platformDescriptor.overdriveVDDCStep = 0; */

	if (hwmgr->platform_descriptor.overdriveLimit.engineClock > 0
		&& hwmgr->platform_descriptor.overdriveLimit.memoryClock > 0)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_ACOverdriveSupport);

	pptable_information->us_small_power_limit1 = powerplay_table->usSmallPowerLimit1;
	pptable_information->us_small_power_limit2 = powerplay_table->usSmallPowerLimit2;
	pptable_information->us_boost_power_limit = powerplay_table->usBoostPowerLimit;
	pptable_information->us_od_turbo_power_limit = powerplay_table->usODTurboPowerLimit;
	pptable_information->us_od_powersave_power_limit = powerplay_table->usODPowerSavePowerLimit;

	pptable_information->us_software_shutdown_temp = powerplay_table->usSoftwareShutdownTemp;

	hwmgr->platform_descriptor.TDPODLimit = (uint16_t)powerplay_table->ODSettingsMax[ATOM_VEGA12_ODSETTING_POWERPERCENTAGE];

	disable_power_control = 0;
	if (!disable_power_control) {
		/* enable TDP overdrive (PowerControl) feature as well if supported */
		if (hwmgr->platform_descriptor.TDPODLimit)
			phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_PowerControl);
	}

	copy_clock_limits_array(hwmgr, &pptable_information->power_saving_clock_max, powerplay_table->PowerSavingClockMax);
	copy_clock_limits_array(hwmgr, &pptable_information->power_saving_clock_min, powerplay_table->PowerSavingClockMin);

	pptable_information->smc_pptable = (PPTable_t *)kmalloc(sizeof(PPTable_t), GFP_KERNEL);
	if (pptable_information->smc_pptable == NULL)
		return -ENOMEM;

	memcpy(pptable_information->smc_pptable, &(powerplay_table->smcPPTable), sizeof(PPTable_t));

	result = append_vbios_pptable(hwmgr, (pptable_information->smc_pptable));

	return result;
}