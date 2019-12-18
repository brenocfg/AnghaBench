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
typedef  scalar_t__ time64_t ;
struct rtc_wkalrm {int enabled; int /*<<< orphan*/  time; } ;
struct rtc_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 scalar_t__ EINVAL ; 
 scalar_t__ kstrtos64 (char const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ rtc_read_alarm (struct rtc_device*,struct rtc_wkalrm*) ; 
 scalar_t__ rtc_read_time (struct rtc_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ rtc_set_alarm (struct rtc_device*,struct rtc_wkalrm*) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ rtc_tm_to_time64 (int /*<<< orphan*/ *) ; 
 struct rtc_device* to_rtc_device (struct device*) ; 

__attribute__((used)) static ssize_t
wakealarm_store(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t n)
{
	ssize_t retval;
	time64_t now, alarm;
	time64_t push = 0;
	struct rtc_wkalrm alm;
	struct rtc_device *rtc = to_rtc_device(dev);
	const char *buf_ptr;
	int adjust = 0;

	/* Only request alarms that trigger in the future.  Disable them
	 * by writing another time, e.g. 0 meaning Jan 1 1970 UTC.
	 */
	retval = rtc_read_time(rtc, &alm.time);
	if (retval < 0)
		return retval;
	now = rtc_tm_to_time64(&alm.time);

	buf_ptr = buf;
	if (*buf_ptr == '+') {
		buf_ptr++;
		if (*buf_ptr == '=') {
			buf_ptr++;
			push = 1;
		} else {
			adjust = 1;
		}
	}
	retval = kstrtos64(buf_ptr, 0, &alarm);
	if (retval)
		return retval;
	if (adjust)
		alarm += now;
	if (alarm > now || push) {
		/* Avoid accidentally clobbering active alarms; we can't
		 * entirely prevent that here, without even the minimal
		 * locking from the /dev/rtcN api.
		 */
		retval = rtc_read_alarm(rtc, &alm);
		if (retval < 0)
			return retval;
		if (alm.enabled) {
			if (push) {
				push = rtc_tm_to_time64(&alm.time);
				alarm += push;
			} else
				return -EBUSY;
		} else if (push)
			return -EINVAL;
		alm.enabled = 1;
	} else {
		alm.enabled = 0;

		/* Provide a valid future alarm time.  Linux isn't EFI,
		 * this time won't be ignored when disabling the alarm.
		 */
		alarm = now + 300;
	}
	rtc_time64_to_tm(alarm, &alm.time);

	retval = rtc_set_alarm(rtc, &alm);
	return (retval < 0) ? retval : n;
}