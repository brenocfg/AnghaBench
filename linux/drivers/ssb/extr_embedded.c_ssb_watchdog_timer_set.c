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
struct ssb_bus {int /*<<< orphan*/  extif; int /*<<< orphan*/  chipco; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ ssb_chipco_available (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_chipco_watchdog_timer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ssb_extif_available (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_extif_watchdog_timer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ssb_watchdog_timer_set(struct ssb_bus *bus, u32 ticks)
{
	if (ssb_chipco_available(&bus->chipco)) {
		ssb_chipco_watchdog_timer_set(&bus->chipco, ticks);
		return 0;
	}
	if (ssb_extif_available(&bus->extif)) {
		ssb_extif_watchdog_timer_set(&bus->extif, ticks);
		return 0;
	}
	return -ENODEV;
}