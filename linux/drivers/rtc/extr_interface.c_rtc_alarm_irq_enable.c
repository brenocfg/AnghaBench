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
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {unsigned int enabled; } ;
struct rtc_device {int /*<<< orphan*/  ops_lock; TYPE_2__ dev; TYPE_1__* ops; TYPE_3__ aie_timer; } ;
struct TYPE_5__ {int (* alarm_irq_enable ) (int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtc_timer_enqueue (struct rtc_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  rtc_timer_remove (struct rtc_device*,TYPE_3__*) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  trace_rtc_alarm_irq_enable (unsigned int,int) ; 

int rtc_alarm_irq_enable(struct rtc_device *rtc, unsigned int enabled)
{
	int err;

	err = mutex_lock_interruptible(&rtc->ops_lock);
	if (err)
		return err;

	if (rtc->aie_timer.enabled != enabled) {
		if (enabled)
			err = rtc_timer_enqueue(rtc, &rtc->aie_timer);
		else
			rtc_timer_remove(rtc, &rtc->aie_timer);
	}

	if (err)
		/* nothing */;
	else if (!rtc->ops)
		err = -ENODEV;
	else if (!rtc->ops->alarm_irq_enable)
		err = -EINVAL;
	else
		err = rtc->ops->alarm_irq_enable(rtc->dev.parent, enabled);

	mutex_unlock(&rtc->ops_lock);

	trace_rtc_alarm_irq_enable(enabled, err);
	return err;
}