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
struct _adapter {int dummy; } ;
struct LED_871x {int LedPin; int bLedOn; int bLedBlinkInProgress; int /*<<< orphan*/  BlinkWorkItem; int /*<<< orphan*/  BlinkTimer; int /*<<< orphan*/  BlinkingLedState; scalar_t__ BlinkTimes; int /*<<< orphan*/  CurrLedState; struct _adapter* padapter; } ;
typedef  enum LED_PIN_871x { ____Placeholder_LED_PIN_871x } LED_PIN_871x ;

/* Variables and functions */
 int /*<<< orphan*/  BlinkTimerCallback ; 
 int /*<<< orphan*/  BlinkWorkItemCallback ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_STATE_OFF ; 
 int /*<<< orphan*/  LED_UNKNOWN ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void InitLed871x(struct _adapter *padapter, struct LED_871x *pLed,
		 enum LED_PIN_871x	LedPin)
{
	pLed->padapter = padapter;
	pLed->LedPin = LedPin;
	pLed->CurrLedState = LED_STATE_OFF;
	pLed->bLedOn = false;
	pLed->bLedBlinkInProgress = false;
	pLed->BlinkTimes = 0;
	pLed->BlinkingLedState = LED_UNKNOWN;
	timer_setup(&pLed->BlinkTimer, BlinkTimerCallback, 0);
	INIT_WORK(&pLed->BlinkWorkItem, BlinkWorkItemCallback);
}