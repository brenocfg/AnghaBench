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
typedef  int /*<<< orphan*/  u32 ;
struct pwrctrl_priv {scalar_t__ reg_pdnmode; } ;
struct hal_com_data {int pwrdown; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int BIT4 ; 
 int /*<<< orphan*/  DBG_8192C (char*,int) ; 
 int /*<<< orphan*/  EFUSE_ShadowRead (struct adapter*,int,int,int /*<<< orphan*/ *) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 struct pwrctrl_priv* adapter_to_pwrctl (struct adapter*) ; 

__attribute__((used)) static bool HalDetectPwrDownMode(struct adapter *Adapter)
{
	u8 tmpvalue;
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	struct pwrctrl_priv *pwrctrlpriv = adapter_to_pwrctl(Adapter);


	EFUSE_ShadowRead(Adapter, 1, 0x7B/*EEPROM_RF_OPT3_92C*/, (u32 *)&tmpvalue);

	/*  2010/08/25 MH INF priority > PDN Efuse value. */
	if (tmpvalue & BIT4 && pwrctrlpriv->reg_pdnmode)
		pHalData->pwrdown = true;
	else
		pHalData->pwrdown = false;

	DBG_8192C("HalDetectPwrDownMode(): PDN =%d\n", pHalData->pwrdown);

	return pHalData->pwrdown;
}