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
struct tegra_rtc_info {int /*<<< orphan*/  rtc; int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 unsigned long RTC_PF ; 
 int TEGRA_RTC_INTR_STATUS_SEC_ALARM0 ; 
 int TEGRA_RTC_INTR_STATUS_SEC_CDN_ALARM ; 
 scalar_t__ TEGRA_RTC_REG_INTR_MASK ; 
 scalar_t__ TEGRA_RTC_REG_INTR_STATUS ; 
 struct tegra_rtc_info* dev_get_drvdata (struct device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tegra_rtc_wait_while_busy (struct device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t tegra_rtc_irq_handler(int irq, void *data)
{
	struct device *dev = data;
	struct tegra_rtc_info *info = dev_get_drvdata(dev);
	unsigned long events = 0, flags;
	u32 status;

	status = readl(info->base + TEGRA_RTC_REG_INTR_STATUS);
	if (status) {
		/* clear the interrupt masks and status on any IRQ */
		tegra_rtc_wait_while_busy(dev);

		spin_lock_irqsave(&info->lock, flags);
		writel(0, info->base + TEGRA_RTC_REG_INTR_MASK);
		writel(status, info->base + TEGRA_RTC_REG_INTR_STATUS);
		spin_unlock_irqrestore(&info->lock, flags);
	}

	/* check if alarm */
	if (status & TEGRA_RTC_INTR_STATUS_SEC_ALARM0)
		events |= RTC_IRQF | RTC_AF;

	/* check if periodic */
	if (status & TEGRA_RTC_INTR_STATUS_SEC_CDN_ALARM)
		events |= RTC_IRQF | RTC_PF;

	rtc_update_irq(info->rtc, 1, events);

	return IRQ_HANDLED;
}