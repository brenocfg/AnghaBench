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
struct sp805_wdt {int /*<<< orphan*/  wdd; } ;
struct amba_device {int dummy; } ;

/* Variables and functions */
 struct sp805_wdt* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sp805_wdt_remove(struct amba_device *adev)
{
	struct sp805_wdt *wdt = amba_get_drvdata(adev);

	watchdog_unregister_device(&wdt->wdd);
	watchdog_set_drvdata(&wdt->wdd, NULL);

	return 0;
}