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
struct watchdog_device {int /*<<< orphan*/  timeout; } ;
struct TYPE_2__ {int /*<<< orphan*/  unlock_sequence; scalar_t__ sch_wdtba; } ;

/* Variables and functions */
 scalar_t__ WDTLR ; 
 int /*<<< orphan*/  WDT_ENABLE ; 
 TYPE_1__ ie6xx_wdt_data ; 
 int /*<<< orphan*/  ie6xx_wdt_set_timeout (struct watchdog_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ie6xx_wdt_start(struct watchdog_device *wdd)
{
	ie6xx_wdt_set_timeout(wdd, wdd->timeout);

	/* Enable the watchdog timer */
	spin_lock(&ie6xx_wdt_data.unlock_sequence);
	outb(WDT_ENABLE, ie6xx_wdt_data.sch_wdtba + WDTLR);
	spin_unlock(&ie6xx_wdt_data.unlock_sequence);

	return 0;
}