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
struct cdns_wdt {int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_WDT_RESTART_KEY ; 
 int /*<<< orphan*/  CDNS_WDT_RESTART_OFFSET ; 
 int /*<<< orphan*/  cdns_wdt_writereg (struct cdns_wdt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct cdns_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int cdns_wdt_reload(struct watchdog_device *wdd)
{
	struct cdns_wdt *wdt = watchdog_get_drvdata(wdd);

	spin_lock(&wdt->io_lock);
	cdns_wdt_writereg(wdt, CDNS_WDT_RESTART_OFFSET,
			  CDNS_WDT_RESTART_KEY);
	spin_unlock(&wdt->io_lock);

	return 0;
}