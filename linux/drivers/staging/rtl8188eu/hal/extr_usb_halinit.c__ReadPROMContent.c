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
struct eeprom_priv {int EepromOrEfuse; int bautoload_fail_flag; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int BOOT_FROM_EEPROM ; 
 int /*<<< orphan*/  DBG_88E (char*,char*,char*) ; 
 int EEPROM_EN ; 
 struct eeprom_priv* GET_EEPROM_EFUSE_PRIV (struct adapter*) ; 
 int /*<<< orphan*/  Hal_InitPGData88E (struct adapter*) ; 
 int /*<<< orphan*/  REG_9346CR ; 
 int /*<<< orphan*/  readAdapterInfo_8188EU (struct adapter*) ; 
 int usb_read8 (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ReadPROMContent(struct adapter *Adapter)
{
	struct eeprom_priv *eeprom = GET_EEPROM_EFUSE_PRIV(Adapter);
	u8 eeValue;

	/* check system boot selection */
	eeValue = usb_read8(Adapter, REG_9346CR);
	eeprom->EepromOrEfuse		= (eeValue & BOOT_FROM_EEPROM) ? true : false;
	eeprom->bautoload_fail_flag	= (eeValue & EEPROM_EN) ? false : true;

	DBG_88E("Boot from %s, Autoload %s !\n", (eeprom->EepromOrEfuse ? "EEPROM" : "EFUSE"),
		(eeprom->bautoload_fail_flag ? "Fail" : "OK"));

	Hal_InitPGData88E(Adapter);
	readAdapterInfo_8188EU(Adapter);
}