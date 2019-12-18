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
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXC_RTC_TIME ; 
 scalar_t__ get_alarm_or_time (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (scalar_t__,struct rtc_time*) ; 

__attribute__((used)) static int mxc_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	time64_t val;

	/* Avoid roll-over from reading the different registers */
	do {
		val = get_alarm_or_time(dev, MXC_RTC_TIME);
	} while (val != get_alarm_or_time(dev, MXC_RTC_TIME));

	rtc_time64_to_tm(val, tm);

	return 0;
}