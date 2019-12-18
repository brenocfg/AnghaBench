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
struct hal_com_data {int EEPROMThermalMeter; int bAPKThermalMeterIgnore; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 void* EEPROM_Default_ThermalMeter_8723B ; 
 size_t EEPROM_THERMAL_METER_8723B ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_hci_hal_init_c_ ; 

void Hal_EfuseParseThermalMeter_8723B(
	struct adapter *padapter, u8 *PROMContent, u8 AutoLoadFail
)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(padapter);

/* 	RT_TRACE(_module_hci_hal_init_c_, _drv_notice_, ("%s(): AutoLoadFail = %d\n", __func__, AutoLoadFail)); */
	/*  */
	/*  ThermalMeter from EEPROM */
	/*  */
	if (!AutoLoadFail)
		pHalData->EEPROMThermalMeter = PROMContent[EEPROM_THERMAL_METER_8723B];
	else
		pHalData->EEPROMThermalMeter = EEPROM_Default_ThermalMeter_8723B;

	if ((pHalData->EEPROMThermalMeter == 0xff) || AutoLoadFail) {
		pHalData->bAPKThermalMeterIgnore = true;
		pHalData->EEPROMThermalMeter = EEPROM_Default_ThermalMeter_8723B;
	}

	RT_TRACE(_module_hci_hal_init_c_, _drv_notice_, ("EEPROM ThermalMeter = 0x%x\n", pHalData->EEPROMThermalMeter));
}