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
struct pwrctrl_priv {scalar_t__ cpwm; scalar_t__ rpwm; int /*<<< orphan*/  rpwm_workitem; } ;
struct _adapter {scalar_t__ surprise_removed; scalar_t__ driver_stopped; struct pwrctrl_priv pwrctrlpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _rpwm_check_handler (struct _adapter *padapter)
{
	struct pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;

	if (padapter->driver_stopped || padapter->surprise_removed)
		return;
	if (pwrpriv->cpwm != pwrpriv->rpwm)
		schedule_work(&pwrpriv->rpwm_workitem);
}