#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct TYPE_6__ {int /*<<< orphan*/  expires; } ;
struct TYPE_7__ {scalar_t__ period; TYPE_2__ node; scalar_t__ enabled; } ;
struct rtc_device {int /*<<< orphan*/  ops_lock; TYPE_3__ aie_timer; TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  set_alarm; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtc_timer_enqueue (struct rtc_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  rtc_timer_remove (struct rtc_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  rtc_tm_to_ktime (int /*<<< orphan*/ ) ; 
 int rtc_valid_range (struct rtc_device*,int /*<<< orphan*/ *) ; 
 int rtc_valid_tm (int /*<<< orphan*/ *) ; 

int rtc_set_alarm(struct rtc_device *rtc, struct rtc_wkalrm *alarm)
{
	int err;

	if (!rtc->ops)
		return -ENODEV;
	else if (!rtc->ops->set_alarm)
		return -EINVAL;

	err = rtc_valid_tm(&alarm->time);
	if (err != 0)
		return err;

	err = rtc_valid_range(rtc, &alarm->time);
	if (err)
		return err;

	err = mutex_lock_interruptible(&rtc->ops_lock);
	if (err)
		return err;
	if (rtc->aie_timer.enabled)
		rtc_timer_remove(rtc, &rtc->aie_timer);

	rtc->aie_timer.node.expires = rtc_tm_to_ktime(alarm->time);
	rtc->aie_timer.period = 0;
	if (alarm->enabled)
		err = rtc_timer_enqueue(rtc, &rtc->aie_timer);

	mutex_unlock(&rtc->ops_lock);

	return err;
}