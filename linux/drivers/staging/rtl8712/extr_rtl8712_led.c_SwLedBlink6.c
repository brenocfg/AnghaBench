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
struct _adapter {int dummy; } ;
struct LED_871x {scalar_t__ BlinkingLedState; int CurrLedState; int bLedBlinkInProgress; int /*<<< orphan*/  BlinkTimer; int /*<<< orphan*/  bLedOn; int /*<<< orphan*/  BlinkTimes; struct _adapter* padapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_BLINK_FASTER_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_SCAN_INTERVAL_ALPHA ; 
#define  LED_BLINK_WPS 129 
 void* LED_STATE_OFF ; 
 scalar_t__ LED_STATE_ON ; 
#define  LED_TXRX_BLINK 128 
 int /*<<< orphan*/  SwLedOff (struct _adapter*,struct LED_871x*) ; 
 int /*<<< orphan*/  SwLedOn (struct _adapter*,struct LED_871x*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SwLedBlink6(struct LED_871x *pLed)
{
	struct _adapter *padapter = pLed->padapter;
	u8 bStopBlinking = false;

	/* Change LED according to BlinkingLedState specified. */
	if (pLed->BlinkingLedState == LED_STATE_ON)
		SwLedOn(padapter, pLed);
	else
		SwLedOff(padapter, pLed);
	switch (pLed->CurrLedState) {
	case LED_TXRX_BLINK:
		pLed->BlinkTimes--;
		if (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		if (bStopBlinking) {
			pLed->CurrLedState = LED_STATE_ON;
			pLed->BlinkingLedState = LED_STATE_ON;
			if (!pLed->bLedOn)
				SwLedOn(padapter, pLed);
			pLed->bLedBlinkInProgress = false;
		} else {
			if (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			else
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		}
		break;
	case LED_BLINK_WPS:
		if (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		else
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_timer(&pLed->BlinkTimer, jiffies +
			  msecs_to_jiffies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		break;

	default:
		break;
	}
}