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
struct watchdog_device {int timeout; } ;
struct aspeed_wdt {int dummy; } ;

/* Variables and functions */
 int WDT_RATE_1MHZ ; 
 int /*<<< orphan*/  aspeed_wdt_enable (struct aspeed_wdt*,int) ; 
 struct aspeed_wdt* to_aspeed_wdt (struct watchdog_device*) ; 

__attribute__((used)) static int aspeed_wdt_start(struct watchdog_device *wdd)
{
	struct aspeed_wdt *wdt = to_aspeed_wdt(wdd);

	aspeed_wdt_enable(wdt, wdd->timeout * WDT_RATE_1MHZ);

	return 0;
}