#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ssb_chipcommon {TYPE_2__* dev; } ;
struct bcm47xx_wdt {int dummy; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {scalar_t__ bustype; } ;

/* Variables and functions */
 scalar_t__ SSB_BUSTYPE_SSB ; 
 struct ssb_chipcommon* bcm47xx_wdt_get_drvdata (struct bcm47xx_wdt*) ; 
 int /*<<< orphan*/  ssb_chipco_watchdog_timer_set (struct ssb_chipcommon*,int /*<<< orphan*/ ) ; 

u32 ssb_chipco_watchdog_timer_set_wdt(struct bcm47xx_wdt *wdt, u32 ticks)
{
	struct ssb_chipcommon *cc = bcm47xx_wdt_get_drvdata(wdt);

	if (cc->dev->bus->bustype != SSB_BUSTYPE_SSB)
		return 0;

	return ssb_chipco_watchdog_timer_set(cc, ticks);
}