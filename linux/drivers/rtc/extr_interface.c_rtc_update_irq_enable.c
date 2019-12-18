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
struct rtc_time {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  expires; } ;
struct TYPE_5__ {unsigned int enabled; void* period; TYPE_1__ node; } ;
struct rtc_device {int /*<<< orphan*/  ops_lock; TYPE_2__ uie_rtctimer; scalar_t__ uie_unsupported; scalar_t__ uie_irq_active; } ;
typedef  void* ktime_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __rtc_read_time (struct rtc_device*,struct rtc_time*) ; 
 int /*<<< orphan*/  ktime_add (void*,void*) ; 
 void* ktime_set (int,int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtc_dev_update_irq_enable_emul (struct rtc_device*,unsigned int) ; 
 int rtc_timer_enqueue (struct rtc_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  rtc_timer_remove (struct rtc_device*,TYPE_2__*) ; 
 void* rtc_tm_to_ktime (struct rtc_time) ; 

int rtc_update_irq_enable(struct rtc_device *rtc, unsigned int enabled)
{
	int err;

	err = mutex_lock_interruptible(&rtc->ops_lock);
	if (err)
		return err;

#ifdef CONFIG_RTC_INTF_DEV_UIE_EMUL
	if (enabled == 0 && rtc->uie_irq_active) {
		mutex_unlock(&rtc->ops_lock);
		return rtc_dev_update_irq_enable_emul(rtc, 0);
	}
#endif
	/* make sure we're changing state */
	if (rtc->uie_rtctimer.enabled == enabled)
		goto out;

	if (rtc->uie_unsupported) {
		err = -EINVAL;
		goto out;
	}

	if (enabled) {
		struct rtc_time tm;
		ktime_t now, onesec;

		__rtc_read_time(rtc, &tm);
		onesec = ktime_set(1, 0);
		now = rtc_tm_to_ktime(tm);
		rtc->uie_rtctimer.node.expires = ktime_add(now, onesec);
		rtc->uie_rtctimer.period = ktime_set(1, 0);
		err = rtc_timer_enqueue(rtc, &rtc->uie_rtctimer);
	} else {
		rtc_timer_remove(rtc, &rtc->uie_rtctimer);
	}

out:
	mutex_unlock(&rtc->ops_lock);
#ifdef CONFIG_RTC_INTF_DEV_UIE_EMUL
	/*
	 * Enable emulation if the driver returned -EINVAL to signal that it has
	 * been configured without interrupts or they are not available at the
	 * moment.
	 */
	if (err == -EINVAL)
		err = rtc_dev_update_irq_enable_emul(rtc, enabled);
#endif
	return err;
}