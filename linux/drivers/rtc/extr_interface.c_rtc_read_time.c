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
struct rtc_time {int dummy; } ;
struct rtc_device {int /*<<< orphan*/  ops_lock; } ;

/* Variables and functions */
 int __rtc_read_time (struct rtc_device*,struct rtc_time*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_tm_to_time64 (struct rtc_time*) ; 
 int /*<<< orphan*/  trace_rtc_read_time (int /*<<< orphan*/ ,int) ; 

int rtc_read_time(struct rtc_device *rtc, struct rtc_time *tm)
{
	int err;

	err = mutex_lock_interruptible(&rtc->ops_lock);
	if (err)
		return err;

	err = __rtc_read_time(rtc, tm);
	mutex_unlock(&rtc->ops_lock);

	trace_rtc_read_time(rtc_tm_to_time64(tm), err);
	return err;
}