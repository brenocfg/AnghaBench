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
struct hal_data_8188e {int CrystalCap; } ;
struct adapter {struct hal_data_8188e* HalData; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*,int) ; 
 void* EEPROM_Default_CrystalCap_88E ; 
 size_t EEPROM_XTAL_88E ; 

void Hal_EfuseParseXtal_8188E(struct adapter *pAdapter, u8 *hwinfo, bool AutoLoadFail)
{
	struct hal_data_8188e *pHalData = pAdapter->HalData;

	if (!AutoLoadFail) {
		pHalData->CrystalCap = hwinfo[EEPROM_XTAL_88E];
		if (pHalData->CrystalCap == 0xFF)
			pHalData->CrystalCap = EEPROM_Default_CrystalCap_88E;
	} else {
		pHalData->CrystalCap = EEPROM_Default_CrystalCap_88E;
	}
	DBG_88E("CrystalCap: 0x%2x\n", pHalData->CrystalCap);
}