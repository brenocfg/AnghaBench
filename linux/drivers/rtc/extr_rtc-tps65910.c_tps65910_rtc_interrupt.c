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
struct tps65910_rtc {int /*<<< orphan*/  rtc; } ;
struct tps65910 {int /*<<< orphan*/  regmap; } ;
struct device {struct device* parent; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 int /*<<< orphan*/  TPS65910_RTC_STATUS ; 
 int TPS65910_RTC_STATUS_ALARM ; 
 void* dev_get_drvdata (struct device*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static irqreturn_t tps65910_rtc_interrupt(int irq, void *rtc)
{
	struct device *dev = rtc;
	unsigned long events = 0;
	struct tps65910 *tps = dev_get_drvdata(dev->parent);
	struct tps65910_rtc *tps_rtc = dev_get_drvdata(dev);
	int ret;
	u32 rtc_reg;

	ret = regmap_read(tps->regmap, TPS65910_RTC_STATUS, &rtc_reg);
	if (ret)
		return IRQ_NONE;

	if (rtc_reg & TPS65910_RTC_STATUS_ALARM)
		events = RTC_IRQF | RTC_AF;

	ret = regmap_write(tps->regmap, TPS65910_RTC_STATUS, rtc_reg);
	if (ret)
		return IRQ_NONE;

	/* Notify RTC core on event */
	rtc_update_irq(tps_rtc->rtc, 1, events);

	return IRQ_HANDLED;
}