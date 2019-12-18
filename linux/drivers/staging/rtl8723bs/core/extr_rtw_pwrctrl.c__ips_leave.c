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
struct pwrctrl_priv {scalar_t__ rf_pwrstate; int bips_processing; int bkeepfwalive; int bpower_saving; int /*<<< orphan*/  ips_leave_cnts; void* change_rfpwrstate; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 int _SUCCESS ; 
 struct pwrctrl_priv* adapter_to_pwrctl (struct adapter*) ; 
 scalar_t__ rf_off ; 
 void* rf_on ; 
 int rtw_ips_pwr_up (struct adapter*) ; 
 int /*<<< orphan*/  rtw_read32 (struct adapter*,int) ; 

int _ips_leave(struct adapter *padapter)
{
	struct pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
	int result = _SUCCESS;

	if ((pwrpriv->rf_pwrstate == rf_off) && (!pwrpriv->bips_processing)) {
		pwrpriv->bips_processing = true;
		pwrpriv->change_rfpwrstate = rf_on;
		pwrpriv->ips_leave_cnts++;
		DBG_871X("==>ips_leave cnts:%d\n", pwrpriv->ips_leave_cnts);

		result = rtw_ips_pwr_up(padapter);
		if (result == _SUCCESS) {
			pwrpriv->rf_pwrstate = rf_on;
		}
		DBG_871X("nolinked power save leave\n");

		DBG_871X("==> ips_leave.....LED(0x%08x)...\n", rtw_read32(padapter, 0x4c));
		pwrpriv->bips_processing = false;

		pwrpriv->bkeepfwalive = false;
		pwrpriv->bpower_saving = false;
	}

	return result;
}