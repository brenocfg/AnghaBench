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
struct spear_rtc_config {scalar_t__ ioaddr; } ;
struct TYPE_2__ {unsigned int tm_sec; unsigned int tm_min; unsigned int tm_hour; unsigned int tm_mday; unsigned int tm_mon; unsigned int tm_year; } ;
struct rtc_wkalrm {scalar_t__ enabled; TYPE_1__ time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALARM_DATE_REG ; 
 scalar_t__ ALARM_TIME_REG ; 
 unsigned int HOUR_SHIFT ; 
 unsigned int MDAY_SHIFT ; 
 unsigned int MINUTE_SHIFT ; 
 unsigned int MONTH_SHIFT ; 
 unsigned int SECOND_SHIFT ; 
 unsigned int YEAR_SHIFT ; 
 struct spear_rtc_config* dev_get_drvdata (struct device*) ; 
 int is_write_complete (struct spear_rtc_config*) ; 
 int /*<<< orphan*/  rtc_wait_not_busy (struct spear_rtc_config*) ; 
 int /*<<< orphan*/  spear_rtc_disable_interrupt (struct spear_rtc_config*) ; 
 int /*<<< orphan*/  spear_rtc_enable_interrupt (struct spear_rtc_config*) ; 
 int /*<<< orphan*/  tm2bcd (TYPE_1__*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int spear_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alm)
{
	struct spear_rtc_config *config = dev_get_drvdata(dev);
	unsigned int time, date;
	int err;

	tm2bcd(&alm->time);

	rtc_wait_not_busy(config);

	time = (alm->time.tm_sec << SECOND_SHIFT) | (alm->time.tm_min <<
			MINUTE_SHIFT) |	(alm->time.tm_hour << HOUR_SHIFT);
	date = (alm->time.tm_mday << MDAY_SHIFT) | (alm->time.tm_mon <<
			MONTH_SHIFT) | (alm->time.tm_year << YEAR_SHIFT);

	writel(time, config->ioaddr + ALARM_TIME_REG);
	writel(date, config->ioaddr + ALARM_DATE_REG);
	err = is_write_complete(config);
	if (err < 0)
		return err;

	if (alm->enabled)
		spear_rtc_enable_interrupt(config);
	else
		spear_rtc_disable_interrupt(config);

	return 0;
}