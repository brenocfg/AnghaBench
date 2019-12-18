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
struct rtc_wkalrm {int /*<<< orphan*/  time; int /*<<< orphan*/  enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  expires; } ;
struct TYPE_5__ {TYPE_1__ node; int /*<<< orphan*/  enabled; } ;
struct rtc_device {int /*<<< orphan*/  ops_lock; TYPE_2__ aie_timer; TYPE_3__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  read_alarm; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  memset (struct rtc_wkalrm*,int /*<<< orphan*/ ,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_ktime_to_tm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_tm_to_time64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rtc_read_alarm (int /*<<< orphan*/ ,int) ; 

int rtc_read_alarm(struct rtc_device *rtc, struct rtc_wkalrm *alarm)
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
		memset(alarm, 0, sizeof(struct rtc_wkalrm));
		alarm->enabled = rtc->aie_timer.enabled;
		alarm->time = rtc_ktime_to_tm(rtc->aie_timer.node.expires);
	}
	mutex_unlock(&rtc->ops_lock);

	trace_rtc_read_alarm(rtc_tm_to_time64(&alarm->time), err);
	return err;
}