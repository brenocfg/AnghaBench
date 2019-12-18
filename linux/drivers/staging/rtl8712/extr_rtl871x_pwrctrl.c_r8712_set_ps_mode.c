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
typedef  scalar_t__ uint ;
struct pwrctrl_priv {scalar_t__ pwr_mode; scalar_t__ smart_ps; int bSleep; int /*<<< orphan*/  SetPSModeWorkItem; } ;
struct _adapter {struct pwrctrl_priv pwrctrlpriv; } ;

/* Variables and functions */
 scalar_t__ PM_Card_Disable ; 
 scalar_t__ PS_MODE_ACTIVE ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void r8712_set_ps_mode(struct _adapter *padapter, uint ps_mode, uint smart_ps)
{
	struct pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;

	if (ps_mode > PM_Card_Disable)
		return;
	/* if driver is in active state, we dont need set smart_ps.*/
	if (ps_mode == PS_MODE_ACTIVE)
		smart_ps = 0;
	if ((pwrpriv->pwr_mode != ps_mode) || (pwrpriv->smart_ps != smart_ps)) {
		if (pwrpriv->pwr_mode == PS_MODE_ACTIVE)
			pwrpriv->bSleep = true;
		else
			pwrpriv->bSleep = false;
		pwrpriv->pwr_mode = ps_mode;
		pwrpriv->smart_ps = smart_ps;
		schedule_work(&pwrpriv->SetPSModeWorkItem);
	}
}