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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct eeprom_priv {int bautoload_fail_flag; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*,scalar_t__) ; 
 struct eeprom_priv* GET_EEPROM_EFUSE_PRIV (struct adapter*) ; 
 scalar_t__ RTL_EEPROM_ID ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_hal_init_c_ ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

void Hal_EfuseParseIDCode(struct adapter *padapter, u8 *hwinfo)
{
	struct eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);
/* 	struct hal_com_data	*pHalData = GET_HAL_DATA(padapter); */
	u16 EEPROMId;


	/*  Checl 0x8129 again for making sure autoload status!! */
	EEPROMId = le16_to_cpu(*((__le16 *)hwinfo));
	if (EEPROMId != RTL_EEPROM_ID) {
		DBG_8192C("EEPROM ID(%#x) is invalid!!\n", EEPROMId);
		pEEPROM->bautoload_fail_flag = true;
	} else
		pEEPROM->bautoload_fail_flag = false;

	RT_TRACE(_module_hal_init_c_, _drv_notice_, ("EEPROM ID = 0x%04x\n", EEPROMId));
}