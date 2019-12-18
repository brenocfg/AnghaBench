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
typedef  int u8 ;
typedef  int u16 ;
struct rtc_time {void* tm_hour; void* tm_min; void* tm_sec; } ;
struct device {int dummy; } ;
struct davinci_rtc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PRTCSS_RTC_DAY0 ; 
 int /*<<< orphan*/  PRTCSS_RTC_DAY1 ; 
 int /*<<< orphan*/  PRTCSS_RTC_HOUR ; 
 int /*<<< orphan*/  PRTCSS_RTC_MIN ; 
 int /*<<< orphan*/  PRTCSS_RTC_SEC ; 
 void* bcd2bin (int) ; 
 scalar_t__ convertfromdays (int,struct rtc_time*) ; 
 int /*<<< orphan*/  davinci_rtc_lock ; 
 int /*<<< orphan*/  davinci_rtcss_calendar_wait (struct davinci_rtc*) ; 
 struct davinci_rtc* dev_get_drvdata (struct device*) ; 
 int rtcss_read (struct davinci_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int davinci_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct davinci_rtc *davinci_rtc = dev_get_drvdata(dev);
	u16 days = 0;
	u8 day0, day1;
	unsigned long flags;

	spin_lock_irqsave(&davinci_rtc_lock, flags);

	davinci_rtcss_calendar_wait(davinci_rtc);
	tm->tm_sec = bcd2bin(rtcss_read(davinci_rtc, PRTCSS_RTC_SEC));

	davinci_rtcss_calendar_wait(davinci_rtc);
	tm->tm_min = bcd2bin(rtcss_read(davinci_rtc, PRTCSS_RTC_MIN));

	davinci_rtcss_calendar_wait(davinci_rtc);
	tm->tm_hour = bcd2bin(rtcss_read(davinci_rtc, PRTCSS_RTC_HOUR));

	davinci_rtcss_calendar_wait(davinci_rtc);
	day0 = rtcss_read(davinci_rtc, PRTCSS_RTC_DAY0);

	davinci_rtcss_calendar_wait(davinci_rtc);
	day1 = rtcss_read(davinci_rtc, PRTCSS_RTC_DAY1);

	spin_unlock_irqrestore(&davinci_rtc_lock, flags);

	days |= day1;
	days <<= 8;
	days |= day0;

	if (convertfromdays(days, tm) < 0)
		return -EINVAL;

	return 0;
}