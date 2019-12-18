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
struct timespec64 {unsigned long tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct rtc_time {int dummy; } ;
struct rtc_device {int /*<<< orphan*/  set_offset_nsec; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RTC_SYSTOHC_DEVICE ; 
 int ENODEV ; 
 int EPROTO ; 
 int /*<<< orphan*/  rtc_class_close (struct rtc_device*) ; 
 struct rtc_device* rtc_class_open (int /*<<< orphan*/ ) ; 
 int rtc_set_time (struct rtc_device*,struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 
 int rtc_tv_nsec_ok (int /*<<< orphan*/ ,struct timespec64*,struct timespec64*) ; 
 int /*<<< orphan*/  set_normalized_timespec64 (struct timespec64*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtc_set_ntp_time(struct timespec64 now, unsigned long *target_nsec)
{
	struct rtc_device *rtc;
	struct rtc_time tm;
	struct timespec64 to_set;
	int err = -ENODEV;
	bool ok;

	rtc = rtc_class_open(CONFIG_RTC_SYSTOHC_DEVICE);
	if (!rtc)
		goto out_err;

	if (!rtc->ops || !rtc->ops->set_time)
		goto out_close;

	/* Compute the value of tv_nsec we require the caller to supply in
	 * now.tv_nsec.  This is the value such that (now +
	 * set_offset_nsec).tv_nsec == 0.
	 */
	set_normalized_timespec64(&to_set, 0, -rtc->set_offset_nsec);
	*target_nsec = to_set.tv_nsec;

	/* The ntp code must call this with the correct value in tv_nsec, if
	 * it does not we update target_nsec and return EPROTO to make the ntp
	 * code try again later.
	 */
	ok = rtc_tv_nsec_ok(rtc->set_offset_nsec, &to_set, &now);
	if (!ok) {
		err = -EPROTO;
		goto out_close;
	}

	rtc_time64_to_tm(to_set.tv_sec, &tm);

	err = rtc_set_time(rtc, &tm);

out_close:
	rtc_class_close(rtc);
out_err:
	return err;
}