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
struct stm32_rtc_registers {int /*<<< orphan*/  alrmar; int /*<<< orphan*/  isr; int /*<<< orphan*/  cr; } ;
struct stm32_rtc {scalar_t__ base; TYPE_1__* data; } ;
struct rtc_time {unsigned int tm_mday; unsigned int tm_hour; unsigned int tm_min; unsigned int tm_sec; } ;
struct rtc_wkalrm {int /*<<< orphan*/  enabled; struct rtc_time time; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct stm32_rtc_registers regs; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int STM32_RTC_ALRMXR_DATE ; 
 unsigned int STM32_RTC_ALRMXR_DATE_SHIFT ; 
 unsigned int STM32_RTC_ALRMXR_HOUR ; 
 unsigned int STM32_RTC_ALRMXR_HOUR_SHIFT ; 
 unsigned int STM32_RTC_ALRMXR_MIN ; 
 unsigned int STM32_RTC_ALRMXR_MIN_SHIFT ; 
 unsigned int STM32_RTC_ALRMXR_PM ; 
 unsigned int STM32_RTC_ALRMXR_SEC ; 
 unsigned int STM32_RTC_ALRMXR_SEC_SHIFT ; 
 unsigned int STM32_RTC_CR_ALRAE ; 
 unsigned int STM32_RTC_ISR_ALRAWF ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct stm32_rtc* dev_get_drvdata (struct device*) ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 int readl_relaxed_poll_timeout_atomic (scalar_t__,unsigned int,unsigned int,int,int) ; 
 int /*<<< orphan*/  stm32_rtc_alarm_irq_enable (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ stm32_rtc_valid_alrm (struct stm32_rtc*,struct rtc_time*) ; 
 int /*<<< orphan*/  stm32_rtc_wpr_lock (struct stm32_rtc*) ; 
 int /*<<< orphan*/  stm32_rtc_wpr_unlock (struct stm32_rtc*) ; 
 int /*<<< orphan*/  tm2bcd (struct rtc_time*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static int stm32_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct stm32_rtc *rtc = dev_get_drvdata(dev);
	const struct stm32_rtc_registers *regs = &rtc->data->regs;
	struct rtc_time *tm = &alrm->time;
	unsigned int cr, isr, alrmar;
	int ret = 0;

	tm2bcd(tm);

	/*
	 * RTC alarm can't be set on a specific date, unless this date is
	 * up to the same day of month next month.
	 */
	if (stm32_rtc_valid_alrm(rtc, tm) < 0) {
		dev_err(dev, "Alarm can be set only on upcoming month.\n");
		return -EINVAL;
	}

	alrmar = 0;
	/* tm_year and tm_mon are not used because not supported by RTC */
	alrmar |= (tm->tm_mday << STM32_RTC_ALRMXR_DATE_SHIFT) &
		  STM32_RTC_ALRMXR_DATE;
	/* 24-hour format */
	alrmar &= ~STM32_RTC_ALRMXR_PM;
	alrmar |= (tm->tm_hour << STM32_RTC_ALRMXR_HOUR_SHIFT) &
		  STM32_RTC_ALRMXR_HOUR;
	alrmar |= (tm->tm_min << STM32_RTC_ALRMXR_MIN_SHIFT) &
		  STM32_RTC_ALRMXR_MIN;
	alrmar |= (tm->tm_sec << STM32_RTC_ALRMXR_SEC_SHIFT) &
		  STM32_RTC_ALRMXR_SEC;

	stm32_rtc_wpr_unlock(rtc);

	/* Disable Alarm */
	cr = readl_relaxed(rtc->base + regs->cr);
	cr &= ~STM32_RTC_CR_ALRAE;
	writel_relaxed(cr, rtc->base + regs->cr);

	/*
	 * Poll Alarm write flag to be sure that Alarm update is allowed: it
	 * takes around 2 rtc_ck clock cycles
	 */
	ret = readl_relaxed_poll_timeout_atomic(rtc->base + regs->isr,
						isr,
						(isr & STM32_RTC_ISR_ALRAWF),
						10, 100000);

	if (ret) {
		dev_err(dev, "Alarm update not allowed\n");
		goto end;
	}

	/* Write to Alarm register */
	writel_relaxed(alrmar, rtc->base + regs->alrmar);

	stm32_rtc_alarm_irq_enable(dev, alrm->enabled);
end:
	stm32_rtc_wpr_lock(rtc);

	return ret;
}