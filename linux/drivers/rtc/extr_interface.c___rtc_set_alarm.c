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
typedef  scalar_t__ time64_t ;
struct rtc_time {int dummy; } ;
struct rtc_wkalrm {struct rtc_time time; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {TYPE_2__ dev; TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_alarm ) (int /*<<< orphan*/ ,struct rtc_wkalrm*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ETIME ; 
 int __rtc_read_time (struct rtc_device*,struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_subtract_offset (struct rtc_device*,struct rtc_time*) ; 
 scalar_t__ rtc_tm_to_time64 (struct rtc_time*) ; 
 int rtc_valid_tm (struct rtc_time*) ; 
 int stub1 (int /*<<< orphan*/ ,struct rtc_wkalrm*) ; 
 int /*<<< orphan*/  trace_rtc_set_alarm (scalar_t__,int) ; 

__attribute__((used)) static int __rtc_set_alarm(struct rtc_device *rtc, struct rtc_wkalrm *alarm)
{
	struct rtc_time tm;
	time64_t now, scheduled;
	int err;

	err = rtc_valid_tm(&alarm->time);
	if (err)
		return err;

	scheduled = rtc_tm_to_time64(&alarm->time);

	/* Make sure we're not setting alarms in the past */
	err = __rtc_read_time(rtc, &tm);
	if (err)
		return err;
	now = rtc_tm_to_time64(&tm);
	if (scheduled <= now)
		return -ETIME;
	/*
	 * XXX - We just checked to make sure the alarm time is not
	 * in the past, but there is still a race window where if
	 * the is alarm set for the next second and the second ticks
	 * over right here, before we set the alarm.
	 */

	rtc_subtract_offset(rtc, &alarm->time);

	if (!rtc->ops)
		err = -ENODEV;
	else if (!rtc->ops->set_alarm)
		err = -EINVAL;
	else
		err = rtc->ops->set_alarm(rtc->dev.parent, alarm);

	trace_rtc_set_alarm(rtc_tm_to_time64(&alarm->time), err);
	return err;
}