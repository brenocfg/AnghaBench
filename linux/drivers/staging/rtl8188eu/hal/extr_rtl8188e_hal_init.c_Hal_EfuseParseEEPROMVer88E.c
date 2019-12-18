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
struct hal_data_8188e {int EEPROMVersion; } ;
struct adapter {struct hal_data_8188e* HalData; } ;

/* Variables and functions */
 int EEPROM_Default_Version ; 
 size_t EEPROM_VERSION_88E ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_hci_hal_init_c_ ; 

void Hal_EfuseParseEEPROMVer88E(struct adapter *padapter, u8 *hwinfo, bool AutoLoadFail)
{
	struct hal_data_8188e *pHalData = padapter->HalData;

	if (!AutoLoadFail) {
		pHalData->EEPROMVersion = hwinfo[EEPROM_VERSION_88E];
		if (pHalData->EEPROMVersion == 0xFF)
			pHalData->EEPROMVersion = EEPROM_Default_Version;
	} else {
		pHalData->EEPROMVersion = 1;
	}
	RT_TRACE(_module_hci_hal_init_c_, _drv_info_,
		 ("Hal_EfuseParseEEPROMVer(), EEVer = %d\n",
		 pHalData->EEPROMVersion));
}