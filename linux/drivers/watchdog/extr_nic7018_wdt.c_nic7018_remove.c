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
struct platform_device {int dummy; } ;
struct nic7018_wdt {scalar_t__ io_base; int /*<<< orphan*/  wdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK ; 
 scalar_t__ WDT_REG_LOCK ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 struct nic7018_wdt* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nic7018_remove(struct platform_device *pdev)
{
	struct nic7018_wdt *wdt = platform_get_drvdata(pdev);

	watchdog_unregister_device(&wdt->wdd);

	/* Lock WDT register */
	outb(LOCK, wdt->io_base + WDT_REG_LOCK);

	return 0;
}