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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_rtc_info {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_RTC_INTR_MASK_SEC_ALARM0 ; 
 scalar_t__ TEGRA_RTC_REG_INTR_MASK ; 
 struct tegra_rtc_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tegra_rtc_wait_while_busy (struct device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tegra_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct tegra_rtc_info *info = dev_get_drvdata(dev);
	unsigned long flags;
	u32 status;

	tegra_rtc_wait_while_busy(dev);
	spin_lock_irqsave(&info->lock, flags);

	/* read the original value, and OR in the flag */
	status = readl(info->base + TEGRA_RTC_REG_INTR_MASK);
	if (enabled)
		status |= TEGRA_RTC_INTR_MASK_SEC_ALARM0; /* set it */
	else
		status &= ~TEGRA_RTC_INTR_MASK_SEC_ALARM0; /* clear it */

	writel(status, info->base + TEGRA_RTC_REG_INTR_MASK);

	spin_unlock_irqrestore(&info->lock, flags);

	return 0;
}