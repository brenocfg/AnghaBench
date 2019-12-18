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
struct eeprom_priv {int /*<<< orphan*/  bautoload_fail_flag; int /*<<< orphan*/  efuse_eeprom_data; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct eeprom_priv* GET_EEPROM_EFUSE_PRIV (struct adapter*) ; 
 int /*<<< orphan*/  Hal_EfuseParseBoardType88E (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseCustomerID88E (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseEEPROMVer88E (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseIDCode88E (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseMACAddr_8188EU (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParsePIDVID_8188EU (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_EfuseParseXtal_8188E (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_ReadAntennaDiversity88E (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_ReadPowerSavingMode88E (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_ReadThermalMeter_88E (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hal_ReadTxPowerInfo88E (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8188e_EfuseParseChnlPlan (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void readAdapterInfo_8188EU(struct adapter *adapt)
{
	struct eeprom_priv *eeprom = GET_EEPROM_EFUSE_PRIV(adapt);

	/* parse the eeprom/efuse content */
	Hal_EfuseParseIDCode88E(adapt, eeprom->efuse_eeprom_data);
	Hal_EfuseParsePIDVID_8188EU(adapt, eeprom->efuse_eeprom_data, eeprom->bautoload_fail_flag);
	Hal_EfuseParseMACAddr_8188EU(adapt, eeprom->efuse_eeprom_data, eeprom->bautoload_fail_flag);

	Hal_ReadPowerSavingMode88E(adapt, eeprom->efuse_eeprom_data, eeprom->bautoload_fail_flag);
	Hal_ReadTxPowerInfo88E(adapt, eeprom->efuse_eeprom_data, eeprom->bautoload_fail_flag);
	Hal_EfuseParseEEPROMVer88E(adapt, eeprom->efuse_eeprom_data, eeprom->bautoload_fail_flag);
	rtl8188e_EfuseParseChnlPlan(adapt, eeprom->efuse_eeprom_data, eeprom->bautoload_fail_flag);
	Hal_EfuseParseXtal_8188E(adapt, eeprom->efuse_eeprom_data, eeprom->bautoload_fail_flag);
	Hal_EfuseParseCustomerID88E(adapt, eeprom->efuse_eeprom_data, eeprom->bautoload_fail_flag);
	Hal_ReadAntennaDiversity88E(adapt, eeprom->efuse_eeprom_data, eeprom->bautoload_fail_flag);
	Hal_EfuseParseBoardType88E(adapt, eeprom->efuse_eeprom_data, eeprom->bautoload_fail_flag);
	Hal_ReadThermalMeter_88E(adapt, eeprom->efuse_eeprom_data, eeprom->bautoload_fail_flag);
}