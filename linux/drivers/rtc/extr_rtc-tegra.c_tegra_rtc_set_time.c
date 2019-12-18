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
struct tegra_rtc_info {scalar_t__ base; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TEGRA_RTC_REG_SECONDS ; 
 struct tegra_rtc_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_tm_to_time64 (struct rtc_time*) ; 
 int tegra_rtc_wait_while_busy (struct device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tegra_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct tegra_rtc_info *info = dev_get_drvdata(dev);
	u32 sec;
	int ret;

	/* convert tm to seconds */
	sec = rtc_tm_to_time64(tm);

	dev_vdbg(dev, "time set to %u, %ptR\n", sec, tm);

	/* seconds only written if wait succeeded */
	ret = tegra_rtc_wait_while_busy(dev);
	if (!ret)
		writel(sec, info->base + TEGRA_RTC_REG_SECONDS);

	dev_vdbg(dev, "time read back as %d\n",
		 readl(info->base + TEGRA_RTC_REG_SECONDS));

	return ret;
}