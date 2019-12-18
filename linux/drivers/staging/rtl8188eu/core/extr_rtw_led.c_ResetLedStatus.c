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
struct LED_871x {int bLedOn; int bLedBlinkInProgress; int bLedWPSBlinkInProgress; int bLedNoLinkBlinkInProgress; int bLedLinkBlinkInProgress; int bLedScanBlinkInProgress; int /*<<< orphan*/  BlinkingLedState; scalar_t__ BlinkTimes; int /*<<< orphan*/  CurrLedState; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_UNKNOWN ; 
 int /*<<< orphan*/  RTW_LED_OFF ; 

void ResetLedStatus(struct LED_871x *pLed)
{
	pLed->CurrLedState = RTW_LED_OFF; /*  Current LED state. */
	pLed->bLedOn = false; /*  true if LED is ON, false if LED is OFF. */

	pLed->bLedBlinkInProgress = false; /*  true if it is blinking, false o.w.. */
	pLed->bLedWPSBlinkInProgress = false;

	pLed->BlinkTimes = 0; /*  Number of times to toggle led state for blinking. */
	pLed->BlinkingLedState = LED_UNKNOWN; /*  Next state for blinking, either RTW_LED_ON or RTW_LED_OFF are. */

	pLed->bLedNoLinkBlinkInProgress = false;
	pLed->bLedLinkBlinkInProgress = false;
	pLed->bLedScanBlinkInProgress = false;
}