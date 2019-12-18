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
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TEGRA_RTC_REG_MILLI_SECONDS ; 
 scalar_t__ TEGRA_RTC_REG_SHADOW_SECONDS ; 
 struct tegra_rtc_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*,int /*<<< orphan*/ ,struct rtc_time*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int tegra_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct tegra_rtc_info *info = dev_get_drvdata(dev);
	unsigned long flags;
	u32 sec, msec;

	/*
	 * RTC hardware copies seconds to shadow seconds when a read of
	 * milliseconds occurs. use a lock to keep other threads out.
	 */
	spin_lock_irqsave(&info->lock, flags);

	msec = readl(info->base + TEGRA_RTC_REG_MILLI_SECONDS);
	sec = readl(info->base + TEGRA_RTC_REG_SHADOW_SECONDS);

	spin_unlock_irqrestore(&info->lock, flags);

	rtc_time64_to_tm(sec, tm);

	dev_vdbg(dev, "time read as %u, %ptR\n", sec, tm);

	return 0;
}