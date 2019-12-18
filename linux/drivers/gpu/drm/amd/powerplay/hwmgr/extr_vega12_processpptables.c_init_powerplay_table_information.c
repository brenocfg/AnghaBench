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
struct TYPE_7__ {scalar_t__ engineClock; scalar_t__ memoryClock; } ;
struct TYPE_8__ {int /*<<< orphan*/  platformCaps; scalar_t__ TDPODLimit; TYPE_2__ overdriveLimit; } ;
struct TYPE_6__ {scalar_t__ ucType; } ;
struct pp_hwmgr {TYPE_3__ platform_descriptor; TYPE_1__ thermal_controller; scalar_t__ pptable; } ;
struct phm_ppt_v3_information {scalar_t__ uc_thermal_controller_type; int /*<<< orphan*/ * smc_pptable; int /*<<< orphan*/  power_saving_clock_min; int /*<<< orphan*/  power_saving_clock_max; void* us_software_shutdown_temp; void* us_od_powersave_power_limit; void* us_od_turbo_power_limit; void* us_boost_power_limit; void* us_small_power_limit2; void* us_small_power_limit1; int /*<<< orphan*/  od_settings_min; int /*<<< orphan*/  od_settings_max; } ;
struct TYPE_9__ {scalar_t__ ucThermalControllerType; int /*<<< orphan*/  smcPPTable; int /*<<< orphan*/  PowerSavingClockMin; int /*<<< orphan*/  PowerSavingClockMax; int /*<<< orphan*/ * ODSettingsMax; int /*<<< orphan*/  usSoftwareShutdownTemp; int /*<<< orphan*/  usODPowerSavePowerLimit; int /*<<< orphan*/  usODTurboPowerLimit; int /*<<< orphan*/  usBoostPowerLimit; int /*<<< orphan*/  usSmallPowerLimit2; int /*<<< orphan*/  usSmallPowerLimit1; int /*<<< orphan*/ * ODSettingsMin; } ;
typedef  int /*<<< orphan*/  PPTable_t ;
typedef  TYPE_4__ ATOM_Vega12_POWERPLAYTABLE ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_VEGA12_ODSETTING_COUNT ; 
 size_t ATOM_VEGA12_ODSETTING_GFXCLKFMAX ; 
 size_t ATOM_VEGA12_ODSETTING_POWERPERCENTAGE ; 
 size_t ATOM_VEGA12_ODSETTING_UCLKFMAX ; 
 int /*<<< orphan*/  ATOM_VEGA12_PPCLOCK_COUNT ; 
 scalar_t__ ATOM_VEGA12_PP_THERMALCONTROLLER_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ACOverdriveSupport ; 
 int /*<<< orphan*/  PHM_PlatformCaps_MicrocodeFanControl ; 
 int /*<<< orphan*/  PHM_PlatformCaps_PowerControl ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ThermalController ; 
 scalar_t__ VEGA12_ENGINECLOCK_HARDMAX ; 
 int append_vbios_pptable (struct pp_hwmgr*,int /*<<< orphan*/ *) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  phm_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phm_copy_clock_limits_array (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phm_copy_overdrive_settings_limits_array (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
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

	if (le32_to_cpu(powerplay_table->ODSettingsMax[ATOM_VEGA12_ODSETTING_GFXCLKFMAX]) > VEGA12_ENGINECLOCK_HARDMAX)
		hwmgr->platform_descriptor.overdriveLimit.engineClock = VEGA12_ENGINECLOCK_HARDMAX;
	else
		hwmgr->platform_descriptor.overdriveLimit.engineClock =
			le32_to_cpu(powerplay_table->ODSettingsMax[ATOM_VEGA12_ODSETTING_GFXCLKFMAX]);
	hwmgr->platform_descriptor.overdriveLimit.memoryClock =
		le32_to_cpu(powerplay_table->ODSettingsMax[ATOM_VEGA12_ODSETTING_UCLKFMAX]);

	phm_copy_overdrive_settings_limits_array(hwmgr,
						 &pptable_information->od_settings_max,
						 powerplay_table->ODSettingsMax,
						 ATOM_VEGA12_ODSETTING_COUNT);
	phm_copy_overdrive_settings_limits_array(hwmgr,
						 &pptable_information->od_settings_min,
						 powerplay_table->ODSettingsMin,
						 ATOM_VEGA12_ODSETTING_COUNT);

	/* hwmgr->platformDescriptor.minOverdriveVDDC = 0;
	hwmgr->platformDescriptor.maxOverdriveVDDC = 0;
	hwmgr->platformDescriptor.overdriveVDDCStep = 0; */

	if (hwmgr->platform_descriptor.overdriveLimit.engineClock > 0
		&& hwmgr->platform_descriptor.overdriveLimit.memoryClock > 0)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_ACOverdriveSupport);

	pptable_information->us_small_power_limit1 = le16_to_cpu(powerplay_table->usSmallPowerLimit1);
	pptable_information->us_small_power_limit2 = le16_to_cpu(powerplay_table->usSmallPowerLimit2);
	pptable_information->us_boost_power_limit = le16_to_cpu(powerplay_table->usBoostPowerLimit);
	pptable_information->us_od_turbo_power_limit = le16_to_cpu(powerplay_table->usODTurboPowerLimit);
	pptable_information->us_od_powersave_power_limit = le16_to_cpu(powerplay_table->usODPowerSavePowerLimit);

	pptable_information->us_software_shutdown_temp = le16_to_cpu(powerplay_table->usSoftwareShutdownTemp);

	hwmgr->platform_descriptor.TDPODLimit = le32_to_cpu(powerplay_table->ODSettingsMax[ATOM_VEGA12_ODSETTING_POWERPERCENTAGE]);

	disable_power_control = 0;
	if (!disable_power_control) {
		/* enable TDP overdrive (PowerControl) feature as well if supported */
		if (hwmgr->platform_descriptor.TDPODLimit)
			phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_PowerControl);
	}

	phm_copy_clock_limits_array(hwmgr, &pptable_information->power_saving_clock_max, powerplay_table->PowerSavingClockMax, ATOM_VEGA12_PPCLOCK_COUNT);
	phm_copy_clock_limits_array(hwmgr, &pptable_information->power_saving_clock_min, powerplay_table->PowerSavingClockMin, ATOM_VEGA12_PPCLOCK_COUNT);

	pptable_information->smc_pptable = (PPTable_t *)kmalloc(sizeof(PPTable_t), GFP_KERNEL);
	if (pptable_information->smc_pptable == NULL)
		return -ENOMEM;

	memcpy(pptable_information->smc_pptable, &(powerplay_table->smcPPTable), sizeof(PPTable_t));

	result = append_vbios_pptable(hwmgr, (pptable_information->smc_pptable));

	return result;
}