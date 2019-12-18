#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vega20_od8_settings {int overdrive8_capabilities; TYPE_1__* od8_settings_array; } ;
struct vega20_hwmgr {struct vega20_od8_settings od8_settings; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct TYPE_2__ {int feature_id; } ;

/* Variables and functions */
 int OD8_ACOUSTIC_LIMIT_SCLK ; 
 int OD8_FAN_SPEED_MIN ; 
 int OD8_GFXCLK_CURVE ; 
 int OD8_GFXCLK_LIMITS ; 
 int OD8_POWER_LIMIT ; 
 size_t OD8_SETTING_FAN_ACOUSTIC_LIMIT ; 
 size_t OD8_SETTING_FAN_MIN_SPEED ; 
 size_t OD8_SETTING_FAN_TARGET_TEMP ; 
 size_t OD8_SETTING_GFXCLK_FMAX ; 
 size_t OD8_SETTING_GFXCLK_FMIN ; 
 size_t OD8_SETTING_GFXCLK_FREQ1 ; 
 size_t OD8_SETTING_GFXCLK_FREQ2 ; 
 size_t OD8_SETTING_GFXCLK_FREQ3 ; 
 size_t OD8_SETTING_GFXCLK_VOLTAGE1 ; 
 size_t OD8_SETTING_GFXCLK_VOLTAGE2 ; 
 size_t OD8_SETTING_GFXCLK_VOLTAGE3 ; 
 size_t OD8_SETTING_OPERATING_TEMP_MAX ; 
 size_t OD8_SETTING_POWER_PERCENTAGE ; 
 size_t OD8_SETTING_UCLK_FMAX ; 
 int OD8_TEMPERATURE_FAN ; 
 int OD8_TEMPERATURE_SYSTEM ; 
 int OD8_UCLK_MAX ; 

__attribute__((used)) static int vega20_od8_set_feature_id(
		struct pp_hwmgr *hwmgr)
{
	struct vega20_hwmgr *data = (struct vega20_hwmgr *)(hwmgr->backend);
	struct vega20_od8_settings *od_settings = &(data->od8_settings);

	if (od_settings->overdrive8_capabilities & OD8_GFXCLK_LIMITS) {
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMIN].feature_id =
			OD8_GFXCLK_LIMITS;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMAX].feature_id =
			OD8_GFXCLK_LIMITS;
	} else {
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMIN].feature_id =
			0;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMAX].feature_id =
			0;
	}

	if (od_settings->overdrive8_capabilities & OD8_GFXCLK_CURVE) {
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ1].feature_id =
			OD8_GFXCLK_CURVE;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE1].feature_id =
			OD8_GFXCLK_CURVE;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ2].feature_id =
			OD8_GFXCLK_CURVE;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE2].feature_id =
			OD8_GFXCLK_CURVE;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ3].feature_id =
			OD8_GFXCLK_CURVE;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE3].feature_id =
			OD8_GFXCLK_CURVE;
	} else {
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ1].feature_id =
			0;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE1].feature_id =
			0;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ2].feature_id =
			0;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE2].feature_id =
			0;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ3].feature_id =
			0;
		od_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE3].feature_id =
			0;
	}

	if (od_settings->overdrive8_capabilities & OD8_UCLK_MAX)
		od_settings->od8_settings_array[OD8_SETTING_UCLK_FMAX].feature_id = OD8_UCLK_MAX;
	else
		od_settings->od8_settings_array[OD8_SETTING_UCLK_FMAX].feature_id = 0;

	if (od_settings->overdrive8_capabilities & OD8_POWER_LIMIT)
		od_settings->od8_settings_array[OD8_SETTING_POWER_PERCENTAGE].feature_id = OD8_POWER_LIMIT;
	else
		od_settings->od8_settings_array[OD8_SETTING_POWER_PERCENTAGE].feature_id = 0;

	if (od_settings->overdrive8_capabilities & OD8_ACOUSTIC_LIMIT_SCLK)
		od_settings->od8_settings_array[OD8_SETTING_FAN_ACOUSTIC_LIMIT].feature_id =
			OD8_ACOUSTIC_LIMIT_SCLK;
	else
		od_settings->od8_settings_array[OD8_SETTING_FAN_ACOUSTIC_LIMIT].feature_id =
			0;

	if (od_settings->overdrive8_capabilities & OD8_FAN_SPEED_MIN)
		od_settings->od8_settings_array[OD8_SETTING_FAN_MIN_SPEED].feature_id =
			OD8_FAN_SPEED_MIN;
	else
		od_settings->od8_settings_array[OD8_SETTING_FAN_MIN_SPEED].feature_id =
			0;

	if (od_settings->overdrive8_capabilities & OD8_TEMPERATURE_FAN)
		od_settings->od8_settings_array[OD8_SETTING_FAN_TARGET_TEMP].feature_id =
			OD8_TEMPERATURE_FAN;
	else
		od_settings->od8_settings_array[OD8_SETTING_FAN_TARGET_TEMP].feature_id =
			0;

	if (od_settings->overdrive8_capabilities & OD8_TEMPERATURE_SYSTEM)
		od_settings->od8_settings_array[OD8_SETTING_OPERATING_TEMP_MAX].feature_id =
			OD8_TEMPERATURE_SYSTEM;
	else
		od_settings->od8_settings_array[OD8_SETTING_OPERATING_TEMP_MAX].feature_id =
			0;

	return 0;
}