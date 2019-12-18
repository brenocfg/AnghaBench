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
struct watchdog_device {int timeout; } ;
struct tegra_wdt {scalar_t__ wdt_regs; } ;

/* Variables and functions */
 scalar_t__ WDT_STS ; 
 int WDT_STS_COUNT_MASK ; 
 int WDT_STS_COUNT_SHIFT ; 
 int WDT_STS_EXP_MASK ; 
 int WDT_STS_EXP_SHIFT ; 
 int readl (scalar_t__) ; 
 struct tegra_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int tegra_wdt_get_timeleft(struct watchdog_device *wdd)
{
	struct tegra_wdt *wdt = watchdog_get_drvdata(wdd);
	u32 val;
	int count;
	int exp;

	val = readl(wdt->wdt_regs + WDT_STS);

	/* Current countdown (from timeout) */
	count = (val >> WDT_STS_COUNT_SHIFT) & WDT_STS_COUNT_MASK;

	/* Number of expirations (we are waiting for the 4th expiration) */
	exp = (val >> WDT_STS_EXP_SHIFT) & WDT_STS_EXP_MASK;

	/*
	 * The entire thing is divided by 4 because we are ticking down 4 times
	 * faster due to needing to wait for the 4th expiration.
	 */
	return (((3 - exp) * wdd->timeout) + count) / 4;
}