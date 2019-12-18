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
typedef  int u8 ;
struct mlme_priv {int dummy; } ;
struct TYPE_2__ {scalar_t__ rf_pwrstate; } ;
struct adapter {TYPE_1__ pwrctrlpriv; struct mlme_priv mlmepriv; } ;
struct LED_871x {scalar_t__ BlinkingLedState; int CurrLedState; int bLedLinkBlinkInProgress; int bLedNoLinkBlinkInProgress; int bLedScanBlinkInProgress; int bLedBlinkInProgress; int bLedWPSBlinkInProgress; int /*<<< orphan*/  BlinkTimer; int /*<<< orphan*/  bLedOn; int /*<<< orphan*/  BlinkTimes; struct adapter* padapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_BLINK_FASTER_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_LINK_INTERVAL_ALPHA ; 
#define  LED_BLINK_NORMAL 133 
 int /*<<< orphan*/  LED_BLINK_NO_LINK_INTERVAL_ALPHA ; 
#define  LED_BLINK_SCAN 132 
 int /*<<< orphan*/  LED_BLINK_SCAN_INTERVAL_ALPHA ; 
#define  LED_BLINK_SLOWLY 131 
#define  LED_BLINK_TXRX 130 
#define  LED_BLINK_WPS 129 
#define  LED_BLINK_WPS_STOP 128 
 int /*<<< orphan*/  LED_BLINK_WPS_SUCCESS_INTERVAL_ALPHA ; 
 void* RTW_LED_OFF ; 
 scalar_t__ RTW_LED_ON ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ResetLedStatus (struct LED_871x*) ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl8712_led_c_ ; 
 int /*<<< orphan*/  check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ rf_on ; 
 int /*<<< orphan*/  sw_led_off (struct adapter*,struct LED_871x*) ; 
 int /*<<< orphan*/  sw_led_on (struct adapter*,struct LED_871x*) ; 

__attribute__((used)) static void SwLedBlink1(struct LED_871x *pLed)
{
	struct adapter *padapter = pLed->padapter;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	u8 bStopBlinking = false;

	/*  Change LED according to BlinkingLedState specified. */
	if (pLed->BlinkingLedState == RTW_LED_ON) {
		sw_led_on(padapter, pLed);
		RT_TRACE(_module_rtl8712_led_c_, _drv_info_,
			 ("Blinktimes (%d): turn on\n", pLed->BlinkTimes));
	} else {
		sw_led_off(padapter, pLed);
		RT_TRACE(_module_rtl8712_led_c_, _drv_info_,
			 ("Blinktimes (%d): turn off\n", pLed->BlinkTimes));
	}

	if (padapter->pwrctrlpriv.rf_pwrstate != rf_on) {
		sw_led_off(padapter, pLed);
		ResetLedStatus(pLed);
		return;
	}

	switch (pLed->CurrLedState) {
	case LED_BLINK_SLOWLY:
		if (pLed->bLedOn)
			pLed->BlinkingLedState = RTW_LED_OFF;
		else
			pLed->BlinkingLedState = RTW_LED_ON;
		mod_timer(&pLed->BlinkTimer, jiffies +
			  msecs_to_jiffies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		break;
	case LED_BLINK_NORMAL:
		if (pLed->bLedOn)
			pLed->BlinkingLedState = RTW_LED_OFF;
		else
			pLed->BlinkingLedState = RTW_LED_ON;
		mod_timer(&pLed->BlinkTimer, jiffies +
			  msecs_to_jiffies(LED_BLINK_LINK_INTERVAL_ALPHA));
		break;
	case LED_BLINK_SCAN:
		pLed->BlinkTimes--;
		if (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		if (bStopBlinking) {
			if (check_fwstate(pmlmepriv, _FW_LINKED)) {
				pLed->bLedLinkBlinkInProgress = true;
				pLed->CurrLedState = LED_BLINK_NORMAL;
				if (pLed->bLedOn)
					pLed->BlinkingLedState = RTW_LED_OFF;
				else
					pLed->BlinkingLedState = RTW_LED_ON;
				mod_timer(&pLed->BlinkTimer, jiffies +
					  msecs_to_jiffies(LED_BLINK_LINK_INTERVAL_ALPHA));
				RT_TRACE(_module_rtl8712_led_c_, _drv_info_, ("CurrLedState %d\n", pLed->CurrLedState));
			} else if (!check_fwstate(pmlmepriv, _FW_LINKED)) {
				pLed->bLedNoLinkBlinkInProgress = true;
				pLed->CurrLedState = LED_BLINK_SLOWLY;
				if (pLed->bLedOn)
					pLed->BlinkingLedState = RTW_LED_OFF;
				else
					pLed->BlinkingLedState = RTW_LED_ON;
				mod_timer(&pLed->BlinkTimer, jiffies +
					  msecs_to_jiffies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
				RT_TRACE(_module_rtl8712_led_c_, _drv_info_, ("CurrLedState %d\n", pLed->CurrLedState));
			}
			pLed->bLedScanBlinkInProgress = false;
		} else {
			if (pLed->bLedOn)
				pLed->BlinkingLedState = RTW_LED_OFF;
			else
				pLed->BlinkingLedState = RTW_LED_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		}
		break;
	case LED_BLINK_TXRX:
		pLed->BlinkTimes--;
		if (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		if (bStopBlinking) {
			if (check_fwstate(pmlmepriv, _FW_LINKED)) {
				pLed->bLedLinkBlinkInProgress = true;
				pLed->CurrLedState = LED_BLINK_NORMAL;
				if (pLed->bLedOn)
					pLed->BlinkingLedState = RTW_LED_OFF;
				else
					pLed->BlinkingLedState = RTW_LED_ON;
				mod_timer(&pLed->BlinkTimer, jiffies +
					  msecs_to_jiffies(LED_BLINK_LINK_INTERVAL_ALPHA));
				RT_TRACE(_module_rtl8712_led_c_, _drv_info_, ("CurrLedState %d\n", pLed->CurrLedState));
			} else if (!check_fwstate(pmlmepriv, _FW_LINKED)) {
				pLed->bLedNoLinkBlinkInProgress = true;
				pLed->CurrLedState = LED_BLINK_SLOWLY;
				if (pLed->bLedOn)
					pLed->BlinkingLedState = RTW_LED_OFF;
				else
					pLed->BlinkingLedState = RTW_LED_ON;
				mod_timer(&pLed->BlinkTimer, jiffies +
					  msecs_to_jiffies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
				RT_TRACE(_module_rtl8712_led_c_, _drv_info_, ("CurrLedState %d\n", pLed->CurrLedState));
			}
			pLed->BlinkTimes = 0;
			pLed->bLedBlinkInProgress = false;
		} else {
			if (pLed->bLedOn)
				pLed->BlinkingLedState = RTW_LED_OFF;
			else
				pLed->BlinkingLedState = RTW_LED_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		}
		break;
	case LED_BLINK_WPS:
		if (pLed->bLedOn)
			pLed->BlinkingLedState = RTW_LED_OFF;
		else
			pLed->BlinkingLedState = RTW_LED_ON;
		mod_timer(&pLed->BlinkTimer, jiffies +
			  msecs_to_jiffies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		break;
	case LED_BLINK_WPS_STOP:	/* WPS success */
		if (pLed->BlinkingLedState == RTW_LED_ON)
			bStopBlinking = false;
		else
			bStopBlinking = true;

		if (bStopBlinking) {
			pLed->bLedLinkBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_NORMAL;
			if (pLed->bLedOn)
				pLed->BlinkingLedState = RTW_LED_OFF;
			else
				pLed->BlinkingLedState = RTW_LED_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_LINK_INTERVAL_ALPHA));
			RT_TRACE(_module_rtl8712_led_c_, _drv_info_, ("CurrLedState %d\n", pLed->CurrLedState));

			pLed->bLedWPSBlinkInProgress = false;
		} else {
			pLed->BlinkingLedState = RTW_LED_OFF;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_WPS_SUCCESS_INTERVAL_ALPHA));
		}
		break;
	default:
		break;
	}
}