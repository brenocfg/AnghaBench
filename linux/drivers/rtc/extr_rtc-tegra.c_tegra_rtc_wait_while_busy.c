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
struct tegra_rtc_info {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct tegra_rtc_info* dev_get_drvdata (struct device*) ; 
 scalar_t__ tegra_rtc_check_busy (struct tegra_rtc_info*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tegra_rtc_wait_while_busy(struct device *dev)
{
	struct tegra_rtc_info *info = dev_get_drvdata(dev);
	int retries = 500; /* ~490 us is the worst case, ~250 us is best */

	/*
	 * First wait for the RTC to become busy. This is when it posts its
	 * updated seconds+msec registers to AHB side.
	 */
	while (tegra_rtc_check_busy(info)) {
		if (!retries--)
			goto retry_failed;

		udelay(1);
	}

	/* now we have about 250 us to manipulate registers */
	return 0;

retry_failed:
	dev_err(dev, "write failed: retry count exceeded\n");
	return -ETIMEDOUT;
}