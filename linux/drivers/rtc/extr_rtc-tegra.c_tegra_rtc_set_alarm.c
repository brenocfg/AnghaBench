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
typedef  scalar_t__ u32 ;
struct tegra_rtc_info {scalar_t__ base; } ;
struct rtc_wkalrm {int /*<<< orphan*/  time; scalar_t__ enabled; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TEGRA_RTC_REG_SECONDS_ALARM0 ; 
 struct tegra_rtc_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ rtc_tm_to_time64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_rtc_alarm_irq_enable (struct device*,int) ; 
 int /*<<< orphan*/  tegra_rtc_wait_while_busy (struct device*) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int tegra_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct tegra_rtc_info *info = dev_get_drvdata(dev);
	u32 sec;

	if (alarm->enabled)
		sec = rtc_tm_to_time64(&alarm->time);
	else
		sec = 0;

	tegra_rtc_wait_while_busy(dev);
	writel(sec, info->base + TEGRA_RTC_REG_SECONDS_ALARM0);
	dev_vdbg(dev, "alarm read back as %d\n",
		 readl(info->base + TEGRA_RTC_REG_SECONDS_ALARM0));

	/* if successfully written and alarm is enabled ... */
	if (sec) {
		tegra_rtc_alarm_irq_enable(dev, 1);
		dev_vdbg(dev, "alarm set as %u, %ptR\n", sec, &alarm->time);
	} else {
		/* disable alarm if 0 or write error */
		dev_vdbg(dev, "alarm disabled\n");
		tegra_rtc_alarm_irq_enable(dev, 0);
	}

	return 0;
}