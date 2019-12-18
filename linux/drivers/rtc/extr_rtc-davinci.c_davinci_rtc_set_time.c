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
struct rtc_time {int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct device {int dummy; } ;
struct davinci_rtc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PRTCSS_RTC_CCTRL ; 
 int PRTCSS_RTC_CCTRL_CAEN ; 
 int /*<<< orphan*/  PRTCSS_RTC_DAY0 ; 
 int /*<<< orphan*/  PRTCSS_RTC_DAY1 ; 
 int /*<<< orphan*/  PRTCSS_RTC_HOUR ; 
 int /*<<< orphan*/  PRTCSS_RTC_MIN ; 
 int /*<<< orphan*/  PRTCSS_RTC_SEC ; 
 int bin2bcd (int /*<<< orphan*/ ) ; 
 scalar_t__ convert2days (int*,struct rtc_time*) ; 
 int /*<<< orphan*/  davinci_rtc_lock ; 
 int /*<<< orphan*/  davinci_rtcss_calendar_wait (struct davinci_rtc*) ; 
 struct davinci_rtc* dev_get_drvdata (struct device*) ; 
 int rtcss_read (struct davinci_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtcss_write (struct davinci_rtc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int davinci_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct davinci_rtc *davinci_rtc = dev_get_drvdata(dev);
	u16 days;
	u8 rtc_cctrl;
	unsigned long flags;

	if (convert2days(&days, tm) < 0)
		return -EINVAL;

	spin_lock_irqsave(&davinci_rtc_lock, flags);

	davinci_rtcss_calendar_wait(davinci_rtc);
	rtcss_write(davinci_rtc, bin2bcd(tm->tm_sec), PRTCSS_RTC_SEC);

	davinci_rtcss_calendar_wait(davinci_rtc);
	rtcss_write(davinci_rtc, bin2bcd(tm->tm_min), PRTCSS_RTC_MIN);

	davinci_rtcss_calendar_wait(davinci_rtc);
	rtcss_write(davinci_rtc, bin2bcd(tm->tm_hour), PRTCSS_RTC_HOUR);

	davinci_rtcss_calendar_wait(davinci_rtc);
	rtcss_write(davinci_rtc, days & 0xFF, PRTCSS_RTC_DAY0);

	davinci_rtcss_calendar_wait(davinci_rtc);
	rtcss_write(davinci_rtc, (days & 0xFF00) >> 8, PRTCSS_RTC_DAY1);

	rtc_cctrl = rtcss_read(davinci_rtc, PRTCSS_RTC_CCTRL);
	rtc_cctrl |= PRTCSS_RTC_CCTRL_CAEN;
	rtcss_write(davinci_rtc, rtc_cctrl, PRTCSS_RTC_CCTRL);

	spin_unlock_irqrestore(&davinci_rtc_lock, flags);

	return 0;
}