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
struct eeprom_priv {int /*<<< orphan*/  efuse_eeprom_data; scalar_t__ bautoload_fail_flag; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_MAP_LEN_88E ; 
 int /*<<< orphan*/  Efuse_ReadAllMap (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct eeprom_priv* GET_EEPROM_EFUSE_PRIV (struct adapter*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void EFUSE_ShadowMapUpdate(struct adapter *pAdapter, u8 efuseType)
{
	struct eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(pAdapter);

	if (pEEPROM->bautoload_fail_flag)
		memset(pEEPROM->efuse_eeprom_data, 0xFF, EFUSE_MAP_LEN_88E);
	else
		Efuse_ReadAllMap(pAdapter, efuseType, pEEPROM->efuse_eeprom_data);
}