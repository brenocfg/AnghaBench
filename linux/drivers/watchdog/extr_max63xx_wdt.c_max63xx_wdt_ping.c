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
struct max63xx_wdt {int /*<<< orphan*/  (* ping ) (struct max63xx_wdt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct max63xx_wdt*) ; 
 struct max63xx_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int max63xx_wdt_ping(struct watchdog_device *wdd)
{
	struct max63xx_wdt *wdt = watchdog_get_drvdata(wdd);

	wdt->ping(wdt);
	return 0;
}