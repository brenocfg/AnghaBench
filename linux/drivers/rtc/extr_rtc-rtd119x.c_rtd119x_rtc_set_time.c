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
struct rtd119x_rtc {int base_year; scalar_t__ base; } ;
struct rtc_time {int tm_year; int tm_sec; unsigned int tm_min; unsigned int tm_hour; scalar_t__ tm_yday; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RTD_RTCDATE1 ; 
 unsigned int RTD_RTCDATE1_RTCDATE1_MASK ; 
 scalar_t__ RTD_RTCDATE2 ; 
 unsigned int RTD_RTCDATE2_RTCDATE2_MASK ; 
 scalar_t__ RTD_RTCHR ; 
 unsigned int RTD_RTCHR_RTCHR_MASK ; 
 scalar_t__ RTD_RTCMIN ; 
 unsigned int RTD_RTCMIN_RTCMIN_MASK ; 
 scalar_t__ RTD_RTCSEC ; 
 int RTD_RTCSEC_RTCSEC_MASK ; 
 struct rtd119x_rtc* dev_get_drvdata (struct device*) ; 
 scalar_t__ rtd119x_rtc_days_in_year (int) ; 
 int /*<<< orphan*/  rtd119x_rtc_set_enabled (struct device*,int) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static int rtd119x_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct rtd119x_rtc *data = dev_get_drvdata(dev);
	unsigned int day;
	int i;

	if (1900 + tm->tm_year < data->base_year)
		return -EINVAL;

	day = 0;
	for (i = data->base_year; i < 1900 + tm->tm_year; i++)
		day += rtd119x_rtc_days_in_year(i);

	day += tm->tm_yday;
	if (day > 0x7fff)
		return -EINVAL;

	rtd119x_rtc_set_enabled(dev, false);

	writel_relaxed((tm->tm_sec << 1) & RTD_RTCSEC_RTCSEC_MASK, data->base + RTD_RTCSEC);
	writel_relaxed(tm->tm_min & RTD_RTCMIN_RTCMIN_MASK, data->base + RTD_RTCMIN);
	writel_relaxed(tm->tm_hour & RTD_RTCHR_RTCHR_MASK, data->base + RTD_RTCHR);
	writel_relaxed(day & RTD_RTCDATE1_RTCDATE1_MASK, data->base + RTD_RTCDATE1);
	writel_relaxed((day >> 8) & RTD_RTCDATE2_RTCDATE2_MASK, data->base + RTD_RTCDATE2);

	rtd119x_rtc_set_enabled(dev, true);

	return 0;
}