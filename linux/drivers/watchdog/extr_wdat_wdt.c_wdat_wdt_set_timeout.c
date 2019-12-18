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
struct wdat_wdt {unsigned int period; } ;
struct watchdog_device {unsigned int timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_WDAT_SET_COUNTDOWN ; 
 struct wdat_wdt* to_wdat_wdt (struct watchdog_device*) ; 
 int wdat_wdt_run_action (struct wdat_wdt*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wdat_wdt_set_timeout(struct watchdog_device *wdd,
				unsigned int timeout)
{
	struct wdat_wdt *wdat = to_wdat_wdt(wdd);
	unsigned int periods;
	int ret;

	periods = timeout * 1000 / wdat->period;
	ret = wdat_wdt_run_action(wdat, ACPI_WDAT_SET_COUNTDOWN, periods, NULL);
	if (!ret)
		wdd->timeout = timeout;
	return ret;
}