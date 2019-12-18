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
struct twl_rtc {int wake_enabled; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_RTC_INTERRUPTS_REG_IT_ALARM_M ; 
 struct twl_rtc* dev_get_drvdata (struct device*) ; 
 scalar_t__ device_can_wakeup (struct device*) ; 
 int /*<<< orphan*/  disable_irq_wake (int) ; 
 int /*<<< orphan*/  enable_irq_wake (int) ; 
 int mask_rtc_irq_bit (struct twl_rtc*,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int set_rtc_irq_bit (struct twl_rtc*,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int twl_rtc_alarm_irq_enable(struct device *dev, unsigned enabled)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct twl_rtc *twl_rtc = dev_get_drvdata(dev);
	int irq = platform_get_irq(pdev, 0);
	int ret;

	if (enabled) {
		ret = set_rtc_irq_bit(twl_rtc,
				      BIT_RTC_INTERRUPTS_REG_IT_ALARM_M);
		if (device_can_wakeup(dev) && !twl_rtc->wake_enabled) {
			enable_irq_wake(irq);
			twl_rtc->wake_enabled = true;
		}
	} else {
		ret = mask_rtc_irq_bit(twl_rtc,
				       BIT_RTC_INTERRUPTS_REG_IT_ALARM_M);
		if (twl_rtc->wake_enabled) {
			disable_irq_wake(irq);
			twl_rtc->wake_enabled = false;
		}
	}

	return ret;
}