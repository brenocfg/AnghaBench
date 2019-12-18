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
struct adapter {int dummy; } ;
struct LED_871x {int /*<<< orphan*/  BlinkWorkItem; int /*<<< orphan*/  BlinkTimer; struct adapter* padapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BlinkTimerCallback ; 
 int /*<<< orphan*/  BlinkWorkItemCallback ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetLedStatus (struct LED_871x*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void InitLed871x(struct adapter *padapter, struct LED_871x *pLed)
{
	pLed->padapter = padapter;

	ResetLedStatus(pLed);

	timer_setup(&pLed->BlinkTimer, BlinkTimerCallback, 0);

	INIT_WORK(&pLed->BlinkWorkItem, BlinkWorkItemCallback);
}