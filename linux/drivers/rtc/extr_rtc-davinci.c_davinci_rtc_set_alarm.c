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
typedef  int u16 ;
struct rtc_time {scalar_t__ tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; } ;
struct rtc_wkalrm {struct rtc_time time; } ;
struct device {int dummy; } ;
struct davinci_rtc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PRTCSS_RTC_ADAY0 ; 
 int /*<<< orphan*/  PRTCSS_RTC_ADAY1 ; 
 int /*<<< orphan*/  PRTCSS_RTC_AHOUR ; 
 int /*<<< orphan*/  PRTCSS_RTC_AMIN ; 
 int bin2bcd (int /*<<< orphan*/ ) ; 
 scalar_t__ convert2days (int*,struct rtc_time*) ; 
 int /*<<< orphan*/  davinci_rtc_lock ; 
 int /*<<< orphan*/  davinci_rtc_read_time (struct device*,struct rtc_time*) ; 
 int /*<<< orphan*/  davinci_rtcss_calendar_wait (struct davinci_rtc*) ; 
 struct davinci_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 int /*<<< orphan*/  rtcss_write (struct davinci_rtc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int davinci_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alm)
{
	struct davinci_rtc *davinci_rtc = dev_get_drvdata(dev);
	unsigned long flags;
	u16 days;

	if (alm->time.tm_mday <= 0 && alm->time.tm_mon < 0
	    && alm->time.tm_year < 0) {
		struct rtc_time tm;
		unsigned long now, then;

		davinci_rtc_read_time(dev, &tm);
		rtc_tm_to_time(&tm, &now);

		alm->time.tm_mday = tm.tm_mday;
		alm->time.tm_mon = tm.tm_mon;
		alm->time.tm_year = tm.tm_year;
		rtc_tm_to_time(&alm->time, &then);

		if (then < now) {
			rtc_time_to_tm(now + 24 * 60 * 60, &tm);
			alm->time.tm_mday = tm.tm_mday;
			alm->time.tm_mon = tm.tm_mon;
			alm->time.tm_year = tm.tm_year;
		}
	}

	if (convert2days(&days, &alm->time) < 0)
		return -EINVAL;

	spin_lock_irqsave(&davinci_rtc_lock, flags);

	davinci_rtcss_calendar_wait(davinci_rtc);
	rtcss_write(davinci_rtc, bin2bcd(alm->time.tm_min), PRTCSS_RTC_AMIN);

	davinci_rtcss_calendar_wait(davinci_rtc);
	rtcss_write(davinci_rtc, bin2bcd(alm->time.tm_hour), PRTCSS_RTC_AHOUR);

	davinci_rtcss_calendar_wait(davinci_rtc);
	rtcss_write(davinci_rtc, days & 0xFF, PRTCSS_RTC_ADAY0);

	davinci_rtcss_calendar_wait(davinci_rtc);
	rtcss_write(davinci_rtc, (days & 0xFF00) >> 8, PRTCSS_RTC_ADAY1);

	spin_unlock_irqrestore(&davinci_rtc_lock, flags);

	return 0;
}