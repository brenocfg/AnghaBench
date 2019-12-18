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
struct regmap {int dummy; } ;
struct ac100_rtc_dev {TYPE_1__* rtc; int /*<<< orphan*/  dev; struct regmap* regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  ops_lock; } ;

/* Variables and functions */
 unsigned int AC100_ALM_INT_ENABLE ; 
 int /*<<< orphan*/  AC100_ALM_INT_STA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int ac100_rtc_alarm_irq_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rtc_update_irq (TYPE_1__*,int,int) ; 

__attribute__((used)) static irqreturn_t ac100_rtc_irq(int irq, void *data)
{
	struct ac100_rtc_dev *chip = data;
	struct regmap *regmap = chip->regmap;
	unsigned int val = 0;
	int ret;

	mutex_lock(&chip->rtc->ops_lock);

	/* read status */
	ret = regmap_read(regmap, AC100_ALM_INT_STA, &val);
	if (ret)
		goto out;

	if (val & AC100_ALM_INT_ENABLE) {
		/* signal rtc framework */
		rtc_update_irq(chip->rtc, 1, RTC_AF | RTC_IRQF);

		/* clear status */
		ret = regmap_write(regmap, AC100_ALM_INT_STA, val);
		if (ret)
			goto out;

		/* disable interrupt */
		ret = ac100_rtc_alarm_irq_enable(chip->dev, 0);
		if (ret)
			goto out;
	}

out:
	mutex_unlock(&chip->rtc->ops_lock);
	return IRQ_HANDLED;
}