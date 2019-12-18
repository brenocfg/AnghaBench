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
struct stm32_rtc_registers {scalar_t__ sr; int /*<<< orphan*/  cr; int /*<<< orphan*/  alrmar; } ;
struct stm32_rtc_events {unsigned int alra; } ;
struct stm32_rtc {scalar_t__ base; TYPE_1__* data; } ;
struct rtc_time {int tm_mday; int tm_wday; int tm_hour; int tm_min; int tm_sec; } ;
struct rtc_wkalrm {int enabled; int pending; struct rtc_time time; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct stm32_rtc_events events; struct stm32_rtc_registers regs; } ;

/* Variables and functions */
 unsigned int STM32_RTC_ALRMXR_DATE ; 
 unsigned int STM32_RTC_ALRMXR_DATE_MASK ; 
 unsigned int STM32_RTC_ALRMXR_DATE_SHIFT ; 
 unsigned int STM32_RTC_ALRMXR_HOUR ; 
 unsigned int STM32_RTC_ALRMXR_HOUR_MASK ; 
 unsigned int STM32_RTC_ALRMXR_HOUR_SHIFT ; 
 unsigned int STM32_RTC_ALRMXR_MIN ; 
 unsigned int STM32_RTC_ALRMXR_MIN_MASK ; 
 unsigned int STM32_RTC_ALRMXR_MIN_SHIFT ; 
 unsigned int STM32_RTC_ALRMXR_PM ; 
 unsigned int STM32_RTC_ALRMXR_SEC ; 
 unsigned int STM32_RTC_ALRMXR_SEC_MASK ; 
 unsigned int STM32_RTC_ALRMXR_SEC_SHIFT ; 
 unsigned int STM32_RTC_ALRMXR_WDAY ; 
 unsigned int STM32_RTC_ALRMXR_WDAY_SHIFT ; 
 unsigned int STM32_RTC_ALRMXR_WDSEL ; 
 unsigned int STM32_RTC_CR_ALRAE ; 
 int /*<<< orphan*/  bcd2tm (struct rtc_time*) ; 
 struct stm32_rtc* dev_get_drvdata (struct device*) ; 
 unsigned int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int stm32_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct stm32_rtc *rtc = dev_get_drvdata(dev);
	const struct stm32_rtc_registers *regs = &rtc->data->regs;
	const struct stm32_rtc_events *evts = &rtc->data->events;
	struct rtc_time *tm = &alrm->time;
	unsigned int alrmar, cr, status;

	alrmar = readl_relaxed(rtc->base + regs->alrmar);
	cr = readl_relaxed(rtc->base + regs->cr);
	status = readl_relaxed(rtc->base + regs->sr);

	if (alrmar & STM32_RTC_ALRMXR_DATE_MASK) {
		/*
		 * Date/day doesn't matter in Alarm comparison so alarm
		 * triggers every day
		 */
		tm->tm_mday = -1;
		tm->tm_wday = -1;
	} else {
		if (alrmar & STM32_RTC_ALRMXR_WDSEL) {
			/* Alarm is set to a day of week */
			tm->tm_mday = -1;
			tm->tm_wday = (alrmar & STM32_RTC_ALRMXR_WDAY) >>
				      STM32_RTC_ALRMXR_WDAY_SHIFT;
			tm->tm_wday %= 7;
		} else {
			/* Alarm is set to a day of month */
			tm->tm_wday = -1;
			tm->tm_mday = (alrmar & STM32_RTC_ALRMXR_DATE) >>
				       STM32_RTC_ALRMXR_DATE_SHIFT;
		}
	}

	if (alrmar & STM32_RTC_ALRMXR_HOUR_MASK) {
		/* Hours don't matter in Alarm comparison */
		tm->tm_hour = -1;
	} else {
		tm->tm_hour = (alrmar & STM32_RTC_ALRMXR_HOUR) >>
			       STM32_RTC_ALRMXR_HOUR_SHIFT;
		if (alrmar & STM32_RTC_ALRMXR_PM)
			tm->tm_hour += 12;
	}

	if (alrmar & STM32_RTC_ALRMXR_MIN_MASK) {
		/* Minutes don't matter in Alarm comparison */
		tm->tm_min = -1;
	} else {
		tm->tm_min = (alrmar & STM32_RTC_ALRMXR_MIN) >>
			      STM32_RTC_ALRMXR_MIN_SHIFT;
	}

	if (alrmar & STM32_RTC_ALRMXR_SEC_MASK) {
		/* Seconds don't matter in Alarm comparison */
		tm->tm_sec = -1;
	} else {
		tm->tm_sec = (alrmar & STM32_RTC_ALRMXR_SEC) >>
			      STM32_RTC_ALRMXR_SEC_SHIFT;
	}

	bcd2tm(tm);

	alrm->enabled = (cr & STM32_RTC_CR_ALRAE) ? 1 : 0;
	alrm->pending = (status & evts->alra) ? 1 : 0;

	return 0;
}