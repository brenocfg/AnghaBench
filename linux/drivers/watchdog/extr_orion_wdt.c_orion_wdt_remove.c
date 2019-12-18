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
struct platform_device {int dummy; } ;
struct orion_watchdog {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 struct watchdog_device* platform_get_drvdata (struct platform_device*) ; 
 struct orion_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (struct watchdog_device*) ; 

__attribute__((used)) static int orion_wdt_remove(struct platform_device *pdev)
{
	struct watchdog_device *wdt_dev = platform_get_drvdata(pdev);
	struct orion_watchdog *dev = watchdog_get_drvdata(wdt_dev);

	watchdog_unregister_device(wdt_dev);
	clk_disable_unprepare(dev->clk);
	clk_put(dev->clk);
	return 0;
}