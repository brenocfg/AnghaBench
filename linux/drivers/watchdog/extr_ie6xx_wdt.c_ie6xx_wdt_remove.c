#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ sch_wdtba; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_IO ; 
 TYPE_1__ ie6xx_wdt_data ; 
 int /*<<< orphan*/  ie6xx_wdt_debugfs_exit () ; 
 int /*<<< orphan*/  ie6xx_wdt_dev ; 
 int /*<<< orphan*/  ie6xx_wdt_stop (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ie6xx_wdt_remove(struct platform_device *pdev)
{
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	ie6xx_wdt_stop(NULL);
	watchdog_unregister_device(&ie6xx_wdt_dev);
	ie6xx_wdt_debugfs_exit();
	release_region(res->start, resource_size(res));
	ie6xx_wdt_data.sch_wdtba = 0;

	return 0;
}