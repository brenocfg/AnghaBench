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
struct TYPE_2__ {void* expires; } ;
struct rtc_timer {void* period; TYPE_1__ node; scalar_t__ enabled; } ;
struct rtc_device {int /*<<< orphan*/  ops_lock; } ;
typedef  void* ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtc_timer_enqueue (struct rtc_device*,struct rtc_timer*) ; 
 int /*<<< orphan*/  rtc_timer_remove (struct rtc_device*,struct rtc_timer*) ; 

int rtc_timer_start(struct rtc_device *rtc, struct rtc_timer *timer,
		    ktime_t expires, ktime_t period)
{
	int ret = 0;

	mutex_lock(&rtc->ops_lock);
	if (timer->enabled)
		rtc_timer_remove(rtc, timer);

	timer->node.expires = expires;
	timer->period = period;

	ret = rtc_timer_enqueue(rtc, timer);

	mutex_unlock(&rtc->ops_lock);
	return ret;
}