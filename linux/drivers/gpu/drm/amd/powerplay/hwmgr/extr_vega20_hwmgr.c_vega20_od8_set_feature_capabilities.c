#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vega20_od8_settings {int /*<<< orphan*/  overdrive8_capabilities; } ;
struct TYPE_9__ {int count; TYPE_2__* dpm_levels; } ;
struct TYPE_10__ {TYPE_3__ mem_table; } ;
struct TYPE_12__ {int MinVoltageGfx; int MaxVoltageGfx; int FanPwmMin; int FanMaximumRpm; scalar_t__ FanZeroRpmEnable; } ;
struct TYPE_7__ {TYPE_6__ pp_table; } ;
struct vega20_hwmgr {TYPE_5__* smu_features; TYPE_4__ dpm_table; struct vega20_od8_settings od8_settings; TYPE_1__ smc_state_table; } ;
struct pp_hwmgr {int od_enabled; scalar_t__ backend; scalar_t__ pptable; } ;
struct phm_ppt_v3_information {int* od_settings_max; int* od_settings_min; scalar_t__* od_feature_capabilities; } ;
struct TYPE_11__ {scalar_t__ enabled; } ;
struct TYPE_8__ {int value; } ;
typedef  TYPE_6__ PPTable_t ;

/* Variables and functions */
 size_t ATOM_VEGA20_ODFEATURE_FAN_ACOUSTIC_LIMIT ; 
 size_t ATOM_VEGA20_ODFEATURE_FAN_SPEED_MIN ; 
 size_t ATOM_VEGA20_ODFEATURE_FAN_ZERO_RPM_CONTROL ; 
 size_t ATOM_VEGA20_ODFEATURE_GFXCLK_CURVE ; 
 size_t ATOM_VEGA20_ODFEATURE_GFXCLK_LIMITS ; 
 size_t ATOM_VEGA20_ODFEATURE_MEMORY_TIMING_TUNE ; 
 size_t ATOM_VEGA20_ODFEATURE_POWER_LIMIT ; 
 size_t ATOM_VEGA20_ODFEATURE_TEMPERATURE_FAN ; 
 size_t ATOM_VEGA20_ODFEATURE_TEMPERATURE_SYSTEM ; 
 size_t ATOM_VEGA20_ODFEATURE_UCLK_MAX ; 
 size_t GNLD_DPM_GFXCLK ; 
 size_t GNLD_DPM_UCLK ; 
 size_t GNLD_FAN_CONTROL ; 
 size_t GNLD_THERMAL ; 
 int /*<<< orphan*/  OD8_ACOUSTIC_LIMIT_SCLK ; 
 int /*<<< orphan*/  OD8_FAN_SPEED_MIN ; 
 int /*<<< orphan*/  OD8_FAN_ZERO_RPM_CONTROL ; 
 int /*<<< orphan*/  OD8_GFXCLK_CURVE ; 
 int /*<<< orphan*/  OD8_GFXCLK_LIMITS ; 
 int /*<<< orphan*/  OD8_MEMORY_TIMING_TUNE ; 
 int /*<<< orphan*/  OD8_POWER_LIMIT ; 
 size_t OD8_SETTING_FAN_ACOUSTIC_LIMIT ; 
 size_t OD8_SETTING_FAN_MIN_SPEED ; 
 size_t OD8_SETTING_FAN_TARGET_TEMP ; 
 size_t OD8_SETTING_GFXCLK_FMAX ; 
 size_t OD8_SETTING_GFXCLK_FMIN ; 
 size_t OD8_SETTING_GFXCLK_VOLTAGE1 ; 
 size_t OD8_SETTING_GFXCLK_VOLTAGE3 ; 
 size_t OD8_SETTING_OPERATING_TEMP_MAX ; 
 size_t OD8_SETTING_POWER_PERCENTAGE ; 
 size_t OD8_SETTING_UCLK_FMAX ; 
 int /*<<< orphan*/  OD8_TEMPERATURE_FAN ; 
 int /*<<< orphan*/  OD8_TEMPERATURE_SYSTEM ; 
 int /*<<< orphan*/  OD8_UCLK_MAX ; 
 int VOLTAGE_SCALE ; 

__attribute__((used)) static int vega20_od8_set_feature_capabilities(
		struct pp_hwmgr *hwmgr)
{
	struct phm_ppt_v3_information *pptable_information =
		(struct phm_ppt_v3_information *)hwmgr->pptable;
	struct vega20_hwmgr *data = (struct vega20_hwmgr *)(hwmgr->backend);
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	struct vega20_od8_settings *od_settings = &(data->od8_settings);

	od_settings->overdrive8_capabilities = 0;

	if (data->smu_features[GNLD_DPM_GFXCLK].enabled) {
		if (pptable_information->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_GFXCLK_LIMITS] &&
		    pptable_information->od_settings_max[OD8_SETTING_GFXCLK_FMAX] > 0 &&
		    pptable_information->od_settings_min[OD8_SETTING_GFXCLK_FMIN] > 0 &&
		    (pptable_information->od_settings_max[OD8_SETTING_GFXCLK_FMAX] >=
		    pptable_information->od_settings_min[OD8_SETTING_GFXCLK_FMIN]))
			od_settings->overdrive8_capabilities |= OD8_GFXCLK_LIMITS;

		if (pptable_information->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_GFXCLK_CURVE] &&
		    (pptable_information->od_settings_min[OD8_SETTING_GFXCLK_VOLTAGE1] >=
		     pp_table->MinVoltageGfx / VOLTAGE_SCALE) &&
		    (pptable_information->od_settings_max[OD8_SETTING_GFXCLK_VOLTAGE3] <=
		     pp_table->MaxVoltageGfx / VOLTAGE_SCALE) &&
		    (pptable_information->od_settings_max[OD8_SETTING_GFXCLK_VOLTAGE3] >=
		     pptable_information->od_settings_min[OD8_SETTING_GFXCLK_VOLTAGE1]))
			od_settings->overdrive8_capabilities |= OD8_GFXCLK_CURVE;
	}

	if (data->smu_features[GNLD_DPM_UCLK].enabled) {
		pptable_information->od_settings_min[OD8_SETTING_UCLK_FMAX] =
			data->dpm_table.mem_table.dpm_levels[data->dpm_table.mem_table.count - 2].value;
		if (pptable_information->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_UCLK_MAX] &&
		    pptable_information->od_settings_min[OD8_SETTING_UCLK_FMAX] > 0 &&
		    pptable_information->od_settings_max[OD8_SETTING_UCLK_FMAX] > 0 &&
		    (pptable_information->od_settings_max[OD8_SETTING_UCLK_FMAX] >=
		    pptable_information->od_settings_min[OD8_SETTING_UCLK_FMAX]))
			od_settings->overdrive8_capabilities |= OD8_UCLK_MAX;
	}

	if (pptable_information->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_POWER_LIMIT] &&
	    pptable_information->od_settings_max[OD8_SETTING_POWER_PERCENTAGE] > 0 &&
	    pptable_information->od_settings_max[OD8_SETTING_POWER_PERCENTAGE] <= 100 &&
	    pptable_information->od_settings_min[OD8_SETTING_POWER_PERCENTAGE] > 0 &&
	    pptable_information->od_settings_min[OD8_SETTING_POWER_PERCENTAGE] <= 100)
		od_settings->overdrive8_capabilities |= OD8_POWER_LIMIT;

	if (data->smu_features[GNLD_FAN_CONTROL].enabled) {
		if (pptable_information->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_FAN_ACOUSTIC_LIMIT] &&
		    pptable_information->od_settings_min[OD8_SETTING_FAN_ACOUSTIC_LIMIT] > 0 &&
		    pptable_information->od_settings_max[OD8_SETTING_FAN_ACOUSTIC_LIMIT] > 0 &&
		    (pptable_information->od_settings_max[OD8_SETTING_FAN_ACOUSTIC_LIMIT] >=
		     pptable_information->od_settings_min[OD8_SETTING_FAN_ACOUSTIC_LIMIT]))
			od_settings->overdrive8_capabilities |= OD8_ACOUSTIC_LIMIT_SCLK;

		if (pptable_information->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_FAN_SPEED_MIN] &&
		    (pptable_information->od_settings_min[OD8_SETTING_FAN_MIN_SPEED] >=
		    (pp_table->FanPwmMin * pp_table->FanMaximumRpm / 100)) &&
		    pptable_information->od_settings_max[OD8_SETTING_FAN_MIN_SPEED] > 0 &&
		    (pptable_information->od_settings_max[OD8_SETTING_FAN_MIN_SPEED] >=
		     pptable_information->od_settings_min[OD8_SETTING_FAN_MIN_SPEED]))
			od_settings->overdrive8_capabilities |= OD8_FAN_SPEED_MIN;
	}

	if (data->smu_features[GNLD_THERMAL].enabled) {
		if (pptable_information->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_TEMPERATURE_FAN] &&
		    pptable_information->od_settings_max[OD8_SETTING_FAN_TARGET_TEMP] > 0 &&
		    pptable_information->od_settings_min[OD8_SETTING_FAN_TARGET_TEMP] > 0 &&
		    (pptable_information->od_settings_max[OD8_SETTING_FAN_TARGET_TEMP] >=
		     pptable_information->od_settings_min[OD8_SETTING_FAN_TARGET_TEMP]))
			od_settings->overdrive8_capabilities |= OD8_TEMPERATURE_FAN;

		if (pptable_information->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_TEMPERATURE_SYSTEM] &&
		    pptable_information->od_settings_max[OD8_SETTING_OPERATING_TEMP_MAX] > 0 &&
		    pptable_information->od_settings_min[OD8_SETTING_OPERATING_TEMP_MAX] > 0 &&
		    (pptable_information->od_settings_max[OD8_SETTING_OPERATING_TEMP_MAX] >=
		     pptable_information->od_settings_min[OD8_SETTING_OPERATING_TEMP_MAX]))
			od_settings->overdrive8_capabilities |= OD8_TEMPERATURE_SYSTEM;
	}

	if (pptable_information->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_MEMORY_TIMING_TUNE])
		od_settings->overdrive8_capabilities |= OD8_MEMORY_TIMING_TUNE;

	if (pptable_information->od_feature_capabilities[ATOM_VEGA20_ODFEATURE_FAN_ZERO_RPM_CONTROL] &&
	    pp_table->FanZeroRpmEnable)
		od_settings->overdrive8_capabilities |= OD8_FAN_ZERO_RPM_CONTROL;

	if (!od_settings->overdrive8_capabilities)
		hwmgr->od_enabled = false;

	return 0;
}