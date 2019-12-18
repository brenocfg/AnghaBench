#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct vega20_od8_settings {TYPE_1__* od8_settings_array; } ;
struct smu_table_context {scalar_t__ overdrive_table; } ;
struct smu_context {scalar_t__ od_settings; struct smu_table_context smu_table; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_4__ {void* MaxOpTemp; void* FanTargetTemperature; void* FanMinimumPwm; void* FanMaximumRpm; int /*<<< orphan*/  OverDrivePct; void* UclkFmax; void* GfxclkVolt3; void* GfxclkFreq3; void* GfxclkVolt2; void* GfxclkFreq2; void* GfxclkVolt1; void* GfxclkFreq1; void* GfxclkFmax; void* GfxclkFmin; } ;
struct TYPE_3__ {int min_value; int max_value; } ;
typedef  TYPE_2__ OverDriveTable_t ;

/* Variables and functions */
 int EINVAL ; 
#define  OD8_SETTING_FAN_ACOUSTIC_LIMIT 141 
#define  OD8_SETTING_FAN_MIN_SPEED 140 
#define  OD8_SETTING_FAN_TARGET_TEMP 139 
#define  OD8_SETTING_GFXCLK_FMAX 138 
#define  OD8_SETTING_GFXCLK_FMIN 137 
#define  OD8_SETTING_GFXCLK_FREQ1 136 
#define  OD8_SETTING_GFXCLK_FREQ2 135 
#define  OD8_SETTING_GFXCLK_FREQ3 134 
#define  OD8_SETTING_GFXCLK_VOLTAGE1 133 
#define  OD8_SETTING_GFXCLK_VOLTAGE2 132 
#define  OD8_SETTING_GFXCLK_VOLTAGE3 131 
#define  OD8_SETTING_OPERATING_TEMP_MAX 130 
#define  OD8_SETTING_POWER_PERCENTAGE 129 
#define  OD8_SETTING_UCLK_FMAX 128 

__attribute__((used)) static int vega20_update_specified_od8_value(struct smu_context *smu,
					     uint32_t index,
					     uint32_t value)
{
	struct smu_table_context *table_context = &smu->smu_table;
	OverDriveTable_t *od_table =
		(OverDriveTable_t *)(table_context->overdrive_table);
	struct vega20_od8_settings *od8_settings =
		(struct vega20_od8_settings *)smu->od_settings;

	switch (index) {
	case OD8_SETTING_GFXCLK_FMIN:
		od_table->GfxclkFmin = (uint16_t)value;
		break;

	case OD8_SETTING_GFXCLK_FMAX:
		if (value < od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMAX].min_value ||
		    value > od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMAX].max_value)
			return -EINVAL;
		od_table->GfxclkFmax = (uint16_t)value;
		break;

	case OD8_SETTING_GFXCLK_FREQ1:
		od_table->GfxclkFreq1 = (uint16_t)value;
		break;

	case OD8_SETTING_GFXCLK_VOLTAGE1:
		od_table->GfxclkVolt1 = (uint16_t)value;
		break;

	case OD8_SETTING_GFXCLK_FREQ2:
		od_table->GfxclkFreq2 = (uint16_t)value;
		break;

	case OD8_SETTING_GFXCLK_VOLTAGE2:
		od_table->GfxclkVolt2 = (uint16_t)value;
		break;

	case OD8_SETTING_GFXCLK_FREQ3:
		od_table->GfxclkFreq3 = (uint16_t)value;
		break;

	case OD8_SETTING_GFXCLK_VOLTAGE3:
		od_table->GfxclkVolt3 = (uint16_t)value;
		break;

	case OD8_SETTING_UCLK_FMAX:
		if (value < od8_settings->od8_settings_array[OD8_SETTING_UCLK_FMAX].min_value ||
		    value > od8_settings->od8_settings_array[OD8_SETTING_UCLK_FMAX].max_value)
			return -EINVAL;
		od_table->UclkFmax = (uint16_t)value;
		break;

	case OD8_SETTING_POWER_PERCENTAGE:
		od_table->OverDrivePct = (int16_t)value;
		break;

	case OD8_SETTING_FAN_ACOUSTIC_LIMIT:
		od_table->FanMaximumRpm = (uint16_t)value;
		break;

	case OD8_SETTING_FAN_MIN_SPEED:
		od_table->FanMinimumPwm = (uint16_t)value;
		break;

	case OD8_SETTING_FAN_TARGET_TEMP:
		od_table->FanTargetTemperature = (uint16_t)value;
		break;

	case OD8_SETTING_OPERATING_TEMP_MAX:
		od_table->MaxOpTemp = (uint16_t)value;
		break;
	}

	return 0;
}