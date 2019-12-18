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
typedef  unsigned int u32 ;
struct watchdog_device {int dummy; } ;
struct bcm7038_watchdog {unsigned int rate; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ WDT_CMD_REG ; 
 unsigned int readl (scalar_t__) ; 
 struct bcm7038_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int bcm7038_wdt_get_timeleft(struct watchdog_device *wdog)
{
	struct bcm7038_watchdog *wdt = watchdog_get_drvdata(wdog);
	u32 time_left;

	time_left = readl(wdt->base + WDT_CMD_REG);

	return time_left / wdt->rate;
}