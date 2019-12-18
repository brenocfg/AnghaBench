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
struct TYPE_2__ {int /*<<< orphan*/  traffic_busy; } ;
struct mlme_priv {TYPE_1__ sitesurveyctrl; } ;
struct LED_871x {int bLedScanBlinkInProgress; int bLedBlinkInProgress; int BlinkTimes; int bLedWPSBlinkInProgress; int /*<<< orphan*/  BlinkTimer; void* BlinkingLedState; void* CurrLedState; int /*<<< orphan*/  bLedOn; } ;
struct led_priv {struct LED_871x SwLed0; } ;
struct _adapter {struct mlme_priv mlmepriv; struct led_priv ledpriv; } ;
typedef  enum LED_CTL_MODE { ____Placeholder_LED_CTL_MODE } LED_CTL_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  IS_LED_BLINKING (struct LED_871x*) ; 
 int /*<<< orphan*/  IS_LED_WPS_BLINKING (struct LED_871x*) ; 
 int /*<<< orphan*/  LED_BLINK_FASTER_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_SCAN_INTERVAL_ALPHA ; 
#define  LED_CTL_LINK 138 
#define  LED_CTL_NO_LINK 137 
#define  LED_CTL_POWER_OFF 136 
#define  LED_CTL_RX 135 
#define  LED_CTL_SITE_SURVEY 134 
#define  LED_CTL_START_TO_LINK 133 
#define  LED_CTL_START_WPS 132 
#define  LED_CTL_START_WPS_BOTTON 131 
#define  LED_CTL_STOP_WPS 130 
#define  LED_CTL_STOP_WPS_FAIL 129 
#define  LED_CTL_TX 128 
 void* LED_SCAN_BLINK ; 
 void* LED_STATE_OFF ; 
 void* LED_STATE_ON ; 
 void* LED_TXRX_BLINK ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SwLedControlMode2(struct _adapter *padapter,
			      enum LED_CTL_MODE LedAction)
{
	struct led_priv	 *ledpriv = &padapter->ledpriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct LED_871x *pLed = &ledpriv->SwLed0;

	switch (LedAction) {
	case LED_CTL_SITE_SURVEY:
		if (pmlmepriv->sitesurveyctrl.traffic_busy)
			; /* dummy branch */
		else if (!pLed->bLedScanBlinkInProgress) {
			if (IS_LED_WPS_BLINKING(pLed))
				return;

			if (pLed->bLedBlinkInProgress) {
				del_timer(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			}
			pLed->bLedScanBlinkInProgress = true;
			pLed->CurrLedState = LED_SCAN_BLINK;
			pLed->BlinkTimes = 24;
			if (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			else
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		}
		break;

	case LED_CTL_TX:
	case LED_CTL_RX:
		if (!pLed->bLedBlinkInProgress &&
		    check_fwstate(pmlmepriv, _FW_LINKED)) {
			if (pLed->CurrLedState == LED_SCAN_BLINK ||
			    IS_LED_WPS_BLINKING(pLed))
				return;
			pLed->bLedBlinkInProgress = true;
			pLed->CurrLedState = LED_TXRX_BLINK;
			pLed->BlinkTimes = 2;
			if (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			else
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		}
		break;

	case LED_CTL_LINK:
		pLed->CurrLedState = LED_STATE_ON;
		pLed->BlinkingLedState = LED_STATE_ON;
		if (pLed->bLedBlinkInProgress) {
			del_timer(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		}
		if (pLed->bLedScanBlinkInProgress) {
			del_timer(&pLed->BlinkTimer);
			pLed->bLedScanBlinkInProgress = false;
		}

		mod_timer(&pLed->BlinkTimer,
			  jiffies + msecs_to_jiffies(0));
		break;

	case LED_CTL_START_WPS: /*wait until xinpin finish*/
	case LED_CTL_START_WPS_BOTTON:
		if (!pLed->bLedWPSBlinkInProgress) {
			if (pLed->bLedBlinkInProgress) {
				del_timer(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			}
			if (pLed->bLedScanBlinkInProgress) {
				del_timer(&pLed->BlinkTimer);
				pLed->bLedScanBlinkInProgress = false;
			}
			pLed->bLedWPSBlinkInProgress = true;
			pLed->CurrLedState = LED_STATE_ON;
			pLed->BlinkingLedState = LED_STATE_ON;
			mod_timer(&pLed->BlinkTimer,
				  jiffies + msecs_to_jiffies(0));
		}
		break;

	case LED_CTL_STOP_WPS:
		pLed->bLedWPSBlinkInProgress = false;
		pLed->CurrLedState = LED_STATE_ON;
		pLed->BlinkingLedState = LED_STATE_ON;
		mod_timer(&pLed->BlinkTimer,
			  jiffies + msecs_to_jiffies(0));
		break;

	case LED_CTL_STOP_WPS_FAIL:
		pLed->bLedWPSBlinkInProgress = false;
		pLed->CurrLedState = LED_STATE_OFF;
		pLed->BlinkingLedState = LED_STATE_OFF;
		mod_timer(&pLed->BlinkTimer,
			  jiffies + msecs_to_jiffies(0));
		break;

	case LED_CTL_START_TO_LINK:
	case LED_CTL_NO_LINK:
		if (!IS_LED_BLINKING(pLed)) {
			pLed->CurrLedState = LED_STATE_OFF;
			pLed->BlinkingLedState = LED_STATE_OFF;
			mod_timer(&pLed->BlinkTimer,
				  jiffies + msecs_to_jiffies(0));
		}
		break;
	case LED_CTL_POWER_OFF:
		pLed->CurrLedState = LED_STATE_OFF;
		pLed->BlinkingLedState = LED_STATE_OFF;
		if (pLed->bLedBlinkInProgress) {
			del_timer(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		}
		if (pLed->bLedScanBlinkInProgress) {
			del_timer(&pLed->BlinkTimer);
			pLed->bLedScanBlinkInProgress = false;
		}
		if (pLed->bLedWPSBlinkInProgress) {
			del_timer(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		}
		mod_timer(&pLed->BlinkTimer,
			  jiffies + msecs_to_jiffies(0));
		break;
	default:
		break;
	}
}