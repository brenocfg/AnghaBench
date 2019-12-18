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
struct stm32_rtc_registers {int /*<<< orphan*/  cr; } ;
struct stm32_rtc_events {int /*<<< orphan*/  alra; } ;
struct stm32_rtc {scalar_t__ base; TYPE_1__* data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct stm32_rtc_events events; struct stm32_rtc_registers regs; } ;

/* Variables and functions */
 unsigned int STM32_RTC_CR_ALRAE ; 
 unsigned int STM32_RTC_CR_ALRAIE ; 
 struct stm32_rtc* dev_get_drvdata (struct device*) ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  stm32_rtc_clear_event_flags (struct stm32_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_rtc_wpr_lock (struct stm32_rtc*) ; 
 int /*<<< orphan*/  stm32_rtc_wpr_unlock (struct stm32_rtc*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static int stm32_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct stm32_rtc *rtc = dev_get_drvdata(dev);
	const struct stm32_rtc_registers *regs = &rtc->data->regs;
	const struct stm32_rtc_events *evts = &rtc->data->events;
	unsigned int cr;

	cr = readl_relaxed(rtc->base + regs->cr);

	stm32_rtc_wpr_unlock(rtc);

	/* We expose Alarm A to the kernel */
	if (enabled)
		cr |= (STM32_RTC_CR_ALRAIE | STM32_RTC_CR_ALRAE);
	else
		cr &= ~(STM32_RTC_CR_ALRAIE | STM32_RTC_CR_ALRAE);
	writel_relaxed(cr, rtc->base + regs->cr);

	/* Clear event flags, otherwise new events won't be received */
	stm32_rtc_clear_event_flags(rtc, evts->alra);

	stm32_rtc_wpr_lock(rtc);

	return 0;
}