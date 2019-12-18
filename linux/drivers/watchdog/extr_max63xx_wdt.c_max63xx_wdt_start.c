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
struct watchdog_device {int dummy; } ;
struct max63xx_wdt {int /*<<< orphan*/  (* ping ) (struct max63xx_wdt*) ;TYPE_1__* timeout; int /*<<< orphan*/  (* set ) (struct max63xx_wdt*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {scalar_t__ tdelay; int /*<<< orphan*/  wdset; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct max63xx_wdt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct max63xx_wdt*) ; 
 struct max63xx_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int max63xx_wdt_start(struct watchdog_device *wdd)
{
	struct max63xx_wdt *wdt = watchdog_get_drvdata(wdd);

	wdt->set(wdt, wdt->timeout->wdset);

	/* check for a edge triggered startup */
	if (wdt->timeout->tdelay == 0)
		wdt->ping(wdt);
	return 0;
}