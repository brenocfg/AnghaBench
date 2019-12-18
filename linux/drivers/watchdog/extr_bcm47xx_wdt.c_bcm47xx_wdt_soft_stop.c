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
struct bcm47xx_wdt {int /*<<< orphan*/  (* timer_set ) (struct bcm47xx_wdt*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  soft_timer; } ;

/* Variables and functions */
 struct bcm47xx_wdt* bcm47xx_wdt_get (struct watchdog_device*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bcm47xx_wdt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm47xx_wdt_soft_stop(struct watchdog_device *wdd)
{
	struct bcm47xx_wdt *wdt = bcm47xx_wdt_get(wdd);

	del_timer_sync(&wdt->soft_timer);
	wdt->timer_set(wdt, 0);

	return 0;
}