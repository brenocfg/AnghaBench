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
typedef  int u32 ;
struct rc5t583_rtc {int /*<<< orphan*/  rtc; } ;
struct rc5t583 {int /*<<< orphan*/  regmap; } ;
struct device {struct device* parent; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int GET_YAL_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  RC5T583_RTC_CTL2 ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 void* dev_get_drvdata (struct device*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static irqreturn_t rc5t583_rtc_interrupt(int irq, void *rtc)
{
	struct device *dev = rtc;
	struct rc5t583 *rc5t583 = dev_get_drvdata(dev->parent);
	struct rc5t583_rtc *rc5t583_rtc = dev_get_drvdata(dev);
	unsigned long events = 0;
	int ret;
	u32 rtc_reg;

	ret = regmap_read(rc5t583->regmap, RC5T583_RTC_CTL2, &rtc_reg);
	if (ret < 0)
		return IRQ_NONE;

	if (rtc_reg & GET_YAL_STATUS) {
		events = RTC_IRQF | RTC_AF;
		/* clear pending Y-alarm interrupt bit */
		rtc_reg &= ~GET_YAL_STATUS;
	}

	ret = regmap_write(rc5t583->regmap, RC5T583_RTC_CTL2, rtc_reg);
	if (ret)
		return IRQ_NONE;

	/* Notify RTC core on event */
	rtc_update_irq(rc5t583_rtc->rtc, 1, events);

	return IRQ_HANDLED;
}