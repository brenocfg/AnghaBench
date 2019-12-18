#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct hal_data_8188e {int EEPROMThermalMeter; int bAPKThermalMeterIgnore; } ;
struct adapter {struct hal_data_8188e* HalData; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*,int) ; 
 void* EEPROM_Default_ThermalMeter_88E ; 
 size_t EEPROM_THERMAL_METER_88E ; 

void Hal_ReadThermalMeter_88E(struct adapter *Adapter, u8 *PROMContent, bool AutoloadFail)
{
	struct hal_data_8188e *pHalData = Adapter->HalData;

	/*  ThermalMeter from EEPROM */
	if (!AutoloadFail)
		pHalData->EEPROMThermalMeter = PROMContent[EEPROM_THERMAL_METER_88E];
	else
		pHalData->EEPROMThermalMeter = EEPROM_Default_ThermalMeter_88E;

	if (pHalData->EEPROMThermalMeter == 0xff || AutoloadFail) {
		pHalData->bAPKThermalMeterIgnore = true;
		pHalData->EEPROMThermalMeter = EEPROM_Default_ThermalMeter_88E;
	}
	DBG_88E("ThermalMeter = 0x%x\n", pHalData->EEPROMThermalMeter);
}