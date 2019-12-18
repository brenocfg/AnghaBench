#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; int tm_wday; int tm_yday; int tm_isdst; } ;
struct rtc_wkalrm {TYPE_3__ time; scalar_t__ pending; scalar_t__ enabled; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {int /*<<< orphan*/  ops_lock; TYPE_2__ dev; TYPE_1__* ops; } ;
struct TYPE_4__ {int (* read_alarm ) (int /*<<< orphan*/ ,struct rtc_wkalrm*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_tm_to_time64 (TYPE_3__*) ; 
 int stub1 (int /*<<< orphan*/ ,struct rtc_wkalrm*) ; 
 int /*<<< orphan*/  trace_rtc_read_alarm (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtc_read_alarm_internal(struct rtc_device *rtc,
				   struct rtc_wkalrm *alarm)
{
	int err;

	err = mutex_lock_interruptible(&rtc->ops_lock);
	if (err)
		return err;

	if (!rtc->ops) {
		err = -ENODEV;
	} else if (!rtc->ops->read_alarm) {
		err = -EINVAL;
	} else {
		alarm->enabled = 0;
		alarm->pending = 0;
		alarm->time.tm_sec = -1;
		alarm->time.tm_min = -1;
		alarm->time.tm_hour = -1;
		alarm->time.tm_mday = -1;
		alarm->time.tm_mon = -1;
		alarm->time.tm_year = -1;
		alarm->time.tm_wday = -1;
		alarm->time.tm_yday = -1;
		alarm->time.tm_isdst = -1;
		err = rtc->ops->read_alarm(rtc->dev.parent, alarm);
	}

	mutex_unlock(&rtc->ops_lock);

	trace_rtc_read_alarm(rtc_tm_to_time64(&alarm->time), err);
	return err;
}