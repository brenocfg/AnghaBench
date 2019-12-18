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
struct nic7018_wdt {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ WDT_CTRL ; 
 scalar_t__ WDT_PRESET_PRESCALE ; 
 scalar_t__ WDT_RELOAD_CTRL ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 struct nic7018_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int nic7018_stop(struct watchdog_device *wdd)
{
	struct nic7018_wdt *wdt = watchdog_get_drvdata(wdd);

	outb(0, wdt->io_base + WDT_CTRL);
	outb(0, wdt->io_base + WDT_RELOAD_CTRL);
	outb(0xF0, wdt->io_base + WDT_PRESET_PRESCALE);

	return 0;
}