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
typedef  scalar_t__ u32 ;
struct ssb_extif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_EXTIF_WATCHDOG ; 
 scalar_t__ SSB_EXTIF_WATCHDOG_MAX_TIMER ; 
 int /*<<< orphan*/  extif_write32 (struct ssb_extif*,int /*<<< orphan*/ ,scalar_t__) ; 

u32 ssb_extif_watchdog_timer_set(struct ssb_extif *extif, u32 ticks)
{
	if (ticks > SSB_EXTIF_WATCHDOG_MAX_TIMER)
		ticks = SSB_EXTIF_WATCHDOG_MAX_TIMER;
	extif_write32(extif, SSB_EXTIF_WATCHDOG, ticks);

	return ticks;
}