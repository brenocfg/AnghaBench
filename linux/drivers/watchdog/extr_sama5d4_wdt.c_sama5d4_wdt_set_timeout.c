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
typedef  int /*<<< orphan*/  u32 ;
struct watchdog_device {unsigned int timeout; } ;
struct sama5d4_wdt {int mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_WDT_MR ; 
 int AT91_WDT_SET_WDV (int /*<<< orphan*/ ) ; 
 int AT91_WDT_WDDIS ; 
 int AT91_WDT_WDV ; 
 int /*<<< orphan*/  WDT_SEC2TICKS (unsigned int) ; 
 struct sama5d4_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 scalar_t__ wdt_enabled ; 
 int /*<<< orphan*/  wdt_write (struct sama5d4_wdt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sama5d4_wdt_set_timeout(struct watchdog_device *wdd,
				 unsigned int timeout)
{
	struct sama5d4_wdt *wdt = watchdog_get_drvdata(wdd);
	u32 value = WDT_SEC2TICKS(timeout);

	wdt->mr &= ~AT91_WDT_WDV;
	wdt->mr |= AT91_WDT_SET_WDV(value);

	/*
	 * WDDIS has to be 0 when updating WDD/WDV. The datasheet states: When
	 * setting the WDDIS bit, and while it is set, the fields WDV and WDD
	 * must not be modified.
	 * If the watchdog is enabled, then the timeout can be updated. Else,
	 * wait that the user enables it.
	 */
	if (wdt_enabled)
		wdt_write(wdt, AT91_WDT_MR, wdt->mr & ~AT91_WDT_WDDIS);

	wdd->timeout = timeout;

	return 0;
}