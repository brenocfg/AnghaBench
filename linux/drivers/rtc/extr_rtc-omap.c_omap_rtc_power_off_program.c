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
typedef  int u32 ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; } ;
struct omap_rtc {TYPE_1__* type; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* lock ) (struct omap_rtc*) ;int /*<<< orphan*/  (* unlock ) (struct omap_rtc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_RTC_ALARM2_DAYS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM2_HOURS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM2_MINUTES_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM2_MONTHS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM2_SECONDS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM2_YEARS_REG ; 
 int OMAP_RTC_INTERRUPTS_IT_ALARM2 ; 
 int /*<<< orphan*/  OMAP_RTC_INTERRUPTS_REG ; 
 int OMAP_RTC_PMIC_POWER_EN_EN ; 
 int /*<<< orphan*/  OMAP_RTC_PMIC_REG ; 
 int /*<<< orphan*/  OMAP_RTC_SECONDS_REG ; 
 int OMAP_RTC_STATUS_ALARM2 ; 
 int /*<<< orphan*/  OMAP_RTC_STATUS_REG ; 
 int /*<<< orphan*/  bcd2tm (struct rtc_time*) ; 
 struct omap_rtc* omap_rtc_power_off_rtc ; 
 int /*<<< orphan*/  omap_rtc_read_time_raw (struct omap_rtc*,struct rtc_time*) ; 
 int rtc_read (struct omap_rtc*,int /*<<< orphan*/ ) ; 
 int rtc_readl (struct omap_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned long,struct rtc_time*) ; 
 unsigned long rtc_tm_to_time64 (struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_wait_not_busy (struct omap_rtc*) ; 
 int /*<<< orphan*/  rtc_write (struct omap_rtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_writel (struct omap_rtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct omap_rtc*) ; 
 int /*<<< orphan*/  stub2 (struct omap_rtc*) ; 
 int /*<<< orphan*/  tm2bcd (struct rtc_time*) ; 

int omap_rtc_power_off_program(struct device *dev)
{
	struct omap_rtc *rtc = omap_rtc_power_off_rtc;
	struct rtc_time tm;
	unsigned long now;
	int seconds;
	u32 val;

	rtc->type->unlock(rtc);
	/* enable pmic_power_en control */
	val = rtc_readl(rtc, OMAP_RTC_PMIC_REG);
	rtc_writel(rtc, OMAP_RTC_PMIC_REG, val | OMAP_RTC_PMIC_POWER_EN_EN);

again:
	/* Clear any existing ALARM2 event */
	rtc_writel(rtc, OMAP_RTC_STATUS_REG, OMAP_RTC_STATUS_ALARM2);

	/* set alarm one second from now */
	omap_rtc_read_time_raw(rtc, &tm);
	seconds = tm.tm_sec;
	bcd2tm(&tm);
	now = rtc_tm_to_time64(&tm);
	rtc_time64_to_tm(now + 1, &tm);

	tm2bcd(&tm);

	rtc_wait_not_busy(rtc);

	rtc_write(rtc, OMAP_RTC_ALARM2_SECONDS_REG, tm.tm_sec);
	rtc_write(rtc, OMAP_RTC_ALARM2_MINUTES_REG, tm.tm_min);
	rtc_write(rtc, OMAP_RTC_ALARM2_HOURS_REG, tm.tm_hour);
	rtc_write(rtc, OMAP_RTC_ALARM2_DAYS_REG, tm.tm_mday);
	rtc_write(rtc, OMAP_RTC_ALARM2_MONTHS_REG, tm.tm_mon);
	rtc_write(rtc, OMAP_RTC_ALARM2_YEARS_REG, tm.tm_year);

	/*
	 * enable ALARM2 interrupt
	 *
	 * NOTE: this fails on AM3352 if rtc_write (writeb) is used
	 */
	val = rtc_read(rtc, OMAP_RTC_INTERRUPTS_REG);
	rtc_writel(rtc, OMAP_RTC_INTERRUPTS_REG,
			val | OMAP_RTC_INTERRUPTS_IT_ALARM2);

	/* Retry in case roll over happened before alarm was armed. */
	if (rtc_read(rtc, OMAP_RTC_SECONDS_REG) != seconds) {
		val = rtc_read(rtc, OMAP_RTC_STATUS_REG);
		if (!(val & OMAP_RTC_STATUS_ALARM2))
			goto again;
	}

	rtc->type->lock(rtc);

	return 0;
}