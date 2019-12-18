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
struct wdat_wdt {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_WDAT_SET_REBOOT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int wdat_wdt_run_action (struct wdat_wdt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wdat_wdt_enable_reboot(struct wdat_wdt *wdat)
{
	int ret;

	/*
	 * WDAT specification says that the watchdog is required to reboot
	 * the system when it fires. However, it also states that it is
	 * recommeded to make it configurable through hardware register. We
	 * enable reboot now if it is configrable, just in case.
	 */
	ret = wdat_wdt_run_action(wdat, ACPI_WDAT_SET_REBOOT, 0, NULL);
	if (ret && ret != -EOPNOTSUPP) {
		dev_err(&wdat->pdev->dev,
			"Failed to enable reboot when watchdog triggers\n");
		return ret;
	}

	return 0;
}