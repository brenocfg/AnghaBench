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
struct timerqueue_node {int /*<<< orphan*/  expires; } ;
struct rtc_wkalrm {int enabled; int /*<<< orphan*/  time; } ;
struct rtc_timer {struct timerqueue_node node; scalar_t__ enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {int /*<<< orphan*/  irqwork; TYPE_1__ dev; int /*<<< orphan*/  timerqueue; } ;

/* Variables and functions */
 int ETIME ; 
 int __rtc_set_alarm (struct rtc_device*,struct rtc_wkalrm*) ; 
 int /*<<< orphan*/  pm_stay_awake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_alarm_disable (struct rtc_device*) ; 
 int /*<<< orphan*/  rtc_ktime_to_tm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timerqueue_del (int /*<<< orphan*/ *,struct timerqueue_node*) ; 
 struct timerqueue_node* timerqueue_getnext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rtc_timer_dequeue (struct rtc_timer*) ; 

__attribute__((used)) static void rtc_timer_remove(struct rtc_device *rtc, struct rtc_timer *timer)
{
	struct timerqueue_node *next = timerqueue_getnext(&rtc->timerqueue);

	timerqueue_del(&rtc->timerqueue, &timer->node);
	trace_rtc_timer_dequeue(timer);
	timer->enabled = 0;
	if (next == &timer->node) {
		struct rtc_wkalrm alarm;
		int err;

		next = timerqueue_getnext(&rtc->timerqueue);
		if (!next) {
			rtc_alarm_disable(rtc);
			return;
		}
		alarm.time = rtc_ktime_to_tm(next->expires);
		alarm.enabled = 1;
		err = __rtc_set_alarm(rtc, &alarm);
		if (err == -ETIME) {
			pm_stay_awake(rtc->dev.parent);
			schedule_work(&rtc->irqwork);
		}
	}
}