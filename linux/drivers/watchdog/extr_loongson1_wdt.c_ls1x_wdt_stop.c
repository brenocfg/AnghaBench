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
struct watchdog_device {int dummy; } ;
struct ls1x_wdt_drvdata {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ WDT_EN ; 
 struct ls1x_wdt_drvdata* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ls1x_wdt_stop(struct watchdog_device *wdt_dev)
{
	struct ls1x_wdt_drvdata *drvdata = watchdog_get_drvdata(wdt_dev);

	writel(0x0, drvdata->base + WDT_EN);

	return 0;
}