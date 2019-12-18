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
struct stmp3xxx_rtc_data {int /*<<< orphan*/  rtc; scalar_t__ io; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 scalar_t__ STMP3XXX_RTC_CTRL ; 
 int STMP3XXX_RTC_CTRL_ALARM_IRQ ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 struct stmp3xxx_rtc_data* dev_get_drvdata (void*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t stmp3xxx_rtc_interrupt(int irq, void *dev_id)
{
	struct stmp3xxx_rtc_data *rtc_data = dev_get_drvdata(dev_id);
	u32 status = readl(rtc_data->io + STMP3XXX_RTC_CTRL);

	if (status & STMP3XXX_RTC_CTRL_ALARM_IRQ) {
		writel(STMP3XXX_RTC_CTRL_ALARM_IRQ,
			rtc_data->io + STMP3XXX_RTC_CTRL + STMP_OFFSET_REG_CLR);
		rtc_update_irq(rtc_data->rtc, 1, RTC_AF | RTC_IRQF);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}