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
struct timer_list {int dummy; } ;
struct adapter {scalar_t__ bDriverStopped; scalar_t__ bSurpriseRemoved; } ;
struct LED_871x {int /*<<< orphan*/  BlinkWorkItem; struct adapter* padapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BlinkTimer ; 
 struct LED_871x* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct LED_871x* pLed ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void BlinkTimerCallback(struct timer_list *t)
{
	struct LED_871x *pLed = from_timer(pLed, t, BlinkTimer);
	struct adapter *padapter = pLed->padapter;

	if (padapter->bSurpriseRemoved || padapter->bDriverStopped)
		return;

	schedule_work(&pLed->BlinkWorkItem);
}