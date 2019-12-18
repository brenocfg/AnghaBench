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
struct retu_wdt_dev {int /*<<< orphan*/  ping_work; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct watchdog_device* platform_get_drvdata (struct platform_device*) ; 
 struct retu_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (struct watchdog_device*) ; 

__attribute__((used)) static int retu_wdt_remove(struct platform_device *pdev)
{
	struct watchdog_device *wdog = platform_get_drvdata(pdev);
	struct retu_wdt_dev *wdev = watchdog_get_drvdata(wdog);

	watchdog_unregister_device(wdog);
	cancel_delayed_work_sync(&wdev->ping_work);

	return 0;
}