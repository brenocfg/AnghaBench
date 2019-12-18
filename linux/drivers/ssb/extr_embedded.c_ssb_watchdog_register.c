#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wdt ;
struct TYPE_3__ {int /*<<< orphan*/  max_timer_ms; } ;
struct ssb_bus {struct platform_device* watchdog; int /*<<< orphan*/  busnumber; TYPE_1__ extif; TYPE_1__ chipco; } ;
struct platform_device {int dummy; } ;
struct bcm47xx_wdt {int /*<<< orphan*/  max_timer_ms; int /*<<< orphan*/  timer_set_ms; int /*<<< orphan*/  timer_set; TYPE_1__* driver_data; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int PTR_ERR (struct platform_device*) ; 
 int /*<<< orphan*/  SSB_EXTIF_WATCHDOG_MAX_TIMER_MS ; 
 struct platform_device* platform_device_register_data (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct bcm47xx_wdt*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 scalar_t__ ssb_chipco_available (TYPE_1__*) ; 
 int /*<<< orphan*/  ssb_chipco_watchdog_timer_set_ms ; 
 int /*<<< orphan*/  ssb_chipco_watchdog_timer_set_wdt ; 
 scalar_t__ ssb_extif_available (TYPE_1__*) ; 
 int /*<<< orphan*/  ssb_extif_watchdog_timer_set_ms ; 
 int /*<<< orphan*/  ssb_extif_watchdog_timer_set_wdt ; 

int ssb_watchdog_register(struct ssb_bus *bus)
{
	struct bcm47xx_wdt wdt = {};
	struct platform_device *pdev;

	if (ssb_chipco_available(&bus->chipco)) {
		wdt.driver_data = &bus->chipco;
		wdt.timer_set = ssb_chipco_watchdog_timer_set_wdt;
		wdt.timer_set_ms = ssb_chipco_watchdog_timer_set_ms;
		wdt.max_timer_ms = bus->chipco.max_timer_ms;
	} else if (ssb_extif_available(&bus->extif)) {
		wdt.driver_data = &bus->extif;
		wdt.timer_set = ssb_extif_watchdog_timer_set_wdt;
		wdt.timer_set_ms = ssb_extif_watchdog_timer_set_ms;
		wdt.max_timer_ms = SSB_EXTIF_WATCHDOG_MAX_TIMER_MS;
	} else {
		return -ENODEV;
	}

	pdev = platform_device_register_data(NULL, "bcm47xx-wdt",
					     bus->busnumber, &wdt,
					     sizeof(wdt));
	if (IS_ERR(pdev)) {
		pr_debug("can not register watchdog device, err: %li\n",
			 PTR_ERR(pdev));
		return PTR_ERR(pdev);
	}

	bus->watchdog = pdev;
	return 0;
}