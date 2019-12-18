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
struct ts4800_wdt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS4800_WDT_DISABLE ; 
 int /*<<< orphan*/  ts4800_write_feed (struct ts4800_wdt*,int /*<<< orphan*/ ) ; 
 struct ts4800_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int ts4800_wdt_stop(struct watchdog_device *wdd)
{
	struct ts4800_wdt *wdt = watchdog_get_drvdata(wdd);

	ts4800_write_feed(wdt, TS4800_WDT_DISABLE);
	return 0;
}