#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timerqueue_node {scalar_t__ expires; } ;
struct rtc_wkalrm {int enabled; int /*<<< orphan*/  time; } ;
struct TYPE_5__ {int /*<<< orphan*/  expires; } ;
struct rtc_timer {int enabled; TYPE_2__ node; } ;
struct rtc_time {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {int /*<<< orphan*/  timerqueue; int /*<<< orphan*/  irqwork; TYPE_1__ dev; } ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  __rtc_read_time (struct rtc_device*,struct rtc_time*) ; 
 int __rtc_set_alarm (struct rtc_device*,struct rtc_wkalrm*) ; 
 scalar_t__ ktime_before (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pm_stay_awake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_ktime_to_tm (int /*<<< orphan*/ ) ; 
 scalar_t__ rtc_tm_to_ktime (struct rtc_time) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timerqueue_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  timerqueue_del (int /*<<< orphan*/ *,TYPE_2__*) ; 
 struct timerqueue_node* timerqueue_getnext (int /*<<< orphan*/ *) ; 
 struct timerqueue_node* timerqueue_iterate_next (struct timerqueue_node*) ; 
 int /*<<< orphan*/  trace_rtc_timer_dequeue (struct rtc_timer*) ; 
 int /*<<< orphan*/  trace_rtc_timer_enqueue (struct rtc_timer*) ; 

__attribute__((used)) static int rtc_timer_enqueue(struct rtc_device *rtc, struct rtc_timer *timer)
{
	struct timerqueue_node *next = timerqueue_getnext(&rtc->timerqueue);
	struct rtc_time tm;
	ktime_t now;

	timer->enabled = 1;
	__rtc_read_time(rtc, &tm);
	now = rtc_tm_to_ktime(tm);

	/* Skip over expired timers */
	while (next) {
		if (next->expires >= now)
			break;
		next = timerqueue_iterate_next(next);
	}

	timerqueue_add(&rtc->timerqueue, &timer->node);
	trace_rtc_timer_enqueue(timer);
	if (!next || ktime_before(timer->node.expires, next->expires)) {
		struct rtc_wkalrm alarm;
		int err;

		alarm.time = rtc_ktime_to_tm(timer->node.expires);
		alarm.enabled = 1;
		err = __rtc_set_alarm(rtc, &alarm);
		if (err == -ETIME) {
			pm_stay_awake(rtc->dev.parent);
			schedule_work(&rtc->irqwork);
		} else if (err) {
			timerqueue_del(&rtc->timerqueue, &timer->node);
			trace_rtc_timer_dequeue(timer);
			timer->enabled = 0;
			return err;
		}
	}
	return 0;
}