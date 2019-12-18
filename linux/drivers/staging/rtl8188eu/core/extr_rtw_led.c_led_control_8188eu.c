#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ rf_pwrstate; scalar_t__ rfoff_reason; } ;
struct adapter {TYPE_1__ pwrctrlpriv; int /*<<< orphan*/  hw_init_completed; scalar_t__ bDriverStopped; scalar_t__ bSurpriseRemoved; } ;
typedef  enum LED_CTL_MODE { ____Placeholder_LED_CTL_MODE } LED_CTL_MODE ;

/* Variables and functions */
 int LED_CTL_LINK ; 
 int LED_CTL_NO_LINK ; 
 int LED_CTL_POWER_ON ; 
 int LED_CTL_RX ; 
 int LED_CTL_SITE_SURVEY ; 
 int LED_CTL_TX ; 
 scalar_t__ RF_CHANGE_BY_PS ; 
 int /*<<< orphan*/  SwLedControlMode1 (struct adapter*,int) ; 
 scalar_t__ rf_on ; 

void led_control_8188eu(struct adapter *padapter, enum LED_CTL_MODE LedAction)
{
	if (padapter->bSurpriseRemoved || padapter->bDriverStopped ||
	    !padapter->hw_init_completed)
		return;

	if ((padapter->pwrctrlpriv.rf_pwrstate != rf_on &&
	     padapter->pwrctrlpriv.rfoff_reason > RF_CHANGE_BY_PS) &&
	    (LedAction == LED_CTL_TX || LedAction == LED_CTL_RX ||
	     LedAction == LED_CTL_SITE_SURVEY ||
	     LedAction == LED_CTL_LINK ||
	     LedAction == LED_CTL_NO_LINK ||
	     LedAction == LED_CTL_POWER_ON))
		return;

	SwLedControlMode1(padapter, LedAction);
}