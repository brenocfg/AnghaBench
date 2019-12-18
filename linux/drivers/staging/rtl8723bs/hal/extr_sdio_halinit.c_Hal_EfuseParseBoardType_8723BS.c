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
struct hal_com_data {int BoardType; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int EEPROM_DEFAULT_BOARD_OPTION ; 
 size_t EEPROM_RF_BOARD_OPTION_8723B ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_hci_hal_init_c_ ; 

__attribute__((used)) static void Hal_EfuseParseBoardType_8723BS(
	struct adapter *padapter, u8 *hwinfo, bool AutoLoadFail
)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(padapter);

	if (!AutoLoadFail) {
		pHalData->BoardType = (hwinfo[EEPROM_RF_BOARD_OPTION_8723B] & 0xE0) >> 5;
		if (pHalData->BoardType == 0xFF)
			pHalData->BoardType = (EEPROM_DEFAULT_BOARD_OPTION & 0xE0) >> 5;
	} else
		pHalData->BoardType = 0;
	RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("Board Type: 0x%2x\n", pHalData->BoardType));
}