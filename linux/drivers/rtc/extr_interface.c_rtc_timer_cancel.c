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
struct rtc_timer {scalar_t__ enabled; } ;
struct rtc_device {int /*<<< orphan*/  ops_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_timer_remove (struct rtc_device*,struct rtc_timer*) ; 

void rtc_timer_cancel(struct rtc_device *rtc, struct rtc_timer *timer)
{
	mutex_lock(&rtc->ops_lock);
	if (timer->enabled)
		rtc_timer_remove(rtc, timer);
	mutex_unlock(&rtc->ops_lock);
}