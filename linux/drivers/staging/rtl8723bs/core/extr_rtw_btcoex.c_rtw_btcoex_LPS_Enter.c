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
struct pwrctrl_priv {int bpower_saving; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS_MODE_MIN ; 
 struct pwrctrl_priv* adapter_to_pwrctl (struct adapter*) ; 
 int /*<<< orphan*/  hal_btcoex_LpsVal (struct adapter*) ; 
 int /*<<< orphan*/  rtw_set_ps_mode (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void rtw_btcoex_LPS_Enter(struct adapter *padapter)
{
	struct pwrctrl_priv *pwrpriv;
	u8 lpsVal;


	pwrpriv = adapter_to_pwrctl(padapter);

	pwrpriv->bpower_saving = true;
	lpsVal = hal_btcoex_LpsVal(padapter);
	rtw_set_ps_mode(padapter, PS_MODE_MIN, 0, lpsVal, "BTCOEX");
}