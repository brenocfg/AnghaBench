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
struct LED_871x {int bLedWPSBlinkInProgress; int bLedStartToLinkBlinkInProgress; int bLedBlinkInProgress; int bLedNoLinkBlinkInProgress; int bLedScanBlinkInProgress; int BlinkTimes; int bLedLinkBlinkInProgress; void* BlinkingLedState; int /*<<< orphan*/  BlinkTimer; void* CurrLedState; int /*<<< orphan*/  bLedOn; } ;
struct led_priv {struct LED_871x SwLed1; struct LED_871x SwLed0; } ;
struct _adapter {struct mlme_priv mlmepriv; struct led_priv ledpriv; } ;
typedef  enum LED_CTL_MODE { ____Placeholder_LED_CTL_MODE } LED_CTL_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  IS_LED_WPS_BLINKING (struct LED_871x*) ; 
 int /*<<< orphan*/  LED_BLINK_FASTER_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_NORMAL_INTERVAL ; 
 int /*<<< orphan*/  LED_BLINK_NO_LINK_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_SCAN_INTERVAL_ALPHA ; 
 void* LED_BLINK_SLOWLY ; 
 int /*<<< orphan*/  LED_BLINK_SLOWLY_INTERVAL ; 
 void* LED_BLINK_StartToBlink ; 
 void* LED_BLINK_WPS ; 
 void* LED_BLINK_WPS_STOP ; 
 void* LED_BLINK_WPS_STOP_OVERLAP ; 
#define  LED_CTL_LINK 139 
#define  LED_CTL_NO_LINK 138 
#define  LED_CTL_POWER_OFF 137 
#define  LED_CTL_RX 136 
#define  LED_CTL_SITE_SURVEY 135 
#define  LED_CTL_START_TO_LINK 134 
#define  LED_CTL_START_WPS 133 
#define  LED_CTL_START_WPS_BOTTON 132 
#define  LED_CTL_STOP_WPS 131 
#define  LED_CTL_STOP_WPS_FAIL 130 
#define  LED_CTL_STOP_WPS_FAIL_OVERLAP 129 
#define  LED_CTL_TX 128 
 void* LED_SCAN_BLINK ; 
 void* LED_STATE_OFF ; 
 void* LED_STATE_ON ; 
 void* LED_TXRX_BLINK ; 
 void* LED_UNKNOWN ; 
 int /*<<< orphan*/  SwLedOff (struct _adapter*,struct LED_871x*) ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SwLedControlMode4(struct _adapter *padapter,
			      enum LED_CTL_MODE LedAction)
{
	struct led_priv	*ledpriv = &padapter->ledpriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct LED_871x *pLed = &ledpriv->SwLed0;
	struct LED_871x *pLed1 = &ledpriv->SwLed1;

	switch (LedAction) {
	case LED_CTL_START_TO_LINK:
		if (pLed1->bLedWPSBlinkInProgress) {
			pLed1->bLedWPSBlinkInProgress = false;
			del_timer(&pLed1->BlinkTimer);
			pLed1->BlinkingLedState = LED_STATE_OFF;
			pLed1->CurrLedState = LED_STATE_OFF;
			if (pLed1->bLedOn)
				mod_timer(&pLed->BlinkTimer,
					  jiffies + msecs_to_jiffies(0));
		}
		if (!pLed->bLedStartToLinkBlinkInProgress) {
			if (pLed->CurrLedState == LED_SCAN_BLINK ||
			    IS_LED_WPS_BLINKING(pLed))
				return;
			if (pLed->bLedBlinkInProgress) {
				del_timer(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			}
			if (pLed->bLedNoLinkBlinkInProgress) {
				del_timer(&pLed->BlinkTimer);
				pLed->bLedNoLinkBlinkInProgress = false;
			}
			pLed->bLedStartToLinkBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_StartToBlink;
			if (pLed->bLedOn) {
				pLed->BlinkingLedState = LED_STATE_OFF;
				mod_timer(&pLed->BlinkTimer, jiffies +
					  msecs_to_jiffies(LED_BLINK_SLOWLY_INTERVAL));
			} else {
				pLed->BlinkingLedState = LED_STATE_ON;
				mod_timer(&pLed->BlinkTimer, jiffies +
					  msecs_to_jiffies(LED_BLINK_NORMAL_INTERVAL));
			}
		}
		break;
	case LED_CTL_LINK:
	case LED_CTL_NO_LINK:
		/*LED1 settings*/
		if (LedAction == LED_CTL_LINK) {
			if (pLed1->bLedWPSBlinkInProgress) {
				pLed1->bLedWPSBlinkInProgress = false;
				del_timer(&pLed1->BlinkTimer);
				pLed1->BlinkingLedState = LED_STATE_OFF;
				pLed1->CurrLedState = LED_STATE_OFF;
				if (pLed1->bLedOn)
					mod_timer(&pLed->BlinkTimer,
						  jiffies + msecs_to_jiffies(0));
			}
		}
		if (!pLed->bLedNoLinkBlinkInProgress) {
			if (pLed->CurrLedState == LED_SCAN_BLINK ||
			    IS_LED_WPS_BLINKING(pLed))
				return;
			if (pLed->bLedBlinkInProgress) {
				del_timer(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			}
			pLed->bLedNoLinkBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_SLOWLY;
			if (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			else
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		}
		break;
	case LED_CTL_SITE_SURVEY:
		if (pmlmepriv->sitesurveyctrl.traffic_busy &&
		    check_fwstate(pmlmepriv, _FW_LINKED))
			;
		else if (!pLed->bLedScanBlinkInProgress) {
			if (IS_LED_WPS_BLINKING(pLed))
				return;
			if (pLed->bLedNoLinkBlinkInProgress) {
				del_timer(&pLed->BlinkTimer);
				pLed->bLedNoLinkBlinkInProgress = false;
			}
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
		if (!pLed->bLedBlinkInProgress) {
			if (pLed->CurrLedState == LED_SCAN_BLINK ||
			    IS_LED_WPS_BLINKING(pLed))
				return;
			if (pLed->bLedNoLinkBlinkInProgress) {
				del_timer(&pLed->BlinkTimer);
				pLed->bLedNoLinkBlinkInProgress = false;
			}
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
	case LED_CTL_START_WPS: /*wait until xinpin finish*/
	case LED_CTL_START_WPS_BOTTON:
		if (pLed1->bLedWPSBlinkInProgress) {
			pLed1->bLedWPSBlinkInProgress = false;
			del_timer(&pLed1->BlinkTimer);
			pLed1->BlinkingLedState = LED_STATE_OFF;
			pLed1->CurrLedState = LED_STATE_OFF;
			if (pLed1->bLedOn)
				mod_timer(&pLed->BlinkTimer,
					  jiffies + msecs_to_jiffies(0));
		}
		if (!pLed->bLedWPSBlinkInProgress) {
			if (pLed->bLedNoLinkBlinkInProgress) {
				del_timer(&pLed->BlinkTimer);
				pLed->bLedNoLinkBlinkInProgress = false;
			}
			if (pLed->bLedBlinkInProgress) {
				del_timer(&pLed->BlinkTimer);
				pLed->bLedBlinkInProgress = false;
			}
			if (pLed->bLedScanBlinkInProgress) {
				del_timer(&pLed->BlinkTimer);
				pLed->bLedScanBlinkInProgress = false;
			}
			pLed->bLedWPSBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_WPS;
			if (pLed->bLedOn) {
				pLed->BlinkingLedState = LED_STATE_OFF;
				mod_timer(&pLed->BlinkTimer, jiffies +
					  msecs_to_jiffies(LED_BLINK_SLOWLY_INTERVAL));
			} else {
				pLed->BlinkingLedState = LED_STATE_ON;
				mod_timer(&pLed->BlinkTimer, jiffies +
					  msecs_to_jiffies(LED_BLINK_NORMAL_INTERVAL));
			}
		}
		break;
	case LED_CTL_STOP_WPS:	/*WPS connect success*/
		if (pLed->bLedWPSBlinkInProgress) {
			del_timer(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		}
		pLed->bLedNoLinkBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_SLOWLY;
		if (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		else
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_timer(&pLed->BlinkTimer, jiffies +
			  msecs_to_jiffies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		break;
	case LED_CTL_STOP_WPS_FAIL:	/*WPS authentication fail*/
		if (pLed->bLedWPSBlinkInProgress) {
			del_timer(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		}
		pLed->bLedNoLinkBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_SLOWLY;
		if (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		else
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_timer(&pLed->BlinkTimer, jiffies +
			  msecs_to_jiffies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		/*LED1 settings*/
		if (pLed1->bLedWPSBlinkInProgress)
			del_timer(&pLed1->BlinkTimer);
		else
			pLed1->bLedWPSBlinkInProgress = true;
		pLed1->CurrLedState = LED_BLINK_WPS_STOP;
		if (pLed1->bLedOn)
			pLed1->BlinkingLedState = LED_STATE_OFF;
		else
			pLed1->BlinkingLedState = LED_STATE_ON;
		mod_timer(&pLed->BlinkTimer, jiffies +
			  msecs_to_jiffies(LED_BLINK_NORMAL_INTERVAL));
		break;
	case LED_CTL_STOP_WPS_FAIL_OVERLAP:	/*WPS session overlap*/
		if (pLed->bLedWPSBlinkInProgress) {
			del_timer(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		}
		pLed->bLedNoLinkBlinkInProgress = true;
		pLed->CurrLedState = LED_BLINK_SLOWLY;
		if (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		else
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_timer(&pLed->BlinkTimer, jiffies +
			  msecs_to_jiffies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		/*LED1 settings*/
		if (pLed1->bLedWPSBlinkInProgress)
			del_timer(&pLed1->BlinkTimer);
		else
			pLed1->bLedWPSBlinkInProgress = true;
		pLed1->CurrLedState = LED_BLINK_WPS_STOP_OVERLAP;
		pLed1->BlinkTimes = 10;
		if (pLed1->bLedOn)
			pLed1->BlinkingLedState = LED_STATE_OFF;
		else
			pLed1->BlinkingLedState = LED_STATE_ON;
		mod_timer(&pLed->BlinkTimer, jiffies +
			  msecs_to_jiffies(LED_BLINK_NORMAL_INTERVAL));
		break;
	case LED_CTL_POWER_OFF:
		pLed->CurrLedState = LED_STATE_OFF;
		pLed->BlinkingLedState = LED_STATE_OFF;
		if (pLed->bLedNoLinkBlinkInProgress) {
			del_timer(&pLed->BlinkTimer);
			pLed->bLedNoLinkBlinkInProgress = false;
		}
		if (pLed->bLedLinkBlinkInProgress) {
			del_timer(&pLed->BlinkTimer);
			pLed->bLedLinkBlinkInProgress = false;
		}
		if (pLed->bLedBlinkInProgress) {
			del_timer(&pLed->BlinkTimer);
			pLed->bLedBlinkInProgress = false;
		}
		if (pLed->bLedWPSBlinkInProgress) {
			del_timer(&pLed->BlinkTimer);
			pLed->bLedWPSBlinkInProgress = false;
		}
		if (pLed->bLedScanBlinkInProgress) {
			del_timer(&pLed->BlinkTimer);
			pLed->bLedScanBlinkInProgress = false;
		}
		if (pLed->bLedStartToLinkBlinkInProgress) {
			del_timer(&pLed->BlinkTimer);
			pLed->bLedStartToLinkBlinkInProgress = false;
		}
		if (pLed1->bLedWPSBlinkInProgress) {
			del_timer(&pLed1->BlinkTimer);
			pLed1->bLedWPSBlinkInProgress = false;
		}
		pLed1->BlinkingLedState = LED_UNKNOWN;
		SwLedOff(padapter, pLed);
		SwLedOff(padapter, pLed1);
		break;
	default:
		break;
	}
}