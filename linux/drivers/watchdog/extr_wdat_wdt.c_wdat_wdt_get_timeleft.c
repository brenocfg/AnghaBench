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
typedef  int u32 ;
struct wdat_wdt {int period; } ;
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_WDAT_GET_CURRENT_COUNTDOWN ; 
 struct wdat_wdt* to_wdat_wdt (struct watchdog_device*) ; 
 int /*<<< orphan*/  wdat_wdt_run_action (struct wdat_wdt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned int wdat_wdt_get_timeleft(struct watchdog_device *wdd)
{
	struct wdat_wdt *wdat = to_wdat_wdt(wdd);
	u32 periods = 0;

	wdat_wdt_run_action(wdat, ACPI_WDAT_GET_CURRENT_COUNTDOWN, 0, &periods);
	return periods * wdat->period / 1000;
}