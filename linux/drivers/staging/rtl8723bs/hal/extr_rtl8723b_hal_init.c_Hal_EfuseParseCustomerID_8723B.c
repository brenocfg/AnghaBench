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
typedef  scalar_t__ u8 ;
struct hal_com_data {scalar_t__ EEPROMCustomerID; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 size_t EEPROM_CustomID_8723B ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_hci_hal_init_c_ ; 

void Hal_EfuseParseCustomerID_8723B(
	struct adapter *padapter, u8 *hwinfo, bool AutoLoadFail
)
{
	struct hal_com_data	*pHalData = GET_HAL_DATA(padapter);

/* 	RT_TRACE(_module_hci_hal_init_c_, _drv_notice_, ("%s(): AutoLoadFail = %d\n", __func__, AutoLoadFail)); */
	if (!AutoLoadFail)
		pHalData->EEPROMCustomerID = hwinfo[EEPROM_CustomID_8723B];
	else
		pHalData->EEPROMCustomerID = 0;

	RT_TRACE(_module_hci_hal_init_c_, _drv_notice_, ("EEPROM Customer ID: 0x%2x\n", pHalData->EEPROMCustomerID));
}