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
struct wdtbd70528 {int /*<<< orphan*/  dev; } ;
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int bd70528_wdt_change (struct wdtbd70528*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct wdtbd70528* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int bd70528_wdt_stop(struct watchdog_device *wdt)
{
	struct wdtbd70528 *w = watchdog_get_drvdata(wdt);

	dev_dbg(w->dev, "WDT stopping...\n");
	return bd70528_wdt_change(w, 0);
}