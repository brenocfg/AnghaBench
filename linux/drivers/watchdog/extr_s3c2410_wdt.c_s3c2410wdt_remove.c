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
struct s3c2410_wdt {int /*<<< orphan*/  clock; int /*<<< orphan*/  wdt_device; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct s3c2410_wdt* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  s3c2410wdt_cpufreq_deregister (struct s3c2410_wdt*) ; 
 int s3c2410wdt_mask_and_disable_reset (struct s3c2410_wdt*,int) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s3c2410wdt_remove(struct platform_device *dev)
{
	int ret;
	struct s3c2410_wdt *wdt = platform_get_drvdata(dev);

	ret = s3c2410wdt_mask_and_disable_reset(wdt, true);
	if (ret < 0)
		return ret;

	watchdog_unregister_device(&wdt->wdt_device);

	s3c2410wdt_cpufreq_deregister(wdt);

	clk_disable_unprepare(wdt->clock);

	return 0;
}