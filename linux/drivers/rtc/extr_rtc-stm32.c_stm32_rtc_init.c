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
struct stm32_rtc_registers {int /*<<< orphan*/  cr; int /*<<< orphan*/  prer; } ;
struct stm32_rtc {scalar_t__ base; int /*<<< orphan*/  rtc_ck; TYPE_1__* data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct stm32_rtc_registers regs; } ;

/* Variables and functions */
 unsigned int STM32_RTC_CR_FMT ; 
 unsigned int STM32_RTC_PRER_PRED_A ; 
 unsigned int STM32_RTC_PRER_PRED_A_SHIFT ; 
 unsigned int STM32_RTC_PRER_PRED_S ; 
 unsigned int STM32_RTC_PRER_PRED_S_SHIFT ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char*) ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 int stm32_rtc_enter_init_mode (struct stm32_rtc*) ; 
 int /*<<< orphan*/  stm32_rtc_exit_init_mode (struct stm32_rtc*) ; 
 int stm32_rtc_wait_sync (struct stm32_rtc*) ; 
 int /*<<< orphan*/  stm32_rtc_wpr_lock (struct stm32_rtc*) ; 
 int /*<<< orphan*/  stm32_rtc_wpr_unlock (struct stm32_rtc*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static int stm32_rtc_init(struct platform_device *pdev,
			  struct stm32_rtc *rtc)
{
	const struct stm32_rtc_registers *regs = &rtc->data->regs;
	unsigned int prer, pred_a, pred_s, pred_a_max, pred_s_max, cr;
	unsigned int rate;
	int ret = 0;

	rate = clk_get_rate(rtc->rtc_ck);

	/* Find prediv_a and prediv_s to obtain the 1Hz calendar clock */
	pred_a_max = STM32_RTC_PRER_PRED_A >> STM32_RTC_PRER_PRED_A_SHIFT;
	pred_s_max = STM32_RTC_PRER_PRED_S >> STM32_RTC_PRER_PRED_S_SHIFT;

	for (pred_a = pred_a_max; pred_a + 1 > 0; pred_a--) {
		pred_s = (rate / (pred_a + 1)) - 1;

		if (((pred_s + 1) * (pred_a + 1)) == rate)
			break;
	}

	/*
	 * Can't find a 1Hz, so give priority to RTC power consumption
	 * by choosing the higher possible value for prediv_a
	 */
	if ((pred_s > pred_s_max) || (pred_a > pred_a_max)) {
		pred_a = pred_a_max;
		pred_s = (rate / (pred_a + 1)) - 1;

		dev_warn(&pdev->dev, "rtc_ck is %s\n",
			 (rate < ((pred_a + 1) * (pred_s + 1))) ?
			 "fast" : "slow");
	}

	stm32_rtc_wpr_unlock(rtc);

	ret = stm32_rtc_enter_init_mode(rtc);
	if (ret) {
		dev_err(&pdev->dev,
			"Can't enter in init mode. Prescaler config failed.\n");
		goto end;
	}

	prer = (pred_s << STM32_RTC_PRER_PRED_S_SHIFT) & STM32_RTC_PRER_PRED_S;
	writel_relaxed(prer, rtc->base + regs->prer);
	prer |= (pred_a << STM32_RTC_PRER_PRED_A_SHIFT) & STM32_RTC_PRER_PRED_A;
	writel_relaxed(prer, rtc->base + regs->prer);

	/* Force 24h time format */
	cr = readl_relaxed(rtc->base + regs->cr);
	cr &= ~STM32_RTC_CR_FMT;
	writel_relaxed(cr, rtc->base + regs->cr);

	stm32_rtc_exit_init_mode(rtc);

	ret = stm32_rtc_wait_sync(rtc);
end:
	stm32_rtc_wpr_lock(rtc);

	return ret;
}