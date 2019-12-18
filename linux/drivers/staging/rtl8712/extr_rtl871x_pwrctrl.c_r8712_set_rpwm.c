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
struct pwrctrl_priv {int rpwm; scalar_t__ rpwm_retry; int tog; int cpwm; } ;
struct _adapter {scalar_t__ surprise_removed; scalar_t__ driver_stopped; struct pwrctrl_priv pwrctrlpriv; } ;

/* Variables and functions */
#define  PS_STATE_S1 131 
#define  PS_STATE_S2 130 
#define  PS_STATE_S3 129 
#define  PS_STATE_S4 128 
 int /*<<< orphan*/  r8712_write8 (struct _adapter*,int,int) ; 

void r8712_set_rpwm(struct _adapter *padapter, u8 val8)
{
	u8	rpwm;
	struct pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;

	if (pwrpriv->rpwm == val8) {
		if (pwrpriv->rpwm_retry == 0)
			return;
	}
	if (padapter->driver_stopped || padapter->surprise_removed)
		return;
	rpwm = val8 | pwrpriv->tog;
	switch (val8) {
	case PS_STATE_S1:
		pwrpriv->cpwm = val8;
		break;
	case PS_STATE_S2:/* only for USB normal powersave mode use,
			  * temp mark some code.
			  */
	case PS_STATE_S3:
	case PS_STATE_S4:
		pwrpriv->cpwm = val8;
		break;
	default:
		break;
	}
	pwrpriv->rpwm_retry = 0;
	pwrpriv->rpwm = val8;
	r8712_write8(padapter, 0x1025FE58, rpwm);
	pwrpriv->tog += 0x80;
}