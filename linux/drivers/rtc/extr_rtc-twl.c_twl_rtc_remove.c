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
struct twl_rtc {scalar_t__ class; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_RTC_INTERRUPTS_REG_IT_ALARM_M ; 
 int /*<<< orphan*/  BIT_RTC_INTERRUPTS_REG_IT_TIMER_M ; 
 int /*<<< orphan*/  REG_INT_MSK_LINE_A ; 
 int /*<<< orphan*/  REG_INT_MSK_STS_A ; 
 int /*<<< orphan*/  TWL6030_RTC_INT_MASK ; 
 scalar_t__ TWL_6030 ; 
 int /*<<< orphan*/  mask_rtc_irq_bit (struct twl_rtc*,int /*<<< orphan*/ ) ; 
 struct twl_rtc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  twl6030_interrupt_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl_rtc_remove(struct platform_device *pdev)
{
	struct twl_rtc *twl_rtc = platform_get_drvdata(pdev);

	/* leave rtc running, but disable irqs */
	mask_rtc_irq_bit(twl_rtc, BIT_RTC_INTERRUPTS_REG_IT_ALARM_M);
	mask_rtc_irq_bit(twl_rtc, BIT_RTC_INTERRUPTS_REG_IT_TIMER_M);
	if (twl_rtc->class == TWL_6030) {
		twl6030_interrupt_mask(TWL6030_RTC_INT_MASK,
			REG_INT_MSK_LINE_A);
		twl6030_interrupt_mask(TWL6030_RTC_INT_MASK,
			REG_INT_MSK_STS_A);
	}

	return 0;
}