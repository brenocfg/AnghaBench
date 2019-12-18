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
typedef  scalar_t__ u8 ;
struct pwrctrl_priv {scalar_t__ cpwm; scalar_t__ rpwm; int /*<<< orphan*/  lock; int /*<<< orphan*/  alives; scalar_t__ bFwCurrentInPSMode; } ;
struct adapter {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ PS_STATE_S2 ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XMIT_ALIVE ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_rtl871x_pwrctrl_c_ ; 
 struct pwrctrl_priv* adapter_to_pwrctl (struct adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_task_alive (struct pwrctrl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_set_rpwm (struct adapter*,scalar_t__) ; 

s32 rtw_register_tx_alive(struct adapter *padapter)
{
	s32 res;
	struct pwrctrl_priv *pwrctrl;
	u8 pslv;

	res = _SUCCESS;
	pwrctrl = adapter_to_pwrctl(padapter);
	pslv = PS_STATE_S2;

	mutex_lock(&pwrctrl->lock);

	register_task_alive(pwrctrl, XMIT_ALIVE);

	if (pwrctrl->bFwCurrentInPSMode) {
		RT_TRACE(_module_rtl871x_pwrctrl_c_, _drv_notice_,
				 ("rtw_register_tx_alive: cpwm = 0x%02x alives = 0x%08x\n",
				  pwrctrl->cpwm, pwrctrl->alives));

		if (pwrctrl->cpwm < pslv) {
			if (pwrctrl->cpwm < PS_STATE_S2)
				res = _FAIL;
			if (pwrctrl->rpwm < pslv)
				rtw_set_rpwm(padapter, pslv);
		}
	}

	mutex_unlock(&pwrctrl->lock);

	if (_FAIL == res)
		if (pwrctrl->cpwm >= PS_STATE_S2)
			res = _SUCCESS;

	return res;
}