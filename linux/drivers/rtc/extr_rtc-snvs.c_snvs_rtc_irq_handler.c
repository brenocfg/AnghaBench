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
struct snvs_rtc_data {scalar_t__ clk; scalar_t__ offset; int /*<<< orphan*/  regmap; int /*<<< orphan*/  rtc; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 scalar_t__ SNVS_LPSR ; 
 int SNVS_LPSR_LPTA ; 
 int /*<<< orphan*/  clk_disable (scalar_t__) ; 
 int /*<<< orphan*/  clk_enable (scalar_t__) ; 
 struct snvs_rtc_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snvs_rtc_alarm_irq_enable (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t snvs_rtc_irq_handler(int irq, void *dev_id)
{
	struct device *dev = dev_id;
	struct snvs_rtc_data *data = dev_get_drvdata(dev);
	u32 lpsr;
	u32 events = 0;

	if (data->clk)
		clk_enable(data->clk);

	regmap_read(data->regmap, data->offset + SNVS_LPSR, &lpsr);

	if (lpsr & SNVS_LPSR_LPTA) {
		events |= (RTC_AF | RTC_IRQF);

		/* RTC alarm should be one-shot */
		snvs_rtc_alarm_irq_enable(dev, 0);

		rtc_update_irq(data->rtc, 1, events);
	}

	/* clear interrupt status */
	regmap_write(data->regmap, data->offset + SNVS_LPSR, lpsr);

	if (data->clk)
		clk_disable(data->clk);

	return events ? IRQ_HANDLED : IRQ_NONE;
}