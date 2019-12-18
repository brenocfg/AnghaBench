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
struct pwrctrl_priv {scalar_t__ pwr_mode; int bpower_saving; scalar_t__ bLeisurePs; } ;
struct dvobj_priv {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPS_LEAVE_TIMEOUT_MS ; 
 int /*<<< orphan*/  LPS_RF_ON_check (struct adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ PS_MODE_ACTIVE ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 struct pwrctrl_priv* dvobj_to_pwrctl (struct dvobj_priv*) ; 
 scalar_t__ hal_btcoex_IsBtControlLps (struct adapter*) ; 
 int /*<<< orphan*/  rtw_set_ps_mode (struct adapter*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

void LPS_Leave(struct adapter *padapter, const char *msg)
{
#define LPS_LEAVE_TIMEOUT_MS 100

	struct dvobj_priv *dvobj = adapter_to_dvobj(padapter);
	struct pwrctrl_priv *pwrpriv = dvobj_to_pwrctl(dvobj);
	char buf[32] = {0};

/* 	DBG_871X("+LeisurePSLeave\n"); */

	if (hal_btcoex_IsBtControlLps(padapter))
		return;

	if (pwrpriv->bLeisurePs) {
		if (pwrpriv->pwr_mode != PS_MODE_ACTIVE) {
			sprintf(buf, "WIFI-%s", msg);
			rtw_set_ps_mode(padapter, PS_MODE_ACTIVE, 0, 0, buf);

			if (pwrpriv->pwr_mode == PS_MODE_ACTIVE)
				LPS_RF_ON_check(padapter, LPS_LEAVE_TIMEOUT_MS);
		}
	}

	pwrpriv->bpower_saving = false;
/* 	DBG_871X("-LeisurePSLeave\n"); */

}