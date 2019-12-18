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
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;
struct omap_rtc {TYPE_1__* type; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* lock ) (struct omap_rtc*) ;int /*<<< orphan*/  (* unlock ) (struct omap_rtc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_RTC_DAYS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_HOURS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_MINUTES_REG ; 
 int /*<<< orphan*/  OMAP_RTC_MONTHS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_SECONDS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_YEARS_REG ; 
 struct omap_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  rtc_wait_not_busy (struct omap_rtc*) ; 
 int /*<<< orphan*/  rtc_write (struct omap_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct omap_rtc*) ; 
 int /*<<< orphan*/  stub2 (struct omap_rtc*) ; 
 int /*<<< orphan*/  tm2bcd (struct rtc_time*) ; 

__attribute__((used)) static int omap_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct omap_rtc *rtc = dev_get_drvdata(dev);

	tm2bcd(tm);

	local_irq_disable();
	rtc_wait_not_busy(rtc);

	rtc->type->unlock(rtc);
	rtc_write(rtc, OMAP_RTC_YEARS_REG, tm->tm_year);
	rtc_write(rtc, OMAP_RTC_MONTHS_REG, tm->tm_mon);
	rtc_write(rtc, OMAP_RTC_DAYS_REG, tm->tm_mday);
	rtc_write(rtc, OMAP_RTC_HOURS_REG, tm->tm_hour);
	rtc_write(rtc, OMAP_RTC_MINUTES_REG, tm->tm_min);
	rtc_write(rtc, OMAP_RTC_SECONDS_REG, tm->tm_sec);
	rtc->type->lock(rtc);

	local_irq_enable();

	return 0;
}