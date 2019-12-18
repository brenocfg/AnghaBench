#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtc_time {int dummy; } ;
struct rtc_wkalrm {scalar_t__ enabled; struct rtc_time time; } ;
struct TYPE_4__ {scalar_t__ expires; } ;
struct TYPE_3__ {int enabled; TYPE_2__ node; scalar_t__ period; } ;
struct rtc_device {int /*<<< orphan*/  ops_lock; TYPE_1__ aie_timer; int /*<<< orphan*/  timerqueue; } ;

/* Variables and functions */
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtc_read_time (struct rtc_device*,struct rtc_time*) ; 
 scalar_t__ rtc_tm_to_ktime (struct rtc_time) ; 
 int rtc_valid_tm (struct rtc_time*) ; 
 int /*<<< orphan*/  timerqueue_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  trace_rtc_timer_enqueue (TYPE_1__*) ; 

int rtc_initialize_alarm(struct rtc_device *rtc, struct rtc_wkalrm *alarm)
{
	int err;
	struct rtc_time now;

	err = rtc_valid_tm(&alarm->time);
	if (err != 0)
		return err;

	err = rtc_read_time(rtc, &now);
	if (err)
		return err;

	err = mutex_lock_interruptible(&rtc->ops_lock);
	if (err)
		return err;

	rtc->aie_timer.node.expires = rtc_tm_to_ktime(alarm->time);
	rtc->aie_timer.period = 0;

	/* Alarm has to be enabled & in the future for us to enqueue it */
	if (alarm->enabled && (rtc_tm_to_ktime(now) <
			 rtc->aie_timer.node.expires)) {
		rtc->aie_timer.enabled = 1;
		timerqueue_add(&rtc->timerqueue, &rtc->aie_timer.node);
		trace_rtc_timer_enqueue(&rtc->aie_timer);
	}
	mutex_unlock(&rtc->ops_lock);
	return err;
}