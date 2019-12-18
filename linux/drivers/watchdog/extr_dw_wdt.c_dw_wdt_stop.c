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
struct watchdog_device {int /*<<< orphan*/  status; } ;
struct dw_wdt {int /*<<< orphan*/  rst; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dw_wdt* to_dw_wdt (struct watchdog_device*) ; 

__attribute__((used)) static int dw_wdt_stop(struct watchdog_device *wdd)
{
	struct dw_wdt *dw_wdt = to_dw_wdt(wdd);

	if (!dw_wdt->rst) {
		set_bit(WDOG_HW_RUNNING, &wdd->status);
		return 0;
	}

	reset_control_assert(dw_wdt->rst);
	reset_control_deassert(dw_wdt->rst);

	return 0;
}