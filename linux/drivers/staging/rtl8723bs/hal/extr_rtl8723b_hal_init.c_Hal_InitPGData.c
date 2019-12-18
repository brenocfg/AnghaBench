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
struct eeprom_priv {scalar_t__ efuse_eeprom_data; int /*<<< orphan*/  EepromOrEfuse; int /*<<< orphan*/  bautoload_fail_flag; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_ShadowMapUpdate (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EFUSE_WIFI ; 
 struct eeprom_priv* GET_EEPROM_EFUSE_PRIV (struct adapter*) ; 
 int /*<<< orphan*/  HWSET_MAX_SIZE_8723B ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_hci_hal_init_c_ ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

void Hal_InitPGData(struct adapter *padapter, u8 *PROMContent)
{
	struct eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);

	if (!pEEPROM->bautoload_fail_flag) { /*  autoload OK. */
		if (!pEEPROM->EepromOrEfuse) {
			/*  Read EFUSE real map to shadow. */
			EFUSE_ShadowMapUpdate(padapter, EFUSE_WIFI, false);
			memcpy((void *)PROMContent, (void *)pEEPROM->efuse_eeprom_data, HWSET_MAX_SIZE_8723B);
		}
	} else {/* autoload fail */
		RT_TRACE(_module_hci_hal_init_c_, _drv_notice_, ("AutoLoad Fail reported from CR9346!!\n"));
		if (!pEEPROM->EepromOrEfuse)
			EFUSE_ShadowMapUpdate(padapter, EFUSE_WIFI, false);
		memcpy((void *)PROMContent, (void *)pEEPROM->efuse_eeprom_data, HWSET_MAX_SIZE_8723B);
	}
}