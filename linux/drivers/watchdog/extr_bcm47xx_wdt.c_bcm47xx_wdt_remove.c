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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct bcm47xx_wdt {int /*<<< orphan*/  wdd; } ;

/* Variables and functions */
 struct bcm47xx_wdt* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm47xx_wdt_remove(struct platform_device *pdev)
{
	struct bcm47xx_wdt *wdt = dev_get_platdata(&pdev->dev);

	watchdog_unregister_device(&wdt->wdd);

	return 0;
}