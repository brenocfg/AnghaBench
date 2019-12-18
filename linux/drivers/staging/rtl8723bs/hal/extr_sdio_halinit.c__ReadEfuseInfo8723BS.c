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
struct eeprom_priv {int /*<<< orphan*/  bautoload_fail_flag; int /*<<< orphan*/ * efuse_eeprom_data; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 struct eeprom_priv* GET_EEPROM_EFUSE_PRIV (struct adapter*) ; 
 int HWSET_MAX_SIZE_8723B ; 
 int /*<<< orphan*/  Hal_DetectWoWMode (struct adapter*) ; 
 int /*<<< orphan*/  Hal_EfuseParseAntennaDiversity_8723B (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseBTCoexistInfo_8723B (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseBoardType_8723BS (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseChnlPlan_8723B (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseCustomerID_8723B (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseEEPROMVer_8723B (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseIDCode (struct adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Hal_EfuseParseMACAddr_8723BS (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParsePackageType_8723B (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseThermalMeter_8723B (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseTxPowerInfo_8723B (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseVoltage_8723B (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseXtal_8723B (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_InitPGData (struct adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Hal_ReadRFGainOffset (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_hci_hal_init_c_ ; 

__attribute__((used)) static void _ReadEfuseInfo8723BS(struct adapter *padapter)
{
	struct eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);
	u8 *hwinfo = NULL;

	RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("====>_ReadEfuseInfo8723BS()\n"));

	/*  */
	/*  This part read and parse the eeprom/efuse content */
	/*  */

	if (sizeof(pEEPROM->efuse_eeprom_data) < HWSET_MAX_SIZE_8723B)
		DBG_871X("[WARNING] size of efuse_eeprom_data is less than HWSET_MAX_SIZE_8723B!\n");

	hwinfo = pEEPROM->efuse_eeprom_data;

	Hal_InitPGData(padapter, hwinfo);

	Hal_EfuseParseIDCode(padapter, hwinfo);
	Hal_EfuseParseEEPROMVer_8723B(padapter, hwinfo, pEEPROM->bautoload_fail_flag);

	Hal_EfuseParseMACAddr_8723BS(padapter, hwinfo, pEEPROM->bautoload_fail_flag);

	Hal_EfuseParseTxPowerInfo_8723B(padapter, hwinfo, pEEPROM->bautoload_fail_flag);
	Hal_EfuseParseBoardType_8723BS(padapter, hwinfo, pEEPROM->bautoload_fail_flag);

	/*  */
	/*  Read Bluetooth co-exist and initialize */
	/*  */
	Hal_EfuseParsePackageType_8723B(padapter, hwinfo, pEEPROM->bautoload_fail_flag);
	Hal_EfuseParseBTCoexistInfo_8723B(padapter, hwinfo, pEEPROM->bautoload_fail_flag);
	Hal_EfuseParseChnlPlan_8723B(padapter, hwinfo, pEEPROM->bautoload_fail_flag);
	Hal_EfuseParseXtal_8723B(padapter, hwinfo, pEEPROM->bautoload_fail_flag);
	Hal_EfuseParseThermalMeter_8723B(padapter, hwinfo, pEEPROM->bautoload_fail_flag);
	Hal_EfuseParseAntennaDiversity_8723B(padapter, hwinfo, pEEPROM->bautoload_fail_flag);
	Hal_EfuseParseCustomerID_8723B(padapter, hwinfo, pEEPROM->bautoload_fail_flag);

	Hal_EfuseParseVoltage_8723B(padapter, hwinfo, pEEPROM->bautoload_fail_flag);

#ifdef CONFIG_WOWLAN
	Hal_DetectWoWMode(padapter);
#endif

	Hal_ReadRFGainOffset(padapter, hwinfo, pEEPROM->bautoload_fail_flag);

	RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("<==== _ReadEfuseInfo8723BS()\n"));
}