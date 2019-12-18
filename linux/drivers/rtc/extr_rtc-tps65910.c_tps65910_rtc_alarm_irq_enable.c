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
typedef  int /*<<< orphan*/  u8 ;
struct tps65910 {int /*<<< orphan*/  regmap; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS65910_RTC_INTERRUPTS ; 
 int /*<<< orphan*/  TPS65910_RTC_INTERRUPTS_IT_ALARM ; 
 struct tps65910* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65910_rtc_alarm_irq_enable(struct device *dev,
					 unsigned int enabled)
{
	struct tps65910 *tps = dev_get_drvdata(dev->parent);
	u8 val = 0;

	if (enabled)
		val = TPS65910_RTC_INTERRUPTS_IT_ALARM;

	return regmap_write(tps->regmap, TPS65910_RTC_INTERRUPTS, val);
}